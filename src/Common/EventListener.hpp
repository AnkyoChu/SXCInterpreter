/*********************************************************************
 *	@file		EventListener.hpp
 *	@brief		事件的监听者
 *
 *
 *	Date        Name        Description
 *	21/05/15	MYLS		Creation.
 *
 *********************************************************************/
#pragma once

#include <memory>
#include <type_traits>
#include "Log.hpp"

namespace cm {
	class Event;
	class ListenerBase;
	template<class T> class EventListener;
}


/**
 *	\brief 事件监听者 基类
 */
class cm::ListenerBase {

	friend class EventManager;

public:

	/**
	 *	\brief  基类的虚析构函数
	 */
	virtual ~ListenerBase() = 0 {}

private:

	/**
	 *	\brief  将会检查并调用监听者的对应的操作
	 *	\param	eventObject	触发的事件
	 */
	inline virtual void trigger(std::shared_ptr<Event> eventObject) = 0;

};


/**
 *	\brief 事件监听者
 */
template<class T> class cm::EventListener : public ListenerBase {

public:

	/**
	 *	\brief  基类的虚析构函数
	 */
	virtual ~EventListener() {};

private:

	/**
	 *	\brief 执行监听者对应操作
	 *	\param	eventObject	被触发的事件
	 */
	inline virtual void process(const T & eventObject) = 0;

	/**
	 *	\brief 将会检查并调用监听者的对应的操作
	 *	\param	eventObject	触发的事件
	 */
	inline void trigger(std::shared_ptr<Event> eventObject) override;
};


/*********************************************************************
 *	EventListener
 *********************************************************************/

template<class T> void cm::EventListener<T>::
trigger(std::shared_ptr<Event> eventObject)
{
	static_assert(std::is_base_of<Event, T>::value, "EventListener:: T is not a Event");
	static_assert(std::is_convertible<T, Event>::value, "EventListener:: Cannot convert T to Event");
	auto theEvent = std::dynamic_pointer_cast<T>(eventObject);
	if (theEvent)
		process(*theEvent);
	else
		Log::Err(typeid(*this).name(), ":: dynamic_cast filed!");
}


