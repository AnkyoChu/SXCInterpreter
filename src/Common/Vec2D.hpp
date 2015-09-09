/*********************************************************************
 *
 *	@file		Vec2D.h
 *	@brief		用于二元组
 *
 *
 *	Date        Name        Description
 *	07/03/15	MYLS		Creation.
 *
 *********************************************************************/

#pragma once

#include <cmath>
#include <sstream>
#include "Calculation.hpp"

namespace cm {
	template <typename T> class Vec2D;
}


/**
 *	\brief	二元组，Vec2D<T>
 *			包含了基本的向量运算
 */
template <typename T> class cm::Vec2D {

public:

	/*==========================================================================*/
	/*	公有 构造\析构															*/
	/*==========================================================================*/

	Vec2D();

	Vec2D(Vec2D && rhs);

	Vec2D(const Vec2D & rhs);

	Vec2D(const T x, const T y);

	/* 极坐标形式，isPolar == true 时将按照极坐标形式初始化，否则任然为x, y的形式 */
	Vec2D(const double theta, const T distance, bool isPolar);

#ifdef B2_MATH_H
	Vec2D(const b2Vec2 &rhs)
		: _X(rhs.x), _Y(rhs.y)
	{}

	operator b2Vec2() const
	{
		return std::move(b2Vec2(static_cast<float>(_X), static_cast<float>(_Y)));
	}
#endif

public:

	/*==========================================================================*/
	/*	公有 操作符重载															*/
	/*==========================================================================*/

	bool operator==(const Vec2D& rhs) const;

	bool operator!=(const Vec2D<T>& rhs) const;

	Vec2D<T> operator+(const Vec2D<T>& rhs) const;

	Vec2D<T> operator-(const Vec2D<T>& rhs) const;

	Vec2D<T> operator-() const;

	Vec2D<T> operator*(const T scalar) const;

	Vec2D<T> operator/(const T scalar) const;

	Vec2D<T>& operator=(const Vec2D<T>& rhs);

	Vec2D<T>& operator+=(const Vec2D<T>& rhs);

	Vec2D<T>& operator-=(const Vec2D<T>& rhs);

	Vec2D<T>& operator*=(const T scalar);

	Vec2D<T>& operator/=(const T scalar);

	friend std::istringstream& operator >> (std::istringstream& iss, Vec2D<T>& rhs)
	{
		const int MAX_LENGTH_IN_LINE = 80;
		iss.ignore(MAX_LENGTH_IN_LINE, '(');
		iss >> rhs._X;
		iss.ignore(MAX_LENGTH_IN_LINE, ',');
		iss >> rhs._Y;
		iss.ignore(MAX_LENGTH_IN_LINE, ')');
		iss.ignore(MAX_LENGTH_IN_LINE, ' ');
		return iss;
	}

public:

	/*==========================================================================*/
	/*	公有 方法																*/
	/*==========================================================================*/

	T GetX() const;

	T GetY() const;

	void SetX(const T x);

	void SetY(const T y);

	void Set(const T x, const T y);

	Vec2D& IncreaseX(const T x);

	Vec2D& IncreaseY(const T y);

	Vec2D& Counterclockwise90();

	Vec2D& Clockwise90();

	Vec2D& Exchange();

	Vec2D& Normalize();

	T LengthSquared() const;

	T Length() const;

	T DistanceSquared(const Vec2D & rhs) const;

	T Distance(const Vec2D & rhs) const;

	T cross(const Vec2D & rhs) const;

	T dot(const Vec2D & rhs) const;

	double Angle() const;

	double AngleTo(const Vec2D & rhs) const;

private:

	/*==========================================================================*/
	/*	私有成员变量															*/
	/*==========================================================================*/

	T _X;			/**< 第一个元素 */
	T _Y;			/**< 第二个元素 */
};








/*==========================================================================*/
/*	公有 构造\析构															*/
/*==========================================================================*/

template <typename T> inline cm::Vec2D<T>::
Vec2D()
	: _X(0)
	, _Y(0)
{}

template <typename T> inline cm::Vec2D<T>::
Vec2D(Vec2D<T> && rhs)
	: _X(rhs._X)
	, _Y(rhs._Y)
{}

template <typename T> inline cm::Vec2D<T>::
Vec2D(const Vec2D & rhs)
	: _X(rhs._X)
	, _Y(rhs._Y)
{}

template <typename T> inline cm::Vec2D<T>::
Vec2D(const T x, const T y)
	: _X(x)
	, _Y(y)
{}

template <typename T> inline cm::Vec2D<T>::
Vec2D(const double theta, const T distance, bool isPolar)
	: _X(static_cast<T>(cos(theta) * distance))
	, _Y(static_cast<T>(sin(theta) * distance))
{
	if (!isPolar) {
		_X = static_cast<T>(theta);
		_Y = static_cast<T>(distance);
	}
}

/*==========================================================================*/
/*	公有 操作符重载															*/
/*==========================================================================*/

template <> inline bool cm::Vec2D<float>::
operator==(const Vec2D<float>& rhs) const
{
	float delta = (_X > rhs._X) ? (_X - rhs._X) : (rhs._X - _X);
	if (Calculation::EPSf < delta)
		return false;
	delta = (_Y > rhs._Y) ? (_Y - rhs._Y) : (rhs._Y - _Y);
	if (Calculation::EPSf < delta)
		return false;

	return true;
}

template <> inline bool cm::Vec2D<double>::
operator==(const Vec2D<double>& rhs) const
{
	double delta = (_X > rhs._X) ? (_X - rhs._X) : (rhs._X - _X);
	if (Calculation::EPS < delta)
		return false;
	delta = (_Y > rhs._Y) ? (_Y - rhs._Y) : (rhs._Y - _Y);
	if (Calculation::EPS < delta)
		return false;

	return true;
}

