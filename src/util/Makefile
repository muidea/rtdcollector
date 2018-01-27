#
# Makefile
#
# Makefile for Poco Foundation
#

include $(PROJECT_BASE)/build/rules/global

objects = ascii atomicCounter bugcheck debugger errorHandler event exception fPEnvironment memoryStream mutex \
	numberFormatter numericString refCountedObject runnable signalHandler string thread threadLocal timespan timestamp 


SYSLIBS += -lpcre -lz
objects += $(pcre_utf8_objects)

objects += SyslogChannel

target         = util
target_version = $(LIBVERSION)
target_libs    =

include $(PROJECT_BASE)/build/rules/lib
