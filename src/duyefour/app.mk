#third party library include
INCLUDES+=

#third party static library
SLIBS+= 

#third party shared library
LIBS+=pthread dl

#third party shared library path
LIBS_PATH+=$(LIB_DIR)

#predefined
PRE_DEFINED+=

#create dir
OUTPUT:=$(BUILD_PATH)/output
$(shell mkdir -p $(OUTPUT)/bin)
$(shell mkdir -p $(OUTPUT)/obj)

OBJDIR:=$(BUILD_PATH)/output/obj
VPATH:=$(SRCDIRS)

PS:=cpp
CC:=g++
CPPFLAGS+=-Wall -g -O0 -std=c++11
CPPFLAGS+=$(addprefix -I, $(INCLUDES))
CPPFLAGS+=$(addprefix -D, $(PRE_DEFINED))

SOURCE:=$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.$(PS)))

CPPSRCS:=$(notdir $(SOURCE))
OBJS:=$(patsubst %.$(PS), $(OBJDIR)/%.o, $(CPPSRCS))

#shared library flags
LIB_FLAGS:=$(addprefix -l, $(LIBS)) $(addprefix -L, $(LIBS_PATH))

#static library flags
SLIB_FLAGS:=-Wl,--whole-archive $(SLIBS) -Wl,--no-whole-archive

TARGET_FILE:=$(OUTPUT)/bin/$(TARGET)

ifdef VERSION
	TARGET_FILE:=$(OUTPUT)/bin/$(TARGET).$(VERSION)
endif

all:$(TARGET)

$(TARGET):$(OBJS)
	@$(CC) $(CPPFLAGS) $(OBJS) -o $(TARGET_FILE) $(SLIB_FLAGS) $(LIB_FLAGS)
	@mkdir -p $(BIN_DIR)    
	@cp -ax $(OUTPUT)/bin/$(TARGET) $(BIN_DIR)
	@echo '===== test code total lines '`find -name \*.[c,h]* | xargs cat | wc -l` '====='
	@echo "Build `basename $(TARGET_FILE)` Success"

$(OBJDIR)/%.o:%.$(PS)
	@echo $(CC) `basename $<`, `more $<|wc -l` lines
	@$(CC) -c $(CPPFLAGS) -o $@ $< 

.PHONY:clean uninstall
#ignore error
.IGNORE:clean cleanall install uninstall 

clean:
	rm $(OUTPUT) -rf
ifneq ($(SOURCE),)	
	@touch -a $(SOURCE)
endif

cleanall:clean
	rm $(RELEASE_DIR) -rf

install:uninstall
	@echo "Start Install `basename $(TARGET_FILE)`"
ifneq ($(CONF_DIR),)
	@mkdir -p $(INS_CONF_DIR)/$(MODULE)
	@cp -ax $(CONF_DIR)/* $(INS_CONF_DIR)/$(MODULE)
endif
	@mkdir -p $(INS_BIN_DIR)    
	@cp -ax $(BIN_DIR)/$(TARGET) $(INS_BIN_DIR)
	@echo "Install `basename $(TARGET_FILE)` to $(INS_BIN_DIR) Complete"

uninstall:
	@echo "Start Uninstall `basename $(TARGET_FILE)`"
ifneq ($(CONF_DIR),)
	@rm -rf $(INS_CONF_DIR)/$(MODULE)
endif
	@rm -rf $(INS_BIN_DIR)/$(TARGET)
	@echo "Uninstall `basename $(TARGET_FILE)` Complete"

