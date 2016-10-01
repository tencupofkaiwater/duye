MODULE:=duyedbserver

VERSION:=1.0.0

TARGET:=lib$(MODULE)

PRE_DEFINED:= 

BUILD_PATH:=$(shell pwd)

SUBDIRS:= ./ 

INCLUDES:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) \
	$(INC_DIR)/duyezero

SRCDIRS:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir))

LIBS_PATH:=

LIBS:= 

SLIBS:=$(LIB_DIR)/libduyezero.a

OUT_HEADS:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)/*.h)

include $(ROOT_DIR)/static.mk
