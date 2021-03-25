// 06/25/07
//---------------------------------------------------------------------------
#ifndef NumericalH
#define NumericalH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <Series.hpp>
#include "newmat.h"

using namespace std;

namespace Numerical {
class LeastSquares{
  public:
  String Type;
  String Desc;
  int NumPoints;         // number of data pairs (col)
  int NumTerms;
  int Error;

  bool OffsetTime;
  double Off;
  
  double * XData;         // input X  (col)
  double * YData;         // input Y  (col)
  double * WData;         // transformed input X (col)
  double * ZData;         // transformed input Y (col)
  float * YFit;          // (col)
  float * Solution;      // (row)

  float Multiplier;
  float Constant;
  float Ymean;
  float Xmean;
  float R2;

  Matrix X;
  SymmetricMatrix SSQ;
  DiagonalMatrix D;
  DiagonalMatrix Hat;
  ColumnVector Y;
  ColumnVector A;
  ColumnVector V;
  ColumnVector Fitted;
  ColumnVector Residual;
  ColumnVector SE;


  LeastSquares(int NumPoints, float x[], float y[], int NumTerms, String Type, String Desc);
  LeastSquares(int NumTerms, String Type, String Desc, TLineSeries *Data, bool OffsetTime);


  virtual void Transform(void){};                // none
  virtual void InverseTransform(int Index){};    // none
  virtual void CreateBasisFunctions(void){};     // none
  virtual void TransformSolution(void){};        // none

  void DoIt(void);                               // none
  void InitializeAndFormBasisVectors(void);
  void CreateAndSolveEquations(void);
  void TransformSolutionAndFindResiduals(void);
  void ComputeYFitAndResiduals(void);

  virtual ~LeastSquares();
};

class Poly : public LeastSquares{
  public:
  Poly(int NumPoints, float x[], float y[], int NumTerms) :
    LeastSquares(NumPoints, x, y, NumTerms,
                   "Polynomial Least Squares Fit", "Poly") {DoIt();};

  Poly(TLineSeries *Data, bool OffsetTime, int NumTerms) :
    LeastSquares(NumTerms,
                   "Polynomial Least Squares Fit", "Poly", Data, OffsetTime) {DoIt();};

  void Transform(void);
  void CreateBasisFunctions(void);
  void InverseTransform(int Index);
  void TransformSolution(void);
};

class Fourier : public LeastSquares{

  float Period;
  public:
  Fourier(int NumPoints, float x[], float y[], int NumTerms) :
    LeastSquares(NumPoints, x, y, NumTerms,
      "Fourier Finite Series Least Squares Fit", "For"){DoIt();};

  Fourier(TLineSeries *Data, bool OffsetTime, int NumTerms) :
    LeastSquares(NumTerms, "Fourier Finite Series Least Squares Fit", "For", Data, OffsetTime){DoIt();};

  void Transform(void);
  void CreateBasisFunctions(void);
  void InverseTransform(int Index);
  void TransformSolution(void);
};

class Power : public LeastSquares{
  public:
  Power(int NumPoints, float x[], float y[]) :
    LeastSquares(NumPoints, x, y, 2, "Power Law Least Squares Fit", "Pow"){DoIt();};

  Power(TLineSeries *Data, bool OffsetTime) :
    LeastSquares(2, "Power Law Least Squares Fit", "Pow", Data, OffsetTime){DoIt();};

  void Transform(void);
  void CreateBasisFunctions(void);
  void InverseTransform(int Index);
  void TransformSolution(void);
};

class Expo : public LeastSquares{
  public:
  Expo(int NumPoints, float x[], float y[]) :
    LeastSquares(NumPoints, x, y, 2, "Exponential Least Squares Fit", "Exp"){DoIt();};

  Expo(TLineSeries *Data, bool OffsetTime) :
    LeastSquares(2, "Exponential Least Squares Fit", "Exp", Data, OffsetTime){DoIt();};

  void Transform(void);
  void CreateBasisFunctions(void);
  void InverseTransform(int Index);
  void TransformSolution(void);
};

class Log : public LeastSquares{
  public:
  Log(int NumPoints, float x[], float y[]) :
    LeastSquares(NumPoints, x, y, 2, "Logarithmic Least Squares Fit", "Log"){DoIt();};

  Log(TLineSeries *Data, bool OffsetTime) :
    LeastSquares(2, "Logarithmic Least Squares Fit", "Log", Data, OffsetTime){DoIt();};

  void Transform(void);
  void CreateBasisFunctions(void);
  void InverseTransform(int Index);
  void TransformSolution(void);
};

class MLinReg : public LeastSquares{
  public:
  MLinReg(int NumPoints, float x[], float y[], int NumTerms) :
    LeastSquares(NumPoints, x, y, NumTerms, "Multiple Linear Regression", "MLR"){DoIt();};

  MLinReg(TLineSeries *Data, int NumTerms, double **Basis) :
    LeastSquares(NumTerms, "Multiple Linear Regression", "MLR", Data, false), Basis(Basis) {CopyAndDelete(), DoIt();};

  double **Basis;

  void Transform(void);
  void CreateBasisFunctions(void);
  void InverseTransform(int Index);
  void TransformSolution(void);
  void CopyAndDelete(void);
};

class User : public LeastSquares{
  public:
  User(int NumPoints, float x[], float y[]) :
    LeastSquares(NumPoints, x, y, 2, "User's Fit - currently powers of X", "Use"){DoIt();};

  User(TLineSeries *Data, int NumTerms) :
    LeastSquares(2, "User's Fit - currently powers of X", "Use", Data, OffsetTime){DoIt();};

  void Transform(void);
  void CreateBasisFunctions(void);
  void InverseTransform(int Index);
  void TransformSolution(void);
};
}
#endif

 