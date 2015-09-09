/*********************************************************************
 *
 *	@file		Identifier.hpp
 *	@brief		标识符，可能的变量名称
 *
 *
 *	Date        Name        Description
 *	08/09/15	MYLS		Creation.
 *
 *********************************************************************/
 
#pragma once

#include <boost/spirit/include/classic_core.hpp>
namespace sxc {
	class Identifier;
}


class sxc::Identifier : public boost::spirit::classic::grammar<sxc::Identifier>
{
public:
	template <typename ScannerT> class definition;
	template <typename ScannerT> friend class definition;
};




template <typename ScannerT> class sxc::Identifier::definition {
	
public:

	definition(sxc::Identifier const & outer);

	boost::spirit::classic::rule<ScannerT> const & start() const;

private:

	boost::spirit::classic::rule<ScannerT> identifier;
};




/*********************************************************************
 *	implement sxc::Identifier::definition
 *********************************************************************/

template <typename ScannerT> inline sxc::Identifier::definition<ScannerT>::
definition(sxc::Identifier const & outer)
{
	/* 语法规则 */
	using namespace boost::spirit::classic;

    identifier
        =   (alpha_p >> *(alnum_p))
		;
}

template <typename ScannerT> inline boost::spirit::classic::rule<ScannerT> const & sxc::Identifier::definition<ScannerT>::
start() const 
{ 
	return identifier; 
}





