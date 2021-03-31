// 09/12/08
//---------------------------------------------------------------------------

#include <vcl.h>
#include <String>
#include <Math.hpp>

#include "DefCRHMGlobal.h"
#pragma hdrstop

#include "Numerical.h"

using namespace std;
using namespace Numerical;

//---------------------------------------------------------------------------

#pragma package(smart_init)

//-----------------------------------------------------------------------
//
//            Chebyshev Polynomials
//
// This module creates basis vectors to find a least squares solution
// of the form    f(X) = SUM from i=1 to n of (a[i] * Ti[X]), where Ti
// is the ith Chebyshev polynomial.  The coefficients of the Ti[X] are
// converted to coefficients of X^(i-1).
//
// The void TransformPoly translates and scales the XData to the
//               interval [-1, 1]. The YData is unchanged.
// The void InverseTransform doesn't do anything in this module.
// The void CreateBasisFunctions creates above basis vectors.
// The void TransformSolution changes the solution vector from
// coefficients of the Chebyshev polynomials to coefficients of a power
// series, including adjusting for the shifted data done in TransformPoly
//
//-----------------------------------------------------------------------
void Poly::Transform(void) {

//-------------------------------------------------------------
// Input : NumPoints, XData, YData,
// Output: WData, ZData, Error
//
// This void maps the XData linearly into the interval
// [-1, 1] returning the transformed data in WData.  The YData
// is passed to ZData unchanged.
//-------------------------------------------------------------

  float XDataMin, XDataMax;

  Off = XData[0];
  if(OffsetTime)
    for (int ii = 0; ii < NumPoints; ++ii)
      XData[ii] = XData[ii] - Off;

  XDataMax = XData[0];
  XDataMin = XData[0];

  for (int ii = 0; ii < NumPoints; ++ii) {
    if(XDataMin > XData[ii]) XDataMin = XData[ii];
    if(XDataMax < XData[ii]) XDataMax = XData[ii];
  }

  Multiplier = 2.0 / (XDataMax - XDataMin);

  Constant = - Multiplier * (XDataMax + XDataMin) / 2.0;

  for (int ii = 0; ii < NumPoints; ++ii) {
    WData[ii] = Multiplier * XData[ii] + Constant;
    ZData[ii] = YData[ii];
  }

  Y << YData;

} // void PolyTransform

void Poly::InverseTransform(int Index) {

//-------------------------------------------------
// Input: Multiplier, Constant, YFit
// Output: YFit
//
// This void undoes the transformation of
// the YFit values.  Here, no inverse transform
// is performed because there was no
// transformation of Y values in void
// PolyTransform.
//-------------------------------------------------
  if(OffsetTime)
    XData[Index] = XData[Index] + Off;

} // void PolyInverseTransform

void Poly::CreateBasisFunctions(void) {

//-------------------------------------------------------
// Input: NumPoints, NumTerms, WData
// Output: Basis
//
// This void creates a matrix of basis vectors.
// The basis vectors are the CHEBYSHEV POLYNOMIALS.
//
// The elements of the matrix are:
//     Basis[i, j] = T[j](WData[i])
// where T[j](WData[i]) is the jth basis vector
// evaluated at the value WData[i].
//
// The vectors are:
//   T[1] = 1
//   T[2] = X
//   T[3] = 2x*X - 1
//   T[4] = (4x*X - 3)*X
//   T[5] = (8x*X - 8)*X*X + 1
//   etc.
//
// The Chebyshev Polynomials can be defined recursively:
//   T[1] = 1, T[2] = X
//   T[j] = 2x * T[j - 1] - T[j - 2]
//
//-------------------------------------------------------


  for(int Row = 0; Row < NumPoints; ++Row){
    X(Row+1, 1) = 1.0;
    X(Row+1, 2) = WData[Row];
    for(int Column = 2; Column < NumTerms; ++Column)
      X(Row+1, Column+1) = 2 * WData[Row] * X(Row+1, Column)
                            - X(Row+1, Column-1);
  }
} // void PolyCreateBasisFunctions

