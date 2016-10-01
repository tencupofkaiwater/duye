MODULE:=duyedbserver

VERSION:=

TARGET:=$(MODULE)

PRE_DEFINED:= 

BUILD_PATH:=$(shell pwd)

SUBDIRS:=./

INCLUDES:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) \
	../serversdk \
	$(INC_DIR)/duyezero \
	$(INC_DIR)/duyeone

SRCDIRS:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) \
	../serversdk

LIBS_PATH:=

LIBS:=duyezero duyeone

SLIBS:=

OUT_HEADS:=

CONF_DIR:=$(BUILD_PATH)/conf

include $(ROOT_DIR)/app.mk
