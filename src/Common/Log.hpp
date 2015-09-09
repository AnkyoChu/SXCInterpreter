/**********************************************************************
 *
 *	@file		Log.hpp
 *	@brief		一个简单的用于重定向输出的类，
 *
 *	Date        Name        Description
 *	02/09/15	MYLS		Creation.
 *
 *********************************************************************/

#pragma once

#include <iostream>
#include <type_traits>

namespace cm {
	class Log;
}

/**
 *	\brief	用于输出消息的一个类
 */
class cm::Log {

public:

	/**
	 *	\brief	输出错误信息
	 *	\param	被打印的信息，各个参数会被空格隔开
	 */
	template<typename... Types> static inline void Msg(Types...args);
	
	/**
	 *	\brief	输出消息
	 *	\param	被打印的信息，各个参数会被空格隔开
	 */
	template<typename... Types> static inline void Err(Types...args);

	enum struct Type : size_t;
	enum struct State : size_t;
	/**
	 *	\brief	切换 消息 \ 错误信息 是否输出
	 *	\param	type	类型，分为{消息, 错误信息}
	 *	\param	state	开启或者关闭
	 */
	static void Switch(Type type, State state);

private:

	/**
	 *	\brief	空的输出消息的函数
	 */
	static void OutputMsg();

	/**
	 *	\brief	空的输出错误的函数
	 */
	static void OutputErr();

	/**
	 *	\brief	实际的输出消息的函数
	 *	\param	被输出的数据，支持基本数据类型
	 */
	template<typename T, typename... Types> static inline void OutputMsg(const T & value, Types...args);
	
	/**
	 *	\brief	实际的输出错误的函数
	 *	\param	被输出的数据，支持基本数据类型
	 */
	template<typename T, typename... Types> static inline void OutputErr(const T & value, Types...args);


	static bool IsMessageEnabled;		/**< 是否会输出消息 */
	static bool IsErrorEnabled;			/**< 是否会输出错误 */

};


/*********************************************************************
 *	enum
 *********************************************************************/

enum struct cm::Log::Type : size_t {
	MSG,
	ERR,
};

enum struct cm::Log::State : size_t {
	ON,
	OFF,
};


/*********************************************************************
 *	implement
 *********************************************************************/

template<typename T, typename ...Types> inline void cm::Log::
OutputMsg(const T & value, Types...args)
{
	std::cout << ' ' << value;
	OutputMsg(args...);
}

template<typename T, typename ...Types> inline void cm::Log::
OutputErr(const T & value, Types...args)
{
	std::cerr << ' ' << value;
	OutputErr(args...);
}


template<typename ...Types> inline void cm::Log::
Msg(Types...args)
{
	if (cm::Log::IsMessageEnabled) {
		std::cout << "[MSG]";
		OutputMsg(args...);
	}
}

template<typename ...Types> inline void cm::Log::
Err(Types...args)
{
	if (cm::Log::IsErrorEnabled) {
		std::cerr << "[ERR]";
		OutputErr(args...);
	}
}


using cm::Log;

