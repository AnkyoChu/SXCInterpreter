/**********************************************************************
 *
 *	@file		Log.hpp
 *	@brief		һ���򵥵������ض���������࣬
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
 *	\brief	���������Ϣ��һ����
 */
class cm::Log {

public:

	/**
	 *	\brief	���������Ϣ
	 *	\param	����ӡ����Ϣ�����������ᱻ�ո����
	 */
	template<typename... Types> static inline void Msg(Types...args);
	
	/**
	 *	\brief	�����Ϣ
	 *	\param	����ӡ����Ϣ�����������ᱻ�ո����
	 */
	template<typename... Types> static inline void Err(Types...args);

	enum struct Type : size_t;
	enum struct State : size_t;
	/**
	 *	\brief	�л� ��Ϣ \ ������Ϣ �Ƿ����
	 *	\param	type	���ͣ���Ϊ{��Ϣ, ������Ϣ}
	 *	\param	state	�������߹ر�
	 */
	static void Switch(Type type, State state);

private:

	/**
	 *	\brief	�յ������Ϣ�ĺ���
	 */
	static void OutputMsg();

	/**
	 *	\brief	�յ��������ĺ���
	 */
	static void OutputErr();

	/**
	 *	\brief	ʵ�ʵ������Ϣ�ĺ���
	 *	\param	����������ݣ�֧�ֻ�����������
	 */
	template<typename T, typename... Types> static inline void OutputMsg(const T & value, Types...args);
	
	/**
	 *	\brief	ʵ�ʵ��������ĺ���
	 *	\param	����������ݣ�֧�ֻ�����������
	 */
	template<typename T, typename... Types> static inline void OutputErr(const T & value, Types...args);


	static bool IsMessageEnabled;		/**< �Ƿ�������Ϣ */
	static bool IsErrorEnabled;			/**< �Ƿ��������� */

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