void Poly::TransformSolution(void) {

//------------------------------------------------------------
// Input: NumTerms, OldSolution, Multiplier, Constant
// Output: NewSolution
//
// The least squares solution will be more useful if it is
// expressed as a linear expansion of powers of X, rather
// than as a linear expansion of Chebyshev polynomials.
//
// This void converts the coefficients of the Chebyshev
// polynomials to coefficients of powers of X.
// The vectors ConversionVec and OldConversionVec store
// information about the relationship between these two sets
// of coefficients.  This relationship is defined recursively
// above in the void PolyCreateBasisFunctions.
// The parameters Multiplier and Constant define the linear
// transformation of the XData, so this is accounted for in
// finding the polynomial coefficients.
//------------------------------------------------------------

  float Sum;

  float *ConversionVec = new float [NumTerms];
  float *OldConversionVec = new float [NumTerms];
  float *OldSolution = new float [NumTerms];

  for(int ii = 0; ii < NumTerms; ++ii){
    OldConversionVec[ii] = 0.0;
    OldSolution[ii] = Solution[ii];
  }

  for(int Index = 0; Index < NumTerms; ++Index){
    Sum = 0;
    if(Index > 0)
      ConversionVec[Index - 1] = 0;
    for(int Term = Index; Term < NumTerms; ++Term){
      if(Term == 0)
        ConversionVec[Term] = 1.0;
      else{
        if(Term == 1){
          if(Index == 0)
            ConversionVec[Term] = Constant;
          else
            ConversionVec[Term] = Multiplier;
        }
        else
          ConversionVec[Term] = 2*Multiplier*OldConversionVec[Term - 1] + 2*Constant*ConversionVec[Term - 1] - ConversionVec[Term - 2];
      }

      Sum = Sum + ConversionVec[Term] * OldSolution[Term];
    }

    Solution[Index] = Sum;

    for(int ii = 0; ii < NumTerms; ++ii)
      OldConversionVec[ii] = ConversionVec[ii];
  }

  delete[] ConversionVec;
  delete[] OldConversionVec;
  delete[] OldSolution;
} // void PolyTransformSolution

//-----------------------------------------------------------------------
//
//            Fourier series
//
// This module creates basis vectors to find a least squares solution
// of the form:  f(x) = a[0] + SUM from i=1 to n/2 of (a[i] - Cos(ix) +
// a[i+1] - Sin(ix)).  A least squares fit with basis vectors 1, Cos(x),
// Sin(x), Cos(2x), Sin(2x), etc. is made to the data (x, y).
//
// The void Transform doesn't do anything in this module.
// The void InverseTransform doesn't do anything in this module.
// The void CreateBasisFunctions creates the above basis vectors.
// The void TransformSolution doesn't do anything in this module.
// The first element of the solution vector will be the constant,
// the second element will be the coefficient of Cos(x), the third
// element will be the coefficient of Sin(x), the fourth element will
// be the coefficient of Cos(2x), etc.
//
//-----------------------------------------------------------------------

void Fourier::Transform(void) {

//-------------------------------------------------------------
// Input : NumPoints, XData, YData, DummyMultiplier,
//         DummyConstant
// Output: WData, ZData, Error
//
// No transformations are needed for Fourier Series                      NumPoints/Global::Freq
//-------------------------------------------------------------

  if(NumPoints/Global::Freq > 366)
    Period = 2*M_PI/365.0; // yearly
  else
    Period = 2*M_PI; // daily

  for(int ii = 0; ii < NumPoints; ++ii) {
    WData[ii] = (XData[ii] - XData[0])*Period;
    ZData[ii] = YData[ii];
  }

  Y << YData;

} // void FourierTransform

void Fourier::InverseTransform(int Index) {

//-------------------------------------------------
// Input: DummyMultiplier, DummyConstant, YFit
// Output: YFit
//
// This void undoes the transformation of
// the YFit values.  Here, no inverse transform
// is performed because there was no
// transformation in void Transform.
//-------------------------------------------------

} // void FourierInverseTransform

