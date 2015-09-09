/*********************************************************************
 *	@file		Event.hpp
 *	@brief		事件的基类
 *
 *
 *	Date        Name        Description
 *	21/05/15	MYLS		Creation.
 *
 *********************************************************************/

#pragma once

namespace cm {
	class Event;
}


/**
 *	\brief 事件基类
 */
class cm::Event {

public:

	/**
	 *	\brief 虚 析构函数
	 */
	virtual ~Event() = 0 {};
};





