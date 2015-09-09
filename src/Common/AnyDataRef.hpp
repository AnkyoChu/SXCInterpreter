/*********************************************************************
 *	@file		AnyDataRef.hpp
 *	@brief		Class AnyDataRef, ref to any data type.
 *
 *
 *	Date        Name        Description
 *	01/03/15	MYLS		Creation.
 *
 *********************************************************************/

#pragma once

#include <cassert>

namespace cm {
	class Data;
	template<typename T> class AnyDataRef;
}


class cm::Data {

public:

	virtual ~Data();

public:

	template<typename T> T& GetRealData();

	template<typename T> const T& GetRealData() const;

protected:

	Data() = default;

};


template<typename T> class cm::AnyDataRef : public Data {

public:

	AnyDataRef(T & data);

	~AnyDataRef();

public:

	T& GetRealData();

	const T& GetRealData() const;

	AnyDataRef& operator =(T& data);

private:

	void set(T& data);

private:

	T* _RealData;
};


/*********************************************************************
 *	Data
 *********************************************************************/

inline cm::Data::
~Data()
{}

template<typename T> T& cm::Data::
GetRealData()
{
	auto ret = dynamic_cast<AnyDataRef<T>*>(this);
	assert(ret);
	return ret->GetRealData();
}

template<typename T> const T& cm::Data::
GetRealData() const
{
	auto ret = dynamic_cast<const AnyDataRef<T>*>(this);
	assert(ret);
	return ret->GetRealData();
}

/*********************************************************************
 *	AnyDataRef
 *********************************************************************/

template<typename T> cm::AnyDataRef<T>::
AnyDataRef(T& data)
	: Data()
	, _RealData(&data)
{}

template<typename T> cm::AnyDataRef<T>::
~AnyDataRef()
{}


template<typename T> T & cm::AnyDataRef<T>::
GetRealData()
{
	return *_RealData;
}

template<typename T> const T & cm::AnyDataRef<T>::
GetRealData() const
{
	return *_RealData;
}

template<typename T> cm::AnyDataRef<T> & cm::AnyDataRef<T>::
operator= (T& data)
{
	set(data);
	return *this;
}


