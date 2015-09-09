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
#include <boost/spirit/include/qi.hpp>
#include <Common/Common.hpp>
#include "Grammar.hpp"

int main(void)
{

	std::cout << "SXCi, version 0.0.1\n" ;
	std::cout << "  >>>> ";

	std::string str;
	while (std::getline(std::cin, str)) {
		if (str == "exit")
			break;

		auto begin = str.begin();
		auto iter = begin;
		auto end = str.end();
		sxc::Grammar<decltype(iter)> g;
		sxc::Skipper<decltype(iter)> s;
		auto r = boost::spirit::qi::phrase_parse(iter, end, g, s);

		if (r && iter == end) {
			Log::Msg("Pass!");
		} else {
			Log::Msg(std::string(iter - begin, ' '), "^ error!");
		}

		std::cout << std::endl << "  >>>> ";
	}

	std::cout << std::endl;


	return 0;
}

