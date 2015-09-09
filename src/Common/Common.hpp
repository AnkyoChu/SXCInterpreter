/*********************************************************************
 *	@file		BehaviorTree.h
 *	@brief		整合Common中的物件
 *				
 *
 *	Date        Name        Description
 *	23/04/15	MYLS		Creation.
 *
 *********************************************************************/

#pragma once

#if _MSC_VER > 1000
#ifdef _DEBUG
#pragma comment(lib, "../Debug/Common.lib")
#else
#pragma comment(lib, "../Release/Common.lib")
#endif
#endif



#include "Log.hpp"

#include "Singleton.hpp"

#include "AbsFactory.hpp"

#include "Calculation.hpp"

#include "AnyDataRef.hpp"

#include "Vec2D.hpp"

#include "RandNumGenerator.hpp"

#include "Timer.hpp"

#include "Event.hpp"

#include "EventListener.hpp"

#include "EventManager.hpp"

#include "State.hpp"

#include "StateMachine.hpp"


