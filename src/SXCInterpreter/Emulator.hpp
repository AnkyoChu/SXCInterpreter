/*********************************************************************
 *
 *	@file		Emulator.hpp
 *	@brief		SXC 虚拟机
 *
 *
 *	Date        Name        Description
 *	08/09/15	MYLS		Creation.
 *
 *********************************************************************/
 
#pragma once

#include <memory>
namespace sxc {
	class Emulator;
}

/**
 *	\brief	SXC 虚拟机
 *			可以使用 doFile 来执行一段文件，或者
 *			使用 doString 执行单独的语句
 */
class sxc::Emulator
{
public:

	/**
	 *	\brief	默认的构造函数
	 */
	Emulator();

	/**
	 *	\brief	默认的析构函数
	 *			显式地写出，防止内联在头文件而无法删除 Impl
	 */
	~Emulator();

public:

	/**
	 *	\brief	执行一个文件
	 *	\param	filePath	被执行的文件的路径
	 *	\return				true 完成执行; false 执行失败
	 */
	bool doFile(const std::string & filePath);

	/**
	 *	\brief	默认的构造函数
	 *	\param	command		待执行的指令字符串
	 *	\return				true 完成执行; false 执行失败
	 */
	bool doString(const std::string & command);

private:

	struct Impl;
	std::unique_ptr<Impl> _Impl;			/**< 全部的成员变量 */
};