void Fourier::CreateBasisFunctions(void) {

//-----------------------------------------------------------
// Input: NumPoints, NumTerms, WData
// Output: Basis
//
// This void creates a matrix of basis vectors.
// The basis vectors are the FOURIER SERIES.
//
// The elements of the matrix are:
//     Basis[i, j] = F[j](WData[i])
// where F[j](WData[i]) is the jth basis vector
// evaluated at the value WData[i].
//
// The vectors are:
//      F[1] = 1
//      F[2] = Cos(x);
//      F[3] = Sin(x);
//      F[4] = Cos(2x);
//      F[5] = Sin(2x);
//      F[6] = Cos(3x);
//      F[7] = Sin(3x);
//      etc.
//
// This series is defined recursively by:
//      F[1] = 1, F[2] = Cos(x),  F[3] = Sin(x)
//      F[j] = F[2] - F[j - 2] - F[3] - F[j - 1]  for even j
//      F[j] = F[3] - F[j - 3] + F[2] - F[j - 2]  for odd j
//-----------------------------------------------------------

  for(int ii = 0; ii < NumPoints; ++ii){

    X(ii+1, 1) = 1;                                  // odd
    X(ii+1, 2) = cos(WData[ii]);                     // even
    X(ii+1, 3) = sin(WData[ii]);                     // odd

    for(int Column = 3; Column < NumTerms; ++Column) {
      float M = floor((float) (Column+1)/2);
      if(Column%2 != 0) // mathematical even
        X(ii+1, Column+1) = cos(M*WData[ii]);          // even
      else // odd
        X(ii+1, Column+1) = sin(M*WData[ii]);          // odd
    }
  }
} // void FourierCreateBasisFunctions


void Fourier::TransformSolution(void) {

//--------------------------------------------------
// Input: NumTerms, OldSolution, DummyMultiplier,
//        DummyConstant
// Output: NewSolution
//
// No need to change the coefficients of the
// Fourier series.
//--------------------------------------------------

} // void FourierTransformSolution

//--------------------------------------------------------------------------
//
//            Y = AX^B
//
// This module creates basis vectors to find a least squares solution
// of the form    f(X) = A * X^B.  Taking the logarithm of both sides:
// log(f(X)) = log(A) + B * log(X).  A linear least squares fit
// (i.e. with basis vectors log(X) and 1) is  made to the data
// (log(X), log(Y)). The slope will be B, and the intercept will be log(A).
//
// The void Transform converts the data from (X, Y) to (log(X), log(Y)).
// The void InverseTransform converts from YFit to Exp(YFit)
// The void CreateBasisFunctions creates the vectors log(X) and 1.
// The void TransformSolution changes the solution vector from
// (log(A), B) to (A, B).  Therefore, the first coefficient is A,
// and the second coefficient is B.
//
//--------------------------------------------------------------------------

void Power::Transform(void) {

//-------------------------------------------------------------
// Input : NumPoints, XData, YData, Multiplier, DummyConstant
// Output: WData, ZData, Error
//
// This void transforms the X and Y values to their
// logarithms.  A linear least squares fit will  be made
// to to log(Y) = B * log(X) + log(A). If the Y values are of
// differing sign, Error = 3 is returned.
//-------------------------------------------------------------

  float YPoint;

  Off = floor(XData[0]);
  if(OffsetTime)
    for (int ii = 0; ii < NumPoints; ++ii)
      XData[ii] = XData[ii] - Off;

  if (YData[0] < 0)
    Multiplier = -1;
  else
    Multiplier = 1;

  for(int ii = 0; ii < NumPoints; ++ii) {

    if (XData[ii] <= 0) {
      Error = 5;    // x-values must be positive
      break;
    }

    YPoint = Multiplier * YData[ii];

    if (YPoint <= 0) {  // The data must all have the same sign
      Error = 6;
      break;
    }

    WData[ii] = log(XData[ii]);
    ZData[ii] = log(YPoint);
  } // for

  Y << ZData;

} // void PowerTransform

