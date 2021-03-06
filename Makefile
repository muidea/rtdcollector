#
# Makefile
#
# The global Makefile, port from poco
#

sinclude config.make

ifndef PROJECT_BASE
$(warning WARNING: PROJECT_BASE is not defined. Assuming current directory.)
export PROJECT_BASE=$(shell pwd)
endif
ifdef PROJECT_VERBOSE
$(info PROJECT_BASE           = $(PROJECT_BASE))
endif

ifndef PROJECT_BUILD
export PROJECT_BUILD=$(PROJECT_BASE)
endif
ifdef PROJECT_VERBOSE
$(info PROJECT_BUILD          = $(PROJECT_BUILD))
endif

#
# Determine OS
#
PROJECT_HOST_OSNAME = $(shell uname)
ifeq ($(findstring CYGWIN,$(PROJECT_HOST_OSNAME)),CYGWIN)
PROJECT_HOST_OSNAME = CYGWIN
endif

PROJECT_HOST_OSARCH ?= $(subst /,-,$(shell uname -m | tr ' ' _))
ifdef PROJECT_VERBOSE
$(info PROJECT_HOST_OSARCH    = $(PROJECT_HOST_OSARCH))
endif

#
# If PROJECT_CONFIG is not set, use the OS name as configuration name
#
ifndef PROJECT_CONFIG
PROJECT_CONFIG = $(PROJECT_HOST_OSNAME)
endif
ifdef PROJECT_VERBOSE
$(info PROJECT_CONFIG         = $(PROJECT_CONFIG))
endif

#
# Include System Specific Settings
#
include $(PROJECT_BASE)/build/config/$(PROJECT_CONFIG)

#
# Determine operating system
#
ifndef PROJECT_TARGET_OSNAME
OSNAME   := $(PROJECT_HOST_OSNAME)
else
OSNAME   := $(PROJECT_TARGET_OSNAME)
endif
ifdef PROJECT_VERBOSE
$(info OSNAME              = $(OSNAME))
endif

ifndef PROJECT_TARGET_OSARCH
OSARCH   := $(PROJECT_HOST_OSARCH)
else
OSARCH   := $(PROJECT_TARGET_OSARCH)
endif
ifdef PROJECT_VERBOSE
$(info OSARCH              = $(OSARCH))
endif

.PHONY: all libexecs cppunit tests samples cleans clean distclean install

all: libexecs tests samples

INSTALLDIR = $(DESTDIR)$(PROJECT_PREFIX)
COMPONENTS = tinyxml2 util rtdcollector

