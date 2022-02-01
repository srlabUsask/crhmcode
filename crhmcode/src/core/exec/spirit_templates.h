#pragma once

#ifndef SPIRIT_TEMPLATES
#define SPIRIT_TEMPLATES


using namespace std;
using namespace BOOST_SPIRIT_CLASSIC_NS;

template <typename T, typename result = bool>
struct L_not : public unary_function<T, result> {
	result operator()(const T x) const { return (result)(!x); }
};

template <typename T, typename result = bool>
struct L_and : public binary_function<T, T, result> {
	result operator()(const T x, const T y) const { return (result)(x && y); }
};

template <typename T, typename result = bool>
struct L_or : public binary_function<T, T, result> {
	result operator()(const T x, const T y) const { return (result)(x || y); }
};

template <typename T, typename result = bool>
struct L_GT : public binary_function<T, T, result> {
	result operator()(const T x, const T y) const { return (result)(x > y); }
};

template <typename T, typename result = bool>
struct L_GE : public binary_function<T, T, result> {
	result operator()(const T x, const T y) const { return (result)(x >= y); }
};

template <typename T, typename result = bool>
struct L_LT : public binary_function<T, T, result> {
	result operator()(const T x, const T y) const { return (result)(x < y); }
};

template <typename T, typename result = bool>
struct L_LE : public binary_function<T, T, result> {
	result operator()(const T x, const T y) const { return (result)(x <= y); }
};

template <typename T, typename result = bool>
struct L_EQ : public binary_function<T, T, result> {
	result operator()(const T x, const T y) const { return (result)(x == y); }
};

template <typename T, typename result = bool>
struct L_NE : public binary_function<T, T, bool> {
	result operator()(const T x, const T y) const { return (result)(x != y); }
};

template <typename arg1, typename result = arg1>
struct SineC : public unary_function<arg1, result> {
	result operator()(const arg1 x) const { return (result)sin(x / 180 * M_PI); }
};

template <typename arg1, typename result = arg1>
struct TanC : public unary_function<arg1, result> {
	result operator()(const arg1 x) const { return (result)tan(x / 180 * M_PI); }
};

template <typename arg1, typename result = arg1>
struct CosC : public unary_function<arg1, result> {
	result operator()(const arg1 x) const { return (result)cos(x / 180 * M_PI); }
};

template <typename arg1, typename result = arg1>
struct ExpC : public unary_function<arg1, result> {
	result operator()(const arg1 x) const { return (result)exp(x); }
};

template <typename arg1, typename result = arg1>
struct LogC : public unary_function<arg1, result> {
	result operator()(const arg1 x) const { return (result)log(x); }
};

template <typename arg1, typename result = arg1>
struct estarC : public unary_function<arg1, result> {
	result operator()(const arg1 x) const { return (result)Common::estar(x); }
};

template <typename T, typename result = T>
struct patmosC : public unary_function<T, result> {
	result operator()(const T Ht) const { return (result)(101.3 * pow((293.0 - 0.0065 * Ht) / 293.0, 5.26)); } // kPa
};

template <typename arg1, typename result = arg1>
struct Log10C : public unary_function<arg1, result> {
	result operator()(const arg1 x) const { return (result)log10(x); }
};

template<typename arg1, typename arg2 = arg1, typename result = arg1>
class PowerC : binary_function <arg1, arg2, result> {
public:
	result operator() (const arg1& x, const arg2& x1) const { return (result)pow(x, x1); }
};

template<typename arg1, typename arg2 = arg1, typename result = arg1>
class MaxC : binary_function <arg1, arg2, result> {
public:
	result operator() (const arg1& x, const arg2& x1) const { return (result)max(x, x1); }
};

template<typename arg1, typename arg2 = arg1, typename result = arg1>
class MinC : binary_function <arg1, arg2, result> {
public:
	result operator() (const arg1& x, const arg2& x1) const { return (result)min(x, x1); }
};

template<typename arg1, typename arg2 = arg1, typename result = arg1>
class spec_humidC : binary_function <arg1, arg2, result> {
public:
	result operator() (const arg1  ea, const arg2 Pa) const { return (result)(0.622 * ea / (Pa - ea * 0.378)); }
};

template <class _Tp>
struct modulus : public binary_function<_Tp, _Tp, _Tp>
{
	_Tp operator()(const _Tp& __x, const _Tp& __y) const { return fmod(__x, __y); }
};


#endif // !SPIRIT_TEMPLATES
