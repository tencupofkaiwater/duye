PRONAME:= dstl
VERSION:=1.0.0
TARGET:= lib$(PRONAME)
PRE_DEFINED := 
BUILD_PATH := $(shell pwd)

INCLUDES := \
    $(BUILD_PATH)/inc \
    ../arithmetic/inc \
    ../component/inc \
    ../vector/inc
    
SLIBS := darithmetic dcomponent dvector

SLIBS:=$(addprefix ../lib/lib, $(SLIBS))
SLIBS:=$(addsuffix .a, $(SLIBS))

LIBS:=

LIBS_PATH:= 

include ../../shared.mk
