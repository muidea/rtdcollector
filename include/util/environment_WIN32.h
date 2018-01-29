//
// Environment_WIN32.h
//
// Library: Foundation
// Package: Core
// Module:  Environment
//
// Definition of the EnvironmentImpl class for WIN32.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef __ENVIRONMENT_WIN32_H_1132__
#define __ENVIRONMENT_WIN32_H_1132__


#include "util.h"


namespace Util {


class Util_API EnvironmentImpl
{
public:
	typedef UInt8 NodeId[6]; /// Ethernet address.

	static std::string getImpl(const std::string& name);	
	static bool hasImpl(const std::string& name);	
	static void setImpl(const std::string& name, const std::string& value);
	static std::string osNameImpl();
	static std::string osDisplayNameImpl();
	static std::string osVersionImpl();
	static std::string osArchitectureImpl();
	static std::string nodeNameImpl();
	static void nodeIdImpl(NodeId& id);
	static unsigned processorCountImpl();
};


} // namespace Util


#endif // __ENVIRONMENT_WIN32_H_1132__