install: libexecs
	mkdir -p $(INSTALLDIR)/include/rtdcollector
	mkdir -p $(INSTALLDIR)/lib
	mkdir -p $(INSTALLDIR)/bin
	for comp in $(filter-out $(foreach f,$(OMIT),$f%),$(COMPONENTS)) ; do \
		if [ -d "$(PROJECT_BASE)/$$comp/include" ] ; then \
			cp -Rf $(PROJECT_BASE)/$$comp/include/* $(INSTALLDIR)/include/ ; \
		fi ; \
		if [ -d "$(PROJECT_BUILD)/$$comp/bin" ] ; then \
			find $(PROJECT_BUILD)/$$comp/bin -perm -700 -type f -exec cp -f {} $(INSTALLDIR)/bin \; ; \
		fi ; \
	done

ifeq ($(OSNAME), CYGWIN)
	find $(PROJECT_BUILD)/lib/$(OSNAME)/$(OSARCH) -name "cyg*" -type f -exec cp -f  {} $(INSTALLDIR)/bin \;
	find $(PROJECT_BUILD)/lib/$(OSNAME)/$(OSARCH) -name "cyg*" -type l -exec cp -Rf {} $(INSTALLDIR)/bin \;
endif
	find $(PROJECT_BUILD)/lib/$(OSNAME)/$(OSARCH) -name "lib*" -type f -exec cp -f  {} $(INSTALLDIR)/lib \;
	find $(PROJECT_BUILD)/lib/$(OSNAME)/$(OSARCH) -name "lib*" -type l -exec cp -Rf {} $(INSTALLDIR)/lib \;

libexecs =  dbusmessageTest-libexec dbusWrapperSend-libexec dbusWrapperRecv-libexec dbusSend-libexec dbusRecv-libexec rtdTest-libexec dbuswrapper-libexec dbusmessage-libexec rtdprotocol-libexec rtdcollector-libexec tinyxml2-libexec util-libexec
tests    =  
samples  =  
cleans   = dbusmessageTest-clean dbusWrapperSend-clean dbusWrapperRecv-clean dbusSend-clean dbusRecv-clean rtdTest-clean dbuswrapper-clean dbusmessage-clean rtdprotocol-clean rtdcollector-clean tinyxml2-clean util-clean

.PHONY: $(libexecs)
.PHONY: $(tests)
.PHONY: $(samples)
.PHONY: $(cleans)

libexecs: $(filter-out $(foreach f,$(OMIT),$f%),$(libexecs))
tests: $(filter-out $(foreach f,$(OMIT),$f%),$(tests))
samples: $(filter-out $(foreach f,$(OMIT),$f%),$(samples))
cleans: $(filter-out $(foreach f,$(OMIT),$f%),$(cleans))

rtdTest-libexec: tinyxml2-libexec util-libexec rtdprotocol-libexec dbuswrapper-libexec dbusmessage-libexec rtdcollector-libexec
	$(MAKE) -C $(PROJECT_BASE)/test/rtdTest

rtdTest-clean:
	$(MAKE) -C $(PROJECT_BASE)/test/rtdTest clean

rtdcollector-libexec: tinyxml2-libexec util-libexec rtdprotocol-libexec dbusmessage-libexec dbuswrapper-libexec
	$(MAKE) -C $(PROJECT_BASE)/src/rtdcollector

rtdcollector-clean:
	$(MAKE) -C $(PROJECT_BASE)/src/rtdcollector clean

dbuswrapper-libexec: util-libexec
	$(MAKE) -C $(PROJECT_BASE)/src/dbuswrapper

dbuswrapper-clean:
	$(MAKE) -C $(PROJECT_BASE)/src/dbuswrapper clean

dbusmessage-libexec: util-libexec tinyxml2-libexec
	$(MAKE) -C $(PROJECT_BASE)/src/dbusmessage

dbusmessage-clean:
	$(MAKE) -C $(PROJECT_BASE)/src/dbusmessage clean

rtdprotocol-libexec: 
	$(MAKE) -C $(PROJECT_BASE)/src/rtdprotocol

rtdprotocol-clean:
	$(MAKE) -C $(PROJECT_BASE)/src/rtdprotocol clean

tinyxml2-libexec: 
	$(MAKE) -C $(PROJECT_BASE)/src/tinyxml2

tinyxml2-clean:
	$(MAKE) -C $(PROJECT_BASE)/src/tinyxml2 clean

util-libexec: 
	$(MAKE) -C $(PROJECT_BASE)/src/util

util-clean:
	$(MAKE) -C $(PROJECT_BASE)/src/util clean

dbusSend-libexec: 
	$(MAKE) -C $(PROJECT_BASE)/test/dbusSend

dbusSend-clean:
	$(MAKE) -C $(PROJECT_BASE)/test/dbusSend clean

dbusRecv-libexec: 
	$(MAKE) -C $(PROJECT_BASE)/test/dbusRecv

dbusRecv-clean:
	$(MAKE) -C $(PROJECT_BASE)/test/dbusRecv clean

dbusWrapperSend-libexec: dbuswrapper-libexec
	$(MAKE) -C $(PROJECT_BASE)/test/dbusWrapperSend

dbusWrapperSend-clean:
	$(MAKE) -C $(PROJECT_BASE)/test/dbusWrapperSend clean

dbusWrapperRecv-libexec: dbuswrapper-libexec
	$(MAKE) -C $(PROJECT_BASE)/test/dbusWrapperRecv

dbusWrapperRecv-clean:
	$(MAKE) -C $(PROJECT_BASE)/test/dbusWrapperRecv clean

dbusmessageTest-libexec: dbusmessage-libexec
	$(MAKE) -C $(PROJECT_BASE)/test/dbusmessageTest

dbusmessageTest-clean:
	$(MAKE) -C $(PROJECT_BASE)/test/dbusmessageTest clean

clean: cleans

distclean:
	rm -rf $(PROJECT_BUILD)/lib
	find $(PROJECT_BUILD) -name obj -type d -print0 | xargs -0 rm -rf
	find $(PROJECT_BUILD) -name .dep -type d -print0 | xargs -0 rm -rf
	find $(PROJECT_BUILD) -name bin -type d -print0 | xargs -0 rm -rf
