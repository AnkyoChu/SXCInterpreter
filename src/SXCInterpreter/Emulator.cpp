/*********************************************************************
 *
 *	@file		Emulator.cpp
 *	@brief		class Emulator 的具体实现
 *
 *
 *	Date        Name        Description
 *	08/09/15	MYLS		Creation.
 *
 *********************************************************************/

#include <fstream>
#include <iomanip>
#include <boost/spirit/include/qi.hpp>
#include "VariableTable.hpp"
#include "Arithmetic.hpp"
#include "Emulator.hpp"



/*********************************************************************
 *	member variables
 *********************************************************************/

struct sxc::Emulator::Impl{
	std::fstream _File;
	VariableTable _Variables;
};


/*********************************************************************
 *	implement
 *********************************************************************/

bool sxc::Emulator::
doFile(const std::string & filePath)
{
	// TODO: finish
	return false;
}


bool sxc::Emulator::
doString(const std::string & cmd)
{
	sxc::Arithmetic calc(_Impl->_Variables);

	boost::spirit::classic::parse_info<> info;
	auto r = calc >> *sxc::SPACE;
	info = boost::spirit::classic::parse(cmd.c_str(), r, sxc::SPACE);

	if (info.full) {
		Log::Msg(calc());
	} else {
		Log::Msg(std::setw(info.stop - cmd.c_str()), "^ error!");
	}

	//do {
	//	if (!info.hit) {
	//		Log::Msg(std::setw(info.stop - cmd.c_str()), "^ error!");
	//	} else if (!info.full) {
	//		Log::Msg(calc());
	//		info = boost::spirit::classic::parse(info.stop, calc >> sxc::SPACE >> sxc::STRING >> !sxc::SPACE, sxc::SPACE);
	//	}
	//	
	//	if (info.full) {
	//		Log::Msg(calc());
	//	}

	//} while (!info.full && info.hit);

	return false;
}




sxc::Emulator::Emulator() : _Impl(std::make_unique<Impl>()) {}
sxc::Emulator::~Emulator(){}







