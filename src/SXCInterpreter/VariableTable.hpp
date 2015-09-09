/*********************************************************************
 *
 *	@file		VariableTable.hpp
 *	@brief		
 *
 *
 *	Date        Name        Description
 *	08/09/15	MYLS		Creation.
 *
 *********************************************************************/
 
#pragma once

#include <vector>
#include <string>
#include <unordered_map>


namespace sxc {
	class VariableTable;
}


class sxc::VariableTable
{
public:

	VariableTable();

public:

	int & operator[](const std::string & key);
	
	int & operator[](std::string && key);
	
	const int & operator[](const std::string & key) const;

	void push();

	void pop();

private:

	std::vector<std::unordered_map<std::string, int>> _Tables;
	// std::vector<std::unordered_map<std::string, boost::any>> a;
};







