MODULE:=duyedbclient

VERSION:=

TARGET:=$(MODULE)

PRE_DEFINED:= 

BUILD_PATH:=$(shell pwd)

SUBDIRS:=./

INCLUDES:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) \
	../clientsdk \
	$(INC_DIR)/duyezero \
	$(INC_DIR)/duyeone

SRCDIRS:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) \
	../clientsdk

LIBS_PATH:=

LIBS:=duyezero duyeone

SLIBS:=

OUT_HEADS:=

include $(ROOT_DIR)/app.mk