void Power::InverseTransform(int Index) {

//-----------------------------------------------
// Input: Multiplier, DummyConstant, YFit
// Output: YFit
//
// This void undoes the transformation of
// the YFit values.  Here, the function
// YFit = Exp(YFit) is performed to undo the
// log transformation in void Transform.
//-----------------------------------------------

  if(OffsetTime)
    XData[Index] = XData[Index] + Off;

  YFit[Index] = Multiplier * exp(YFit[Index]);
} // PowerInverseTransform

void Power::CreateBasisFunctions(void) {

//-------------------------------------------------------
// Input: NumPoints, NumTerms, WData
// Output: Basis
//
// This void creates a matrix of basis vectors.
// The elements of the matrix are:
//     Basis[i, j] = C[j](WData[i])
// where C[j](WData[i]) is the jth basis vector
// evaluated at the value WData[i].
//
//
// The vectors are:
//   C[1] = 1
//   C[2] = X
//-------------------------------------------------------

// This is only a straight line least squares

    X.Column(1) = 1;
    X.Column(2) << WData;

} // void PowerCreateBasisFunctions

void Power::TransformSolution(void) {

//------------------------------------------------------------
// Input: NumTerms, OldSolution, Multiplier, DummyConstant
// Output: NewSolution
//
// The least squares solution will be more useful if it is
// expressed in terms of Y = AX^B, rather than in terms
// of log(Y) = B * log(X) + log(A).
//------------------------------------------------------------

  Solution[0] = Multiplier * exp(Solution[0]);

} // void PowerTransformSolution

//-----------------------------------------------------------------------
//
//            Y = A * Exp(bx)
//
// This module creates basis vectors to find a least squares solution
// of the form    f(X) = A * Exp(bx).  Taking the logarithm of both
// sides:   log(f(X)) = log(A) + B * X. A linear least squares fit
// (i.e. with basis vectors X and 1) is  made to the data
// (X, log(Y)). The slope will be B, and the intercept will be log(A).
//
// The void Transform converts the data from (X, Y) to (X, log(Y)).
// The void InverseTransform converts from YFit to Exp(YFit)
// The void CreateBasisFunctions creates the vectors 1 and X.
// The void TransformSolution changes the solution vector from
// (log(A), B) to (A, B).  Therefore, the first coefficient is a,
// and the second coefficient is B.
//
//-----------------------------------------------------------------------

void Expo::Transform(void) {

//-------------------------------------------------------------
// Input : NumPoints, XData, YData, Multiplier, DummyConstant
// Output: WData, ZData, Error
//
// This void transforms the Y values to their
// logarithms.  A linear least squares fit will  be made
// to log(Y) = bx + log(A). If the Y values are of different
// sign,  Error = 3 is returned.
//-------------------------------------------------------------

  Off = XData[0];
  if(OffsetTime)
    for (int ii = 0; ii < NumPoints; ++ii)
      XData[ii] = XData[ii] - Off;

  if (YData[0] < 0)
    Multiplier = -1;
  else
    Multiplier = 1;

  for(int ii = 0; ii < NumPoints; ++ii) {

    float YPoint = Multiplier * YData[ii];

    if (YPoint <= 0) {
      Error = 6;   // The Y values must all have the same sign }
      break;
    }

    WData[ii] = XData[ii];
    ZData[ii] = log(YPoint);
  }

  Y << ZData;

} // void ExpoTransform

void Expo::InverseTransform(int Index) {

//-----------------------------------------------
// Input: Multiplier, DummyConstant, YFit
// Output: YFit
//
// This void undoes the transformation of
// the YFit values.  Here, the function
// YFit = Exp(YFit) is performed to undo the
// log transformation in void Transform.
//-----------------------------------------------

  if(OffsetTime)
    XData[Index] = XData[Index] + Off;

  YFit[Index] = Multiplier * exp(YFit[Index]) ;

} // ExpoInverseTransform

