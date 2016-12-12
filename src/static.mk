#third party library include
INCLUDES+=
	
#third party static library
SLIBS+=

#third party shared library
LIBS+=

#third party shared library path
LIBS_PATH+=

#predefined
PRE_DEFINED+=

#output head
OUT_HEADS+=

#create dir
OUTPUT:=$(BUILD_PATH)/output
$(shell mkdir -p $(OUTPUT)/lib)
$(shell mkdir -p $(OUTPUT)/obj)

OBJDIR:=$(OUTPUT)/obj
VPATH:=$(SRCDIRS)

PS:=cpp
CC:=g++
CPPFLAGS+=-Wall -O0 -g -std=c++11
CPPFLAGS+=-fPIC
CPPFLAGS+=$(addprefix -I, $(INCLUDES))
CPPFLAGS+=$(addprefix -D, $(PRE_DEFINED))

SOURCE:=$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.$(PS)))

CPPSRCS:=$(notdir $(SOURCE))
OBJS:=$(patsubst %.$(PS), $(OBJDIR)/%.o, $(CPPSRCS))

LIB_FLAGS:=$(addprefix -l, $(LIBS)) $(addprefix -L, $(LIBS_PATH))
SLIB_FLAGS:=$(SLIBS)

TARGET_FILE:=$(OUTPUT)/lib/$(TARGET).a

ifdef VERSION
	TARGET_FILE:=$(OUTPUT)/lib/$(TARGET).a.$(VERSION)
endif

all:$(TARGET) 

$(TARGET):$(OBJS)
	@ar rcs $(TARGET_FILE) $(OBJS) $(SLIB_FLAGS) $(LIB_FLAGS)
	@mkdir -p $(INC_DIR)  
	@mkdir -p $(LIB_DIR)     
	@cp -f $(TARGET_FILE) $(LIB_DIR)
	@cd $(LIB_DIR) && ln -snf $(TARGET).a.$(VERSION) $(TARGET).a
	@echo "Build $(TARGET_FILE) Success"

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
	rm -rf $(RELEASE_DIR)/include/$(MODULE)
	rm -f $(RELEASE_DIR)/lib/$(TARGET).so*

install:uninstall
ifdef VERSION
	@echo "Start Install `basename $(TARGET_FILE)`"
	@mkdir -p $(INS_LIB_DIR)     
	@mkdir -p $(INS_LIB_DIR)/$(MODULE)     
	@cp -f $(LIB_DIR)/$(TARGET).a.$(VERSION) $(INS_LIB_DIR)/$(MODULE)
	@cd $(INS_LIB_DIR) && ln -snf $(MODULE)/$(TARGET).a.$(VERSION) $(TARGET).a
	@echo "Install `basename $(TARGET_FILE)` to $(INS_LIB_DIR)/$(MODULE) Complete"
endif

uninstall:
	@echo "Start uninstall `basename $(TARGET_FILE)`"
	@rm -f $(INS_LIB_DIR)/$(TARGET).a*
	@echo "Install `basename $(TARGET_FILE)` to $(LIB_DIR) Complete"
	@echo "Uninstall `basename $(TARGET_FILE)` to $(INS_LIB_DIR)/$(MODULE) Complete"
