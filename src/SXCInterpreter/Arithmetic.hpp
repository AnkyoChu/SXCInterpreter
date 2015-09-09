/*********************************************************************
 *
 *	@file		Arithmetic.hpp
 *	@brief		
 *
 *
 *	Date        Name        Description
 *	08/09/15	MYLS		Creation.
 *
 *********************************************************************/
 
#pragma once

#include <vector>
#include <functional>
#include <boost/spirit/include/classic_core.hpp>
#include <Common/Log.hpp>
#include "VariableTable.hpp"
#include "Identifier.hpp"
#include "BasicRules.hpp"
namespace sxc {
	class Arithmetic;
}


class sxc::Arithmetic : public boost::spirit::classic::grammar<sxc::Arithmetic>
{
public:

	template <typename ScannerT> class definition;
	template <typename ScannerT> friend class definition;

	Arithmetic(VariableTable & variables);

	int operator()() const;

private:

	VariableTable & _Variables;
	std::vector<int> _Operand;
};




template <typename ScannerT> class sxc::Arithmetic::definition {
	
public:

	definition(sxc::Arithmetic const & outer);

	boost::spirit::classic::rule<ScannerT> const & start() const;

private:

	int check_and_pop();
	
private:

	void push(const int val);
	void read(char const*, char const*);
	void do_neg(char const*, char const*);
	void do_add(char const*, char const*);
	void do_sub(char const*, char const*);
	void do_mul(char const*, char const*);
	void do_div(char const*, char const*);
	void do_mod(char const*, char const*);

private:

	VariableTable & _Variables;
	std::vector<int> & _Stack;
	boost::spirit::classic::rule<ScannerT> expression;
	boost::spirit::classic::rule<ScannerT> term;
	boost::spirit::classic::rule<ScannerT> factor;
	boost::spirit::classic::rule<ScannerT> test;
	Identifier identifier;
};


/*********************************************************************
 *	implement sxc::Arithmetic
 *********************************************************************/

inline sxc::Arithmetic::
Arithmetic(VariableTable & variables)
	: _Variables(variables)
{}

inline int sxc::Arithmetic::
operator()() const
{
	if (_Operand.empty()) {
		Log::Err(typeid(*this).name(), ":: Unexpected error! No result!");
		return 0;
	} else 
		return _Operand.back();
}

/*********************************************************************
 *	implement sxc::Arithmetic::definition
 *********************************************************************/

template <typename ScannerT> inline sxc::Arithmetic::definition<ScannerT>::
definition(sxc::Arithmetic const & outer)
	: _Stack(const_cast<sxc::Arithmetic &>(outer)._Operand)
	, _Variables(const_cast<sxc::Arithmetic &>(outer)._Variables)
{
	/* 初始化其它事物 */
	using std::placeholders::_1;
	using std::placeholders::_2;
	auto push	= std::bind(&definition::push,   this, _1);
	auto read	= std::bind(&definition::read,   this, _1, _2);
	auto op_neg = std::bind(&definition::do_neg, this, _1, _2);
	auto op_add = std::bind(&definition::do_add, this, _1, _2);
	auto op_sub = std::bind(&definition::do_sub, this, _1, _2);
	auto op_mul = std::bind(&definition::do_mul, this, _1, _2);
	auto op_div = std::bind(&definition::do_div, this, _1, _2);
	auto op_mod = std::bind(&definition::do_mod, this, _1, _2);
	_Stack.clear();
	_Stack.reserve(10);


	/* 初始化语法规则 */
	using namespace boost::spirit::classic;

	expression
		=   term
			>> *(   ('+' >> term)[op_add]
				|   ('-' >> term)[op_sub]
				)
		;

    term
        =   factor
            >> *(   ('*' >> factor)[op_mul]
                |   ('/' >> factor)[op_div]
                |   ('%' >> factor)[op_mod]
                )
        ;

    factor
        =   int_p[push]
		|	IDENTIFIER[read]
        |   '(' >> expression >> ')'
        |   ('-' >> factor)[op_neg]
        |   ('+' >> factor)
        ;

	test
		= sxc::ARITHMETIC
		;

}


template <typename ScannerT> inline boost::spirit::classic::rule<ScannerT> const & sxc::Arithmetic::definition<ScannerT>::
start() const 
{ 
	return expression; 
}


/* 自定义 */

template<typename ScannerT> inline int sxc::Arithmetic::definition<ScannerT>::
check_and_pop()
{
	if (_Stack.size() < 2) {
		/* 正常情况下是不会执行这一步的 */
		Log::Err(typeid(*this).name(), ":: Unexpected error! Cannot match the operand!");
		return 0;
	}
	
	auto ret = _Stack.back();
	_Stack.pop_back();
	return ret;
}


/* 用于四则运算的回调函数 */

template<typename ScannerT> inline void sxc::Arithmetic::definition<ScannerT>::
push(const int val)
{
	_Stack.push_back(val);
}

template<typename ScannerT> inline void sxc::Arithmetic::definition<ScannerT>::
read(char const * begin, char const * end)
{
	_Stack.push_back(_Variables[std::move(std::string(begin, end))]);
}

template<typename ScannerT> inline void sxc::Arithmetic::definition<ScannerT>::
do_neg(char const *, char const *)
{
	if (_Stack.empty())
		Log::Err(typeid(*this).name(), ":: Cannot match the operand!");
	else
		_Stack.back() = -_Stack.back();
}

template<typename ScannerT> inline void sxc::Arithmetic::definition<ScannerT>::
do_add(char const *, char const *)
{
	auto snd = check_and_pop();
	_Stack.back() += snd;
}

template<typename ScannerT> inline void sxc::Arithmetic::definition<ScannerT>::
do_sub(char const *, char const *)
{
	auto snd = check_and_pop();
	_Stack.back() -= snd;
}

template<typename ScannerT> inline void sxc::Arithmetic::definition<ScannerT>::
do_mul(char const *, char const *)
{
	auto snd = check_and_pop();
	_Stack.back() *= snd;
}

template<typename ScannerT> inline void sxc::Arithmetic::definition<ScannerT>::
do_div(char const *, char const *)
{
	auto snd = check_and_pop();
	_Stack.back() /= snd;
}

template<typename ScannerT> inline void sxc::Arithmetic::definition<ScannerT>::
do_mod(char const *, char const *)
{
	auto snd = check_and_pop();
	_Stack.back() %= snd;
}



