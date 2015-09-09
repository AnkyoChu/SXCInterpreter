/**********************************************************************
 *
 *	@file		StateMachine.cpp
 *	@brief		Implement of StateMachine.h.
 *
 *	Date        Name        Description
 *	11/11/14	MYLS		Creation.
 *
 *********************************************************************/

#include <typeinfo>
#include "State.hpp"
#include "StateMachine.hpp"


 /*==========================================================================*/
 /*	public Constructor \ Destructor											*/
 /*==========================================================================*/

cm::StateMachine::
StateMachine()
	: _States()
{}

cm::StateMachine::
~StateMachine()
{}

/*==========================================================================*/
/*	public Methods, Modify													*/
/*==========================================================================*/

void cm::StateMachine::
clean()
{
	if (!_States.empty()) {

		for (auto &it : _States) {
			it->onExit();
			delete it;
		}

		_States.erase(_States.begin(), _States.end());
	}
}

void cm::StateMachine::
push(State *pState)
{
	if (!pState) {
		return;
	}
	if (!_States.empty()) {
		_States.back()->pause();
	}
	_States.push_back(pState);
	_States.back()->onEnter();
}

void cm::StateMachine::
change(State *pState)
{
	if (!_States.empty()) {
		if (typeid(*_States.back()) == typeid(*pState)) {
			return;
		}

		_States.back()->onExit();
		delete _States.back();
		_States.pop_back();
	}

	pState->onEnter();
	_States.push_back(pState);
}

void cm::StateMachine::
pop()
{
	if (!_States.empty()) {
		_States.back()->onExit();
		delete _States.back();
		_States.pop_back();
	}

	_States.back()->resume();
}

cm::State * cm::StateMachine::
getRunningState()
{
	if (_States.empty())
		return nullptr;
	else 
		return _States.back();
}

/*==========================================================================*/
/*	public Methods, Query													*/
/*==========================================================================*/

bool cm::StateMachine::
empty()
{
	return _States.empty();
}


