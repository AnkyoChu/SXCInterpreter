/*********************************************************************
 *
 *	@file		BasicRules.hpp
 *	@brief		定义的基础语法规则
 *
 *
 *	Date        Name        Description
 *	08/09/15	MYLS		Creation.
 *
 *********************************************************************/
 
#pragma once
#include <boost/spirit/include/classic_core.hpp>

namespace boost {
	namespace spirit {
		namespace classic {
			template <typename T0 = nil_t, typename T1 = nil_t, typename T2 = nil_t> class rule;
		}
	}
}

namespace sxc {
	extern boost::spirit::classic::rule<> KEYWORDS;
	extern boost::spirit::classic::rule<> COMMENT;
	extern boost::spirit::classic::rule<> SPACE;
	extern boost::spirit::classic::rule<> NUMBER;
	extern boost::spirit::classic::rule<> STRING;
	extern boost::spirit::classic::rule<> IDENTIFIER;
	extern boost::spirit::classic::rule<> ARGUMENT;
	extern boost::spirit::classic::rule<> COMMAND;

	extern boost::spirit::classic::rule<> TERM;
	extern boost::spirit::classic::rule<> FACTOR;
	extern boost::spirit::classic::rule<> ARITHMETIC;
}


namespace sxc {
	struct grammer {
		;
	};
}






