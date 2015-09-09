/*********************************************************************
 *
 *	@file		Grammar.hpp
 *	@brief		定义的基础语法规则，用于语法检查
 *
 *
 *	Date        Name        Description
 *	09/09/15	MYLS		Creation.
 *
 *********************************************************************/
 
#pragma once
#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
//namespace boost {
//	namespace spirit {
//		namespace qi {
//			template <typename Iterator, typename T1, typename T2, typename T3, typename T4> struct rule;
//		}
//	}
//}
namespace sxc {
	template<typename Iterator> struct Skipper;
	template <typename Iterator, typename Skipper> struct Grammar;
}



template <typename Iterator, typename Skipper = sxc::Skipper<Iterator>>
struct sxc::Grammar: public boost::spirit::qi::grammar<Iterator, Skipper>
{

	Grammar() : Grammar::base_type(assignment, "assignment")
    {
        using namespace boost::spirit::qi;

		///////////////////////////////////////////////////////////////////
		/// 基础定义

		keywords
			= lit("while") | "if" | "else" | "out" | "in" | "begin" | "end"
			;

        identifier 
			=	(alpha 
				>> *(alnum)
				)
				- keywords
			;

		number
			= short_
			;

		string
			= char_('\"')
				>> *(char_ - '\"')
					>> '\"'
			;

		///////////////////////////////////////////////////////////////////
		/// 指令

		argument
			= identifier
			| number
			| string
			;

		command
			= identifier
				>> (argument % ',')
			;

		///////////////////////////////////////////////////////////////////
		/// 算术运算
		
		result
			= ('(' >> result >> ')')
			| identifier
			| assignment
			| number
			;

		term
			=	factor
				>> *( ('*'	>> factor)
					| ('/'	>> factor)
					| ('%'	>> factor)
					)
			;

		factor
			=	('(' >> arithmetic >> ')')
			|	result
			|   ('-' >> factor)
			|   ('+' >> factor)
			;

		arithmetic
			=   term
				>> *(   ('+' >> term)
					|   ('-' >> term)
					)
			;

		///////////////////////////////////////////////////////////////////
		/// 赋值运算

		left_value
			= ('(' >> left_value >> ')')
			| identifier
			;

		right_value
			= ('(' >> right_value >> ')')
			| arithmetic
			| result
			;
		
		assignment
			= left_value
				>> '='   
					>> *(  left_value >> '=')
						>> right_value
			;
		
		BOOST_SPIRIT_DEBUG_NODE(assignment);
    }

	template <typename Iterator, typename ... T>
	using rule = boost::spirit::qi::rule<Iterator, T...>;

	rule<Iterator> keywords, identifier, number, string;

	rule<Iterator, Skipper> argument, command;
	rule<Iterator, Skipper> result, term, factor, arithmetic;
	rule<Iterator, Skipper> left_value, right_value, assignment;
};



template<typename Iterator>
struct sxc::Skipper : public boost::spirit::qi::grammar<Iterator> 
{
    Skipper() : Skipper::base_type(skip, "SXC\'s Skipper")
	{
        using namespace boost::spirit::qi;

		comment
			= lit("//")
				>> *(char_ - eol)
					>> eol
			;

        skip 
			= ascii::space 
			| comment;
    }

	template <typename Iterator, typename ... T>
	using rule = boost::spirit::qi::rule<Iterator, T...>;

    rule<Iterator> skip;
	rule<Iterator> comment;
};



