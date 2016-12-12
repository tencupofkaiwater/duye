MODULE:=duyenets

VERSION:=1.0.0

TARGET:=lib$(MODULE)

PRE_DEFINED:= 

BUILD_PATH:=$(shell pwd)

SUBDIRS:= \
	http_server 

INCLUDES:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) \
	$(INC_DIR)/duyebase

SRCDIRS:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir))

LIBS_PATH:=

LIBS:=duyebase 

SLIBS:=

OUT_HEADS:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)/*.h)

include $(ROOT_DIR)/shared.mk
