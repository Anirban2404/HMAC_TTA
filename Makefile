
ifndef src
    src := $(CURDIR)
endif

NET_IF       := ../../src/linux/tte_net_if.o
MAIN_MODULE  := ../../src/linux/tte_main_module.o


MODULE_NAME2 := Node1
CFG1 := Node1_config.o
APP_MODULES1  := $(CFG1) $(MAIN_MODULE) $(NET_IF)

MODULE_NAME2 := Node2
CFG3 := Node2_config.o
APP_MODULES3  := $(CFG3) $(MAIN_MODULE) $(NET_IF)


KERNEL_VERSION     := $(shell uname -r)
KERNEL_BUILD_DIR   := /lib/modules/$(KERNEL_VERSION)/build
TTE_OBJ_DIR        := ../../release/release_ibx
TTE_INCLUDE_DIR    := $(TTE_OBJ_DIR)/include
API_INCLUDE_DIR    := ../../../tte-api
VERBOSE            := 0

TTE_SRC_DIR        := ../../../tte-protocol-layer/src

TTE_PL_LIB   := $(TTE_OBJ_DIR)/libpl_ibx.a

EXTRA_TTE_MODULES := $(FS) $(ATTANSIC_DRV)

ifeq ($(KERNELRELEASE),)
    ### Normal Make running

# version of the application
svn_revision := 0

CC     ?= gcc
CFLAGS += -ggdb -Wall
CFLAGS += -DSVN_REVISION=$(svn_revision)
CFLAGS += -I../common
CFLAGS += -DASSERT
CFLAGS += -DLOG_ERRORS
#CFLAGS += -DLOG_DEBUG
#CFLAGS += -DLOG_CALLS
#CFLAGS += -DSEND_DUMMY_FRAMES
LDFLAGS += -lavutil -lavformat -lavcodec -lz -lm


.PHONY: all
all: modules

.PHONY: modules
modules:
	make -C $(KERNEL_BUILD_DIR) ARCH=x86 M=$$PWD SRCROOT=$$PWD modules V=$(VERBOSE)

.PHONY: install
install: modules
	make -C $(KERNEL_BUILD_DIR) ARCH=x86 M=$$PWD SRCROOT=$$PWD modules_install V=$(VERBOSE)

.PHONY: clean
clean:
	make -C $(KERNEL_BUILD_DIR) ARCH=x86 M=$$PWD SRCROOT=$$PWD clean V=$(VERBOSE)
	rm -f *~ server *.o ../common/*.o *.ko

.PHONY: upload
upload: 
	smbclient //10.100.10.111/inbox -Ugrillinger

else
    ### KBuild running

#EXTRA_CFLAGS += -DLOG_CALLS
#EXTRA_CFLAGS += -DTTE_DEBUG
#EXTRA_CFLAGS += -DTTE_DEBUG_VERBOSE
#EXTRA_CFLAGS += -DDEBUG_ETH_DRIVER
#EXTRA_CFLAGS += -DPRINT_TIMING
EXTRA_CFLAGS += -DTTE_VERBOSE_ERRORS
EXTRA_CFLAGS += -DSLOPPY_DEADLINES
EXTRA_CFLAGS += -DMANDATORY_ETH_LOCKS
#EXTRA_CFLAGS += -DCHECK_ETH_BUF_OWNER
EXTRA_CFLAGS += -DENABLE_NET_IF
#EXTRA_CFLAGS += -DENABLE_FS_IF
EXTRA_CFLAGS += -DCHECK_LINK_LOSS
EXTRA_CFLAGS += -Wall -Wno-unknown-pragmas # -Werror 
EXTRA_CFLAGS += -DOS_ARCH_LINUX -DTARGET_ATOM_LINUX
EXTRA_CFLAGS += -I$(src)/$(TTE_INCLUDE_DIR) -I$(src)/$(API_INCLUDE_DIR)

obj-m   += $(MODULE_NAME1).o
$(MODULE_NAME1)-objs := $(APP_MODULES1) $(TTE_PL_LIB)

#obj-m   += $(MODULE_NAME2).o
#$(MODULE_NAME2)-objs := $(APP_MODULES2) $(TTE_PL_LIB)

obj-m   += $(MODULE_NAME3).o
$(MODULE_NAME3)-objs := $(APP_MODULES3) $(TTE_PL_LIB)

obj-m += SHA1_Crypto.o
obj-m += SHA2_Crypto.o
obj-m += SHA3_sponge.o
endif