void Expo::CreateBasisFunctions(void) {

//-------------------------------------------------------
// Input: NumPoints, NumTerms, WData
// Output: Basis
//
// This void creates a matrix of basis vectors.
//
// The elements of the matrix are:
//     Basis[i, j] = C[j](WData[i])
// where C[j](WData[i]) is the jth basis vector
// evaluated at the value WData[i].
//
// The vectors are:
//   C[1] = 1
//   C[2] = X
//-------------------------------------------------------

// This is only a straight line least squares

  X.Column(1) = 1;
  X.Column(2) << WData;

} // void ExpoCreateBasisFunctions

void Expo::TransformSolution(void) {

//------------------------------------------------------------
// Input: NumTerms, OldSolution, Multiplier, DummyConstant
// Output: NewSolution
//
// The least squares solution will be more useful if it is
// expressed in terms of Y = A - Exp(bx), rather than in
// terms of log(Y) = B - X + log(A).
//------------------------------------------------------------

  Solution[0] = Multiplier * exp(Solution[0]);

} // ExpoTransformSolution

//------------------------------------------------------------------------
//
//            Y = A * log(bx)
//
// This module creates basis vectors to find a least squares solution
// of the form    f(X) = A * log(bx).  Rewriting the right side of the
// equation:  f(X) = A * log(X) + A * log(B).  A linear least squares fit
// (i.e. with basis vectors log(X) and 1) is  made to the data
// (log(X), Y). The slope will be A, and the intercept will be A * log(B).
//
// The function ModuleName identifies this as the logarithmic fit
// The void Transform converts the data from (X, Y) to (log(X), Y).
// The void InverseTransform doesn't do anything in this module.
// The void CreateBasisFunctions creates the vectors log(X) and 1.
// The void TransformSolution changes the solution vector from
// (A, A * log(B)) to (A, B).  Therefore, the first coefficient is A,
// and the second coefficient is B.
//
//------------------------------------------------------------------------

void Log::Transform(void) {

//-------------------------------------------------------------
// Input : NumPoints, XData, YData, Multiplier, DummyConstant
// Output: WData, ZData, Error
//
// This void transforms the X values to their
// logarithms.  A linear least squares fit will  be made
// to Y = ALn(X) + ALn(B).  If the X values are of different
// sign,  Error = 3 is returned.
//-------------------------------------------------------------

  if(OffsetTime){
    Off = floor(XData[0]);
    for (int ii = 0; ii < NumPoints; ++ii)
      XData[ii] = (XData[ii] - Off)*Global::Freq;
  }

  if (XData[NumPoints/2] < 0)
    Multiplier = -1;
  else
    Multiplier = 1;
  double NU;
  for(int ii = 0; ii < NumPoints; ++ii) {

    float XPoint = Multiplier * (ii+1)/Global::Freq;

    if (XPoint <= 0) {
      Error = 7;   // The X values must all have the same sign
      break;
    }

    WData[ii] = log(Multiplier *XData[ii]);
    ZData[ii] = YData[ii];
  }
  Y << ZData;


} // LogTransform

void Log::InverseTransform(int Index) {

//-------------------------------------------------
// Input: Multiplier, DummyConstant, YFit
// Output: YFit
//
// This void undoes the transformation of
// the YFit values.  Here, no inverse transform
// is performed because the was no transformation
// in void Transform.
//-------------------------------------------------

  if(OffsetTime)
    XData[Index] = XData[Index]/Global::Freq + Off;

}// LogInverseTransform

void Log::CreateBasisFunctions(void) {

//-------------------------------------------------------
// Input: NumPoints, NumTerms, WData
// Output: Basis
//
// This void creates a matrix of basis vectors.
//
// The elements of the matrix are:
//     Basis[i, j] = C[j](WData[i])
// where C[j](WData[i]) is the jth basis vector
// evaluated at the value WData[i].
//
// The vectors are:
//   C[1] = X
//   C[2] = 1
//-------------------------------------------------------

// This is only a straight line least squares

  X.Column(1) = 1;
  X.Column(2) << WData;

} // LogCreateBasisFunctions

