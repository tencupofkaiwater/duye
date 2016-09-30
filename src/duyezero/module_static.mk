MODULE:=duyezero

VERSION:=1.0.0

TARGET:=lib$(MODULE)

PRE_DEFINED:= 

BUILD_PATH:=$(shell pwd)

SUBDIRS:= \
	system \
	logger \
	utils \
	public \
	net

INCLUDES:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) 

SRCDIRS:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir))

LIBS_PATH:= 

LIBS:= 

SLIBS:=

OUT_HEADS:=$(wildcard $(BUILD_PATH)/*.h)

include $(ROOT_DIR)/static.mk
