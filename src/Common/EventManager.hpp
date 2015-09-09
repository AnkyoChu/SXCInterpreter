/*********************************************************************
 *
 *	@file		EventManager.hpp
 *	@brief		事件管理器，用于分发各种事件
 *
 *
 *	Date        Name        Description
 *	21/05/15	MYLS		Creation.
 *
 *********************************************************************/

#pragma once

#include <list>
#include <string>
#include <memory>
#include <type_traits>
#include <unordered_map>
#include "Log.hpp"

namespace cm {
	class Event;
	class ListenerBase;
	template<class T> class EventListener;
	class EventManager;
}


/**
 *	\brief	事件管理者，负责分发事件
 */
class cm::EventManager {

public:

	/**
	 *	\brief	默认构造函数
	 */
	EventManager();

public:

	/**
	 *	\brief	清除所有事件，释放资源
	 */
	void clean();

	/**
	 *	\brief	分发事件，执行事件对应listener的操作
	 */
	void dispatch();

	/**
	 *	\brief 发送一个事件
	 *
	 *	\param	eventObj	被发送的事件
	 */
	void sendEvent(Event * eventObj);

	/**
	 *	\brief 发送一个事件[智能指针版本重载]
	 *
	 *	\param	eventObj	被发送的事件
	 */
	void sendEvent(std::shared_ptr<Event> eventObj);

	/**
	 *	\brief	注册一个listener<T>，T为被监听事件的类型
	 *
	 *	\param	listener	事件监听者
	 */
	template<typename T> EventManager & registerListener(EventListener<T> * listener);

	/**
	 *	\brief	清除一个listener<T>，T为被监听事件的类型
	 *
	 *	\param	listener	事件监听者，如果为nullptr，将会清除那个事件的所有监听者
	 */
	template<typename T> EventManager & removeListener(EventListener<T> * listener = nullptr);

private:

	/**
	 *	\brief	添加一个listener，将会被registerListener调用
	 *
	 *	\param	type		事件类型的名字
	 *	\param	listener	事件监听者
	 */
	void addListener(std::string && type, ListenerBase * listener);

	/**
	 *	\brief	删除listener，将会被removeListener调用
	 *
	 *	\param	type		事件类型的名字
	 *	\param	listener	事件监听者
	 */
	void deleteListener(std::string && type, ListenerBase * listener);

private:

	bool _IsDispatching;											/**< 判断当前是否正在处理事件 */
	std::list<std::shared_ptr<Event>> _EventQueue;					/**< 正在分发的事件 */
	std::list<std::pair<std::string, ListenerBase *>> _ToBeAdded;	/**< 将要被增加的事件 */
	std::list<std::pair<std::string, ListenerBase *>> _ToBeDeleted;	/**< 将要被删除的事件 */
	std::unordered_map<std::string, std::list<ListenerBase *>> _ListenerLists;	/**< 事件监听者的列表 */
};


/*********************************************************************
 *	implement
 *********************************************************************/

template<typename EventType> inline cm::EventManager & cm::EventManager::
registerListener(cm::EventListener<EventType> * listener)
{
	if (listener != nullptr && dynamic_cast<const cm::EventListener<EventType> *>(listener))
		addListener(std::string(typeid(EventType).name()), listener);
	else
		Log::Err(typeid(*this).name(), ":: unsupported listener type!");

	return *this;
}

template<typename EventType> inline cm::EventManager & cm::EventManager::
removeListener(cm::EventListener<EventType> * listener)
{
	if (listener == nullptr || dynamic_cast<const cm::EventListener<EventType> *>(listener))
		deleteListener(std::string(typeid(EventType).name()), listener);
	return *this;
}