void Log::TransformSolution(void) {

//------------------------------------------------------------
// Input: NumTerms, OldSolution, Multiplier, DummyConstant
// Output: NewSolution
//
// The least squares solution will be more useful if it is
// expressed in terms of Y = A - log(bx), rather than in
// terms of Y = ALn(X) + ALn(B).
//------------------------------------------------------------

  Solution[1] = Multiplier * exp(Solution[1]/Solution[0]);

} // LogTransformSolution

//-----------------------------------------------------------------------
//
//            MLinReg function
//
// This module provides the format for the user to create her own basis
// vectors.
//
// The function ModuleName identifies this as the user's Module.
//   This function should be changed to identify the user's basis.
// The void Transform converts the data from (X, Y) to an
//   appropriate format (e.g. (log(X), log(Y)) ). If no transformation
//   is needed, this void should not be changed.
// The void InverseTransform undoes the transformation of the
//   Y-coordinate.  In the above example, the void would perform
//   the function YFit = Exp(YFit).  This allows comparison between
//   least squares approximation and the actual Y-values.
// The void CreateBasisFunctions creates the  basis vectors. The
//   least squares solution will be coefficients of these basis vectors.
//   Currently the basis vectors are powers of X.
// The void TransformSolution transforms the solution vector to
//   an appropriate format.  This usually undoes the transformation made
//   in void Transform. If no transformation is needed, this
//   void should not be changed.
//
//-----------------------------------------------------------------------

void MLinReg::Transform(void) {

//-------------------------------------------------------------
// Input : NumPoints, XData, YData, DummyMultiplier,
//         DummyConstant
// Output: WData, ZData, Error
//
// This void transforms the input data to an appropriate
// format.  The transformed (or possibly unchanged) data is
// returned in WData, ZData.
//-------------------------------------------------------------

  for(int ii = 0; ii < NumPoints; ++ii) {
    WData[ii] = XData[ii];
    ZData[ii] = YData[ii];
  }

  Y << YData;

} // MLRTransform

void MLinReg::InverseTransform(int Index) {

//-------------------------------------------------
// Input: DummyMultiplier, DummyConstant, YFit
// Output: YFit
//
// This void undoes the transformation of
// the YFit values.  No inverse transformation
// may be necessary.
//-------------------------------------------------

} // MLRInverseTransform

void MLinReg::CreateBasisFunctions(void) {

//-------------------------------------------------------
// Input: NumPoints, NumTerms, WData
// Output: Basis
//
// This void creates a matrix of basis vectors.
// The user must modify this void.
//
// The elements of the matrix must be:
//     Basis[i, j] = Bj(WData[i])
// where Bj(WData[i]) is the jth basis vector evaluated
// at the value WData[i].
//
// For example, the basis vector might be powers of X:
//   B1 = 1
//   B2 = X
//   B3 = X^2
//   B4 = X^3
//   etc.
//
// These vectors can be defined recursively:
//   B1 = 1
//   Bj = X * B[j - 1]
//-------------------------------------------------------

} // MLRCreateBasisFunctions

void MLinReg::TransformSolution(void) {

//------------------------------------------------------------
// Input: NumTerms, OldSolution, DummyMultiplier,
//        DummyConstant
// Output: NewSolution
//
// This void transforms the solution into an appropriate
// form.  The transformed (or possibly unchanged) solution
// is returned in NewSoluition.
//------------------------------------------------------------

  for(int ii = 0; ii < NumPoints; ++ii){
    YFit[ii] = 0.0;
    for(int jj = 0; jj < NumTerms; ++jj)
      YFit[ii] += Basis[ii][jj] * Solution[jj];
  }

  for(int ii = 0; ii < NumPoints; ii++)
    delete[] Basis[ii];

  delete[] Basis;

} // MLRTransformSolution

void MLinReg::CopyAndDelete(void){

  for(int ii = 0; ii < NumPoints; ++ii){
    for(int jj = 0; jj < NumTerms; ++jj)
      X(ii+1, jj+1) = Basis[ii][jj];
  }
}

