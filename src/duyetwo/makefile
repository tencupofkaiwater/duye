MODULE:=duyetwo

VERSION:=

TARGET:=$(MODULE)

PRE_DEFINED:= 

BUILD_PATH:=$(shell pwd)

SUBDIRS:=./

INCLUDES:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) \
	$(INS_INC_DIR)/duyezero \
	$(INS_INC_DIR)/duyeone \
	$(INS_INC_DIR)/duyedbclient

SRCDIRS:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) 

LIBS_PATH:=

LIBS:=duyezero duyeone duyedbclient

SLIBS:=

OUT_HEADS:=

CONF_DIR:=$(BUILD_PATH)/conf

include $(ROOT_DIR)/app.mk
