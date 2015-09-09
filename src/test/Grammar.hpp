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

	Grammar() : Grammar::base_type(program, "program")
    {
        using namespace boost::spirit::qi;

		///////////////////////////////////////////////////////////////////
		/// 基础定义

		comment
			= ( "//"
				>> *(char_ - (eol | eoi))
					>> (eol | eoi)
			   )
			;

		keywords
			= lit("while") | "if" | "else" | "out" | "in" | "begin" | "end"
			;

        identifier 
			=	(  alpha 
				>> *(alnum)
				)
				- keywords
			;

		number
			= short_
			;

		string
			= '\"'
				>> *(char_ - '\"')
					>> '\"'
			;

		comparison
			= lit("<>") | "==" | "<=" | '<' | ">=" | '>'
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

		operand
			= ('(' >> operand >> ')')
			| assignment
			| identifier
			| number
			;

		term
			= factor
				>> *( ('*'	>> factor)
					| ('/'	>> factor)
					| ('%'	>> factor)
					)
			;

		factor
			= ('(' >> arithmetic >> ')')
			| operand
			| ('-' >> factor)
			| ('+' >> factor)
			;

		arithmetic
			= term
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
			| operand
			;
		
		assignment
			= left_value
				>> '='   
					>> *(  left_value >> '=')
						>> right_value
			;

		///////////////////////////////////////////////////////////////////
		/// 逻辑表达式

		logical
			=	('(' 
					>> logical 
						>> ')'
				)
			|	( right_value
					>> comparison
						>> right_value
				)
			;

		///////////////////////////////////////////////////////////////////
		/// 一般语句

		statement
			=	(	( command
					| string
					| right_value
					| eps
					)
					>> ';'
				)
			;

		loop
			= (lit("while") >> no_skip[ascii::space | comment])
				>> logical
					>> '{'
						>> -block
							>> '}'
			;

		condition
			= (lit("if") >> no_skip[ascii::space | comment])
				>> logical
					>> '{'
						>> -block
							>> '}'
			;

		block
			= +statement
			| loop
			| condition
			| (eps >> (eol | eoi))
			;
		
		///////////////////////////////////////////////////////////////////
		/// 程序块

		program
			= (lit("begin") >> no_skip[ascii::space | comment])
				>> *block
					>> lit("end")
						>> (eol | eoi)
			;

		BOOST_SPIRIT_DEBUG_NODE(loop);
		BOOST_SPIRIT_DEBUG_NODE(condition);
    }

	template <typename Iterator, typename ... T>
	using rule = boost::spirit::qi::rule<Iterator, T...>;

	rule<Iterator> comment;												
	rule<Iterator> keywords, identifier, number, string, comparison;	/**< 基础定义 */
	rule<Iterator, Skipper> argument, command;							/**< 带参数指令 */
	rule<Iterator, Skipper> operand, term, factor, arithmetic;			/**< 算术运算 */
	rule<Iterator, Skipper> left_value, right_value, assignment;		/**< 赋值运算 */
	rule<Iterator, Skipper> logical;									/**< 逻辑运算 */
	rule<Iterator, Skipper> statement;									/**< 一般语句 */
	rule<Iterator, Skipper> loop, condition, block;						/**< 语句块 */
	rule<Iterator, Skipper> program;									/**< 程序块 */
};



template<typename Iterator>
struct sxc::Skipper : public boost::spirit::qi::grammar<Iterator> 
{
    Skipper() : Skipper::base_type(skip, "SXC\'s Skipper")
	{
        using namespace boost::spirit::qi;

		comment
			= ( "//"
				>> *(char_ - (eol | eoi))
					>> (eol | eoi)
			   )
			;

        skip 
			= comment
			| ascii::space;
    }

	template <typename Iterator, typename ... T>
	using rule = boost::spirit::qi::rule<Iterator, T...>;

    rule<Iterator> skip;
	rule<Iterator> comment;
};