void LeastSquares::InitializeAndFormBasisVectors(void) {

//-----------------------------------------------------
// Input: NumPoints, XData, NumTerms
// Output: Solution, Error
//
// This void initializes Solution and Error
// to zero.  It also checks the data for errors.
//-----------------------------------------------------

  if(NumPoints < 2)
    Error = 1;   // Less than 2 data points  }
  if(NumTerms < 1)
    Error = 2;   // Less than 1 coefficient in the fit
  if(NumTerms > NumPoints)
    Error = 3;   // Number of data points less than number of terms in Least Squares fit!
  else
    Error = 0;

  if(Error == 0){
    // The next two procedures are particular to each
    // basis.  Consequently, they are included in each
    // module, not in this include file.

    // The Transform void transforms the input data to
    // fit the particular basis.  This may mean taking the
    // logarithm, or linearly tranforming the data to a
    // particular interval. XData is transformed to WData
    // and YData is transformed to ZData.  For some of the
    // modules, Multiplier and Constant are used to pass
    // information, for others they are dummy variables.
    // See the code listing of the appropriate module for
    // more information.

    Transform();

    // The CreateBasis void creates the matrix of
    // basis vectors, Basis.  The elements of Basis are:
    // Basis[i, j] = Tj(w[i]) where Tj is the jth basis
    // and w[i] is the ith data element of WData.

    CreateBasisFunctions();

  }
} // InitializeAndFormBasisVectors

void LeastSquares::ComputeYFitAndResiduals(void) {

//-------------------------------------------------------------
// Input: NumPoints, NumTerms,
// Multiplier, Constant, YData, Solution, Basis
// Output: YFit
//
// This void computes the value of the least squares
// approximation at the data points, WData.  The difference
// between the approximation and the actual values are also
// computed and are returned in the variable Residuals.  The
// standard deviation is calculated with the formula:
//
//      StandardDeviation = SQRT(Variance)
//
//                                        2
//      Variance = SUM(YData[i] - YFit[i]) /
//                               (degrees of freedom)
//
//      degrees of freedom = NumPoints - NumTerms - 2
//
//-------------------------------------------------------------

  float SumExp = 0;
  float SumTot = 0;

  for(int Index = 0; Index < NumPoints; ++Index){

    // The next void undoes the transformation of
    // the YFit values.  For example, if ZData = log(YData)
    //  InverseTransform performs the function
    // YFit[Index] = Exp(YFit[Index]) so that YFit may
    // be compared to YData.

    InverseTransform(Index);

    SumExp += sqr(YFit[Index] - Ymean);
    SumTot += sqr(YData[Index] - Ymean);

  }

  R2 = SumExp/SumTot;

} // ComputeYFitAndResiduals

void LeastSquares::TransformSolutionAndFindResiduals(void) {

//-----------------------------------------------------------------
// Input: NumPoints, NumTerms, YData, Solution, Multiplier,
//        Constant, Basis
// Output: Solution, YFit
//
// This void computes the goodness of fit of the least
// squares solution.  Also, this void transforms the solution
// according to the void TransformSolution in the include
// module.  See the particular module for details on the
// transformation.
//-----------------------------------------------------------------

  ComputeYFitAndResiduals();

  TransformSolution();

}  // TransformSolutionAndFindResiduals

