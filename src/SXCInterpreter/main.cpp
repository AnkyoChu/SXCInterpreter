/*********************************************************************
 *
 *	@file		main.cpp
 *	@brief		整个程序的入口
 *
 *
 *	Date        Name        Description
 *	08/09/15	MYLS		Creation.
 *
 *********************************************************************/

#include <string>
#include <Common/Common.hpp>
#include "Emulator.hpp"


////////////////////////////////////////////////////////////////////////////
//
//  Main program
//
////////////////////////////////////////////////////////////////////////////


void doFile(sxc::Emulator & emulator, const std::string & path) {
	emulator.doFile(path);
}

void doString(sxc::Emulator & emulator) {
	std::cout << "SXCi, version 0.0.1\n" ;
	std::cout << " >>>> ";

	std::string str;
	while (std::getline(std::cin, str)) {
		if (str == "exit")
			break;

		emulator.doString(str);
		std::cout << std::endl << " >>>> ";
	}

	std::cout << std::endl;
}


int main(int argc, char* argv[])
{
	sxc::Emulator emulator;

	if (argc > 1) {
		for (auto i = 1; i < argc; i++)
			doFile(emulator, argv[i]);
	} else {
		doString(emulator);
	}

	return 0;
}

