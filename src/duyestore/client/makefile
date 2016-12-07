MODULE:=duyedbclient

VERSION:=

TARGET:=$(MODULE)

PRE_DEFINED:= 

BUILD_PATH:=$(shell pwd)

SUBDIRS:=./

INCLUDES:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) \
	../clientsdk \
	$(INC_DIR)/duyebase \
	$(INC_DIR)/duyenets

SRCDIRS:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) \
	../clientsdk

LIBS_PATH:=

LIBS:=duyebase duyenets

SLIBS:=

OUT_HEADS:=

include $(ROOT_DIR)/app.mk