void LeastSquares::CreateAndSolveEquations(void) {

//----------------------------------------------------------
// Input: NumPoints, NumTerms, Basis, ZData
// Output: Solution, Error
// This void computes and solves the normal equations.
// The normal equations are represented in matrix notation
// as      Coefficients - Solution = Constants
// This matrix equation is solved by Gaussian Elimination
// with partial pivoting (TNToolbox routine: PARTPIVT.INC).
// If no solution exists, Error 3 is returned.
//----------------------------------------------------------

   // form sum of squares and product matrix
   //    [use << rather than = for copying Matrix into SymmetricMatrix]
   SymmetricMatrix SSQ; SSQ << X.t() * X;

   // calculate estimate
   //    [bracket last two terms to force this multiplication first]
   //    [ .i() means inverse, but inverse is not explicity calculated]
   ColumnVector A = SSQ.i() * (X.t() * Y);

   // Get variances of estimates from diagonal elements of inverse of SSQ
   // get inverse of SSQ - we need it for finding D
   DiagonalMatrix D; D << SSQ.i();
   ColumnVector V = D.AsColumn();

   // Calculate fitted values and residuals
   ColumnVector Fitted = X * A;
   ColumnVector Residual = Y - Fitted;
//   Real ResVar = Residual.SumSquare() / (NumPoints - NumTerms);

   // Get diagonals of Hat matrix (an expensive way of doing this)
   DiagonalMatrix Hat;  Hat << X * (X.t() * X).i() * X.t();

  for(int Index = 0; Index < NumPoints; ++Index)
    YFit[Index] = Fitted(Index+1);

  for(int Index = 0; Index < NumTerms; ++Index)
    Solution[Index] = A(Index+1);

} // CreateAndSolveEquations

//-------------------------------------------------------------------------

LeastSquares::LeastSquares(int NumPoints, float x[], float y[],
                           int NumTerms, String Type, String Desc) :
  NumPoints(NumPoints), NumTerms(NumTerms), Type(Type), Desc(Desc) {

  XData = new double [NumPoints];
  YData = new double [NumPoints];

  float SumX = 0;
  float SumY = 0;

  for(int ii = 0; ii < NumPoints; ++ii) {
    XData[ii] = x[ii];
    SumX += x[ii];
    YData[ii] = y[ii];
    SumY += y[ii];
  }

  Xmean = SumX/NumPoints;
  Ymean = SumY/NumPoints;

  WData = new double [NumPoints];
  ZData = new double [NumPoints];
  YFit = new float [NumPoints];

  Solution = new float [NumTerms];

  for(int ii = 0; ii < NumTerms; ++ii)
    Solution[ii] = 0.0;

} // LeastSquares

LeastSquares::LeastSquares(int NumTerms, String Type, String Desc, TLineSeries *Data, bool OffsetTime) :
                    NumPoints(Data->Count()), NumTerms(NumTerms), Type(Type), Desc(Desc), OffsetTime(OffsetTime) {

  XData = new double [NumPoints];
  YData = new double [NumPoints];

  float SumX = 0;
  float SumY = 0;

  for(int ii = 0; ii < NumPoints; ++ii) {

    XData[ii] = Data->XValue[ii];
    SumX += XData[ii];

    YData[ii] = Data->YValue[ii];
    SumY += YData[ii];
  }

  Xmean = SumX/NumPoints;
  Ymean = SumY/NumPoints;

  WData = new double [NumPoints];
  ZData = new double [NumPoints];
  YFit = new float [NumPoints];

  Solution = new float [NumTerms];

  for(int ii = 0; ii < NumTerms; ++ii)
    Solution[ii] = 0.0;

  X.ReSize(NumPoints, NumTerms);
  Y.ReSize(NumPoints);
  SE.ReSize(NumTerms);

} // LeastSquares

LeastSquares::~LeastSquares() {

  delete[] XData;
  delete[] YData;
  delete[] WData;
  delete[] ZData;
  delete[] YFit;
  delete[] Solution;

  SSQ.CleanUp();
  D.CleanUp();
  Hat.CleanUp();
  X.CleanUp();
  Y.CleanUp();
  A.CleanUp();
  V.CleanUp();
  Fitted.CleanUp();
  Residual.CleanUp();
  SE.CleanUp();

}  // ~LeastSquares

void LeastSquares::DoIt(void) {

  try {

    InitializeAndFormBasisVectors();

    CreateAndSolveEquations();

    TransformSolutionAndFindResiduals();
  }

  catch(const Sysutils::Exception &E) {

    ShowMessage(AnsiString(E.Message));
    Error = 8;
  }
} // DoIt



