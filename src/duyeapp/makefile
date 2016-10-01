MODULE:=duyetwo

VERSION:=

TARGET:=$(MODULE)

PRE_DEFINED:= 

BUILD_PATH:=$(shell pwd)

SUBDIRS:=./

INCLUDES:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) \
	$(INC_DIR)/duyebase \
	$(INC_DIR)/duyenets \
	$(INC_DIR)/duyedbclient

SRCDIRS:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) 

LIBS_PATH:=

LIBS:=duyebase duyenets duyedbclient

SLIBS:=

OUT_HEADS:=

CONF_DIR:=$(BUILD_PATH)/conf

include $(ROOT_DIR)/app.mk
