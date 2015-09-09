/*********************************************************************
 *
 *	@file		AbsFactory.hpp
 *	@brief		AbsFactory Method 模板类
 *
 *
 *	Date		    Name			  Description
 *	23/04/15	    MYLS			  Creation.
 *	15/05/15	    MYLS			  支持Create方法增加参数.
 *
 *********************************************************************/

#pragma once

#include <map>
#include <string>
#include <functional>
#include <type_traits>
#include "Log.hpp"


namespace cm {
	template<class T, typename ... Types> class AbsFactory;
}


/**
 *	\brief  对象工厂模板类
 *			使用时 T 为被构造对象的基类，Types为构造需要的参数(可以不写)，例如：
 *			ObjectFactory : public AbsFactory<IObject, Type1, Type2, ...>
 */
template<class T, typename ... Types> class cm::AbsFactory {

public:

	/**
	 *	\brief  注册需要构造的对象
	 *
	 *	\param	type	注册类型时对应的字符串
	 *
	 */
	template<typename U> void Register(const std::string & type);

	/**
	 *	\brief  根据字符串名，产生一个对象
	 *
	 *	\param	type	注册类型时对应的字符串
	 *
	 *	\return	目标对象，如果没有注册这个对象，将会返回nullptr
	 */
	T * Create(const std::string & type, Types ... args) const;

	/**
	 *	\brief  根据字符串名，产生一个对象
	 *
	 *	\param	type	注册类型时对应的字符串
	 *
	 *	\return	目标对象，如果没有注册这个对象，将会返回nullptr
	 */
	T * Create(const std::string & type, Types ... args);

private:

	std::map<std::string, std::function<T *(Types ... args)>> _Creator;			/**< 构造器 */
	typename std::map<std::string, std::function<T *(Types ... args)>>::iterator _Iter;	/**< 在非 const 调用下使用，记录上次_Iter的位置 */
};


/*==========================================================================*/
/*	implement																*/
/*==========================================================================*/

template<class T, typename ... Types>
template<typename U> inline void cm::AbsFactory<T, Types...>::
Register(const std::string & type)
{
	static_assert(std::is_base_of<T, U>::value, "ERROR! T is not base of U.\n");

	if ((_Iter = _Creator.find(type)) == _Creator.end())
		_Creator.insert(std::make_pair(type, [](Types ... args) {return new U(args...); }));
	else
		Log::Err(typeid(*this).name(),":: Type < ", type, "> already exists!");
}


template<class T, typename ... Types> inline T * cm::AbsFactory<T, Types...>::
Create(const std::string & type, Types ... args) const
{
	auto creator = _Creator.find(type);

	if (creator == _Creator.end()) {
		Log::Err(typeid(*this).name(), ":: No Such Type < ", type, " >");
		return nullptr;
	}

	return creator->second(args...);
}

template<class T, typename ...Types> inline T * cm::AbsFactory<T, Types...>::
Create(const std::string & type, Types ...args)
{
	if (_Iter == _Creator.end() || _Iter->first != type)
		_Iter = _Creator.find(type);

	if (_Iter == _Creator.end()) {
		Log::Err(typeid(*this).name(), ":: No Such Type < ", type, " >");
		return nullptr;
	}

	return _Iter->second(args...);
}

