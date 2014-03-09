PRONAME:= dposix
TARGET:= lib$(PRONAME)
PRE_DEFINED := 
BUILD_PATH := $(shell pwd)

INCLUDES := \
            ../ips/inc \
            ../memory/inc \
            ../socekt/inc \
			../stdio/inc \
			../system/inc \
            ../thread/inc \

SLIBS := dsystem dipc dmemory dsocket dstdio dthread

SLIBS := $(addprefix ../lib/lib, $(SLIBS))
SLIBS := $(addsuffix .a, $(SLIBS))

LIBS :=

LIBS_PATH := 

include ../../shared.mk