template <typename T> inline bool cm::Vec2D<T>::
operator==(const Vec2D<T>& rhs) const
{
	return (_X == rhs._X) && (_Y == rhs._Y);
}

template <typename T> inline bool cm::Vec2D<T>::
operator!=(const Vec2D<T>& rhs) const
{
	return !(*this == rhs);
}

template <typename T> inline cm::Vec2D<T> cm::Vec2D<T>::
operator+(const Vec2D<T>& rhs) const
{
	return Vec2D(_X + rhs._X, _Y + rhs._Y);
}

template <typename T> inline cm::Vec2D<T> cm::Vec2D<T>::
operator-(const Vec2D<T>& rhs) const
{
	return Vec2D(_X - rhs._X, _Y - rhs._Y);
}

template <typename T> inline cm::Vec2D<T> cm::Vec2D<T>::
operator-() const
{
	return Vec2D(-_X, -_Y);
}

template <typename T> inline cm::Vec2D<T> cm::Vec2D<T>::
operator*(const T scalar) const
{
	return Vec2D(_X * scalar, _Y * scalar);
}

template <typename T> inline cm::Vec2D<T> cm::Vec2D<T>::
operator/(const T scalar) const
{
	return Vec2D(_X / scalar, _Y / scalar);
}

template <typename T> inline cm::Vec2D<T> & cm::Vec2D<T>::
operator=(const Vec2D<T>& rhs)
{
	_X = rhs._X;
	_Y = rhs._Y;
	return *this;
}

template <typename T> inline cm::Vec2D<T> & cm::Vec2D<T>::
operator+=(const Vec2D<T>& rhs)
{
	_X += rhs._X;
	_Y += rhs._Y;
	return *this;
}

template <typename T> inline cm::Vec2D<T> & cm::Vec2D<T>::
operator-=(const Vec2D<T>& rhs)
{
	_X -= rhs._X;
	_Y -= rhs._Y;
	return *this;
}

template <typename T> inline cm::Vec2D<T> & cm::Vec2D<T>::
operator*=(const T scalar)
{
	_X *= scalar;
	_Y *= scalar;
	return *this;
}

template <typename T> inline cm::Vec2D<T> & cm::Vec2D<T>::
operator/=(const T scalar)
{
	_X /= scalar;
	_Y /= scalar;
	return *this;
}


/*==========================================================================*/
/*	公有 方法																*/
/*==========================================================================*/

template <typename T> inline T cm::Vec2D<T>::
GetX() const
{
	return _X;
}

template <typename T> inline T cm::Vec2D<T>::
GetY() const
{
	return _Y;
}

template <typename T> inline void cm::Vec2D<T>::
SetX(const T x)
{
	_X = x;
}

template <typename T> inline void cm::Vec2D<T>::
SetY(const T y)
{
	_Y = y;
}

template<typename T> inline void cm::Vec2D<T>::
Set(const T x, const T y)
{
	_X = x;
	_Y = y;
}

template <typename T> inline cm::Vec2D<T>& cm::Vec2D<T>::
IncreaseX(const T x)
{
	_X += x;
	return *this;
}

template <typename T> inline cm::Vec2D<T>& cm::Vec2D<T>::
IncreaseY(const T y)
{
	_Y += y;
	return *this;
}

template <typename T> inline cm::Vec2D<T>& cm::Vec2D<T>::
Counterclockwise90()
{
	T bak(std::move(_X));
	_X = std::move(_Y);
	_Y = std::move(bak);
	_X = -_X;
	return *this;
}

template <typename T> inline cm::Vec2D<T>& cm::Vec2D<T>::
Clockwise90()
{
	T bak(std::move(_X));
	_X = std::move(_Y);
	_Y = std::move(bak);
	_Y = -_Y;
	return *this;
}

template <typename T> inline cm::Vec2D<T>& cm::Vec2D<T>::
Exchange()
{
	T bak(std::move(_Y));
	_Y = std::move(_X);
	_X = std::move(bak);
	return *this;
}

template <typename T> inline cm::Vec2D<T>& cm::Vec2D<T>::
Normalize()
{
	T scalar = Length();
	if (scalar > 0)
		(*this) /= scalar;
	return *this;
}

template <typename T> inline T cm::Vec2D<T>::
Length() const
{
	return static_cast<T>(sqrt(LengthSquared()));
}

template <typename T> inline T cm::Vec2D<T>::
LengthSquared() const
{
	return _X * _X + _Y* _Y;
}

template <typename T> inline T cm::Vec2D<T>::
Distance(const Vec2D<T>& rhs) const
{
	return static_cast<T>(sqrt(DistanceSquared(rhs)));
}

template <typename T> inline T cm::Vec2D<T>::
DistanceSquared(const Vec2D & rhs) const
{
	return (rhs._X - _X) * (rhs._X - _X) + (rhs._Y - _Y) * (rhs._Y - _Y);
}


template <typename T> inline T cm::Vec2D<T>::
cross(const Vec2D & rhs) const
{
	return _X * rhs._Y - rhs._X * _Y;
}

template <typename T> inline T cm::Vec2D<T>::
dot(const Vec2D & rhs) const
{
	return _X * rhs._X + _Y * rhs._Y;
}


template <typename T> inline double cm::Vec2D<T>::
Angle() const
{
	return atan2(_Y, _X);
}

template <typename T> inline double cm::Vec2D<T>::
AngleTo(const Vec2D<T>& rhs) const
{
	return atan2(rhs._Y - _Y, rhs._X - _X);
}


namespace cm {
	typedef Vec2D<float> Vec2Df;
	typedef Vec2D<int> Vec2Di;
	typedef Vec2D<unsigned int> Vec2Du;
}


