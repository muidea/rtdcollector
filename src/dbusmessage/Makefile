#
# Makefile
#
# Makefile for DBusMessage
#

include $(PROJECT_BASE)/build/rules/global

INCLUDE += -I /usr/local/dbus-1.12.2/include/dbus-1.0 -I /usr/local/lib/dbus-1.0/include
LIBRARY += -L/usr/local/lib
SYSLIBS += -ldbus-1

objects = rtdconfig rtddata rtdevent

target         = dbusmessage
target_version = $(LIBVERSION)
target_libs    =

include $(PROJECT_BASE)/build/rules/lib
