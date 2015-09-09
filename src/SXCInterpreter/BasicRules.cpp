/*********************************************************************
 *
 *	@file		BasicRules.cpp
 *	@brief		定义的基础语法规则
 *
 *
 *	Date        Name        Description
 *	08/09/15	MYLS		Creation.
 *
 *********************************************************************/
 
#pragma once

#include <climits>
#include "BasicRules.hpp"

namespace sxc {
	typedef boost::spirit::classic::rule<> rule;
	using namespace boost::spirit::classic;
}


sxc::rule sxc::SPACE
	= sxc::space_p 
	| sxc::COMMENT
	;

sxc::rule sxc::KEYWORDS
	= sxc::str_p("while") | "if" | "else" | "out" | "in" | "begin" | "end"
	;

sxc::rule sxc::NUMBER
	= sxc::int_p
	;

sxc::rule sxc::STRING
	= sxc::ch_p('\"')
		>> *(sxc::anychar_p - '\"')
			>> '\"'
	;

sxc::rule sxc::COMMENT
	= sxc::str_p("//")
		>> *(sxc::anychar_p - (sxc::eol_p | sxc::end_p))
			>> (sxc::eol_p | sxc::end_p)
	;

sxc::rule sxc::IDENTIFIER
	=	(sxc::alpha_p 
		>> *(sxc::alnum_p)
		)
		- sxc::KEYWORDS
	;

sxc::rule sxc::ARGUMENT
	= sxc::IDENTIFIER
	| sxc::NUMBER
	| sxc::STRING
	;

sxc::rule sxc::COMMAND
	=	sxc::IDENTIFIER
		>> sxc::SPACE
			>> sxc::ARGUMENT
				>> *(!sxc::SPACE 
					>> ',' 
						>> !sxc::SPACE 
							>> sxc::ARGUMENT
					)
	;




sxc::rule sxc::TERM
    =   sxc::FACTOR
        >> *(   ('*' >> sxc::FACTOR)
            |   ('/' >> sxc::FACTOR)
            |   ('%' >> sxc::FACTOR)
            )
    ;

sxc::rule sxc::FACTOR
    =   sxc::NUMBER
	|	sxc::IDENTIFIER
    |   '(' >> sxc::ARITHMETIC >> ')'
    |   ('-' >> sxc::FACTOR)
    |   ('+' >> sxc::FACTOR)
    ;

sxc::rule sxc::ARITHMETIC
	=   sxc::TERM
		>> *(   ('+' >> sxc::TERM)
			|   ('-' >> sxc::TERM)
			)
	;









