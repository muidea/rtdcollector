//
// RefCountedObject.cpp
//
// Library: Foundation
// Package: Core
// Module:  RefCountedObject
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "util/refCountedObject.h"


namespace Util {


RefCountedObject::RefCountedObject(): _counter(1)
{
}


RefCountedObject::~RefCountedObject()
{
}


} // namespace Util
