/**********************************************************************
 *
 *	@file		Log.hpp
 *	@brief		һ���򵥵������ض���������࣬
 *
 *	Date        Name        Description
 *	02/09/15	MYLS		Creation.
 *
 *********************************************************************/

#include "Log.hpp"

void cm::Log::
OutputMsg()
{
	std::cout << std::endl;
}

void cm::Log::
OutputErr() 
{
	std::cerr << std::endl;
}

void cm::Log::
Switch(Type type, State state)
{
	switch (type)
	{
	case Type::MSG:
		IsMessageEnabled = (state == State::ON);
		break;
	case Type::ERR:
		IsErrorEnabled = (state == State::ON);
		break;
	default:
		break;
	}
}

bool cm::Log::IsMessageEnabled = true;
bool cm::Log::IsErrorEnabled = true;

