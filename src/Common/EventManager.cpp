/*********************************************************************
 *
 *	@file		EventManager.cpp
 *	@brief		事件管理器，用于分发各种事件
 *
 *
 *	Date        Name        Description
 *	21/05/15	MYLS		Creation.
 *
 *********************************************************************/

#include <typeinfo>
#include <algorithm>
#include "Event.hpp"
#include "EventListener.hpp"
#include "EventManager.hpp"


cm::EventManager::
EventManager()
	: _IsDispatching(false)
	, _EventQueue()
	, _ToBeAdded()
	, _ToBeDeleted()
	, _ListenerLists()
{}


void cm::EventManager::
clean()
{
	if (_IsDispatching == false) {
		_EventQueue.clear();
		_ToBeAdded.clear();
		_ToBeDeleted.clear();
		_ListenerLists.clear();
	} else {
		Log::Err(typeid(*this).name(), ":: cannot clean when dispatching!");
	}
}

void cm::EventManager::
sendEvent(cm::Event * eventObj)
{
	_EventQueue.push_back(std::shared_ptr<cm::Event>(eventObj));
}

void cm::EventManager::
sendEvent(std::shared_ptr<Event> eventObj)
{
	_EventQueue.push_back(eventObj);	
}

void cm::EventManager::
dispatch()
{
	/* [0]lock */
	_IsDispatching = true;

	/* [1]分发事件 */
	while (!_EventQueue.empty()) {
		auto frontEvent = _EventQueue.front();

		for (auto & it : _ListenerLists[typeid(*frontEvent).name()])
			it->trigger(frontEvent);

		_EventQueue.pop_front();
	}

	/* [2]检查是否有监听被取消 */
	while (!_ToBeDeleted.empty()) {
		auto & frontEvent = _ToBeDeleted.front();
		auto & key = frontEvent.first;
		auto & listener = frontEvent.second;

		auto iter = _ListenerLists.find(key);
		if(iter != _ListenerLists.end()) {
			if (listener != nullptr)
				iter->second.remove(listener);
			else 
				iter->second.clear();
		} else {
			Log::Err(typeid(*this).name(), ":: cannot delete, no such key:", key);
		}

		_ToBeDeleted.pop_front();
	}

	/* [3]检查是否有监听被加入 */
	while (!_ToBeAdded.empty()) {
		_ListenerLists[_ToBeAdded.front().first].push_back(_ToBeAdded.front().second);
		_ToBeAdded.pop_front();
	}

	/* [4]unlock */
	_IsDispatching = false;
}


void cm::EventManager::
addListener(std::string && index, ListenerBase * listener)
{
	if (_IsDispatching)
		_ToBeAdded.push_back(std::make_pair(index, listener));
	else
		_ListenerLists[index].push_back(listener);
}


void cm::EventManager::
deleteListener(std::string && key, ListenerBase * listener)
{
	if (_IsDispatching) {
		_ToBeDeleted.push_back(std::make_pair(key, listener));
	} else {
		auto iter = _ListenerLists.find(key);
		if(iter != _ListenerLists.end()) {
			if (listener != nullptr)
				iter->second.remove(listener);
			else 
				iter->second.clear();
		} else {
			Log::Err(typeid(*this).name(), ":: cannot delete, no such key:", key);
		}
	}
}



