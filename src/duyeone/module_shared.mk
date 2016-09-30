MODULE:=duyeone

VERSION:=1.0.0

TARGET:=lib$(MODULE)

PRE_DEFINED:= 

BUILD_PATH:=$(shell pwd)

SUBDIRS:= \
	file_server \
	rpc_server

INCLUDES:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) \
	$(INS_INC_DIR)/duyezero

SRCDIRS:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir))

LIBS_PATH:=

LIBS:=duyezero 

SLIBS:=

OUT_HEADS:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)/*.h)

include $(ROOT_DIR)/shared.mk
