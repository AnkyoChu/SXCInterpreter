/*********************************************************************
 *
 *	@file		VariableTable.cpp
 *	@brief		
 *
 *
 *	Date        Name        Description
 *	08/09/15	MYLS		Creation.
 *
 *********************************************************************/

#include <Common/Log.hpp>
#include "VariableTable.hpp"



sxc::VariableTable::
VariableTable()
	: _Tables()
{
	// TODO: add to .ini
	_Tables.reserve(5);
}


int & sxc::VariableTable::
operator[] (const std::string & key)
{
	if (_Tables.empty()) {
		Log::Err(typeid(*this).name(), ":: VariableTable is empty!", "Cannot find", key, ". A new table has been created!");
		push();
		return _Tables.back()[key];
	}

	for (auto & table : _Tables) {
		auto iter = table.find(key);
		if (iter != table.end())
			return iter->second;
	}

	return _Tables.back()[key];
}

int & sxc::VariableTable::
operator[](std::string && key)
{
	if (_Tables.empty()) {
		Log::Err(typeid(*this).name(), ":: VariableTable is empty!", "Cannot find", key, ". A new table has been created!");
		_Tables.emplace_back();
		return _Tables.back()[std::move(key)];
	}

	for (auto & table : _Tables) {
		auto iter = table.find(key);
		if (iter != table.end())
			return iter->second;
	}

	return _Tables.back()[std::move(key)];
}

const int & sxc::VariableTable::
operator[](const std::string & key) const
{
	for (auto & table : _Tables) {
		auto iter = table.find(key);
		if (iter != table.end())
			return iter->second;
	}

	static const int ret = 0;
	return ret;
}


void sxc::VariableTable::
push()
{
	_Tables.emplace_back();
}

void sxc::VariableTable::
pop()
{
	if (_Tables.empty())
		Log::Err(typeid(*this).name(), ":: VariableTable is empty and cannot pop!");
	else 
		_Tables.pop_back();
}
