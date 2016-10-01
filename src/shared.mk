#third party library include
INCLUDES+=

#third party static library
SLIBS+=

#third party shared library
LIBS+=

#third party shared library path
LIBS_PATH+=$(LIB_DIR)

#predefined
PRE_DEFINED+=

#output head files
OUT_HEADS+=

#create dir
OUTPUT:=$(BUILD_PATH)/output
$(shell mkdir -p $(OUTPUT)/lib)
$(shell mkdir -p $(OUTPUT)/obj)

OBJDIR:=$(OUTPUT)/obj
VPATH:=$(SRCDIRS)

PS:=cpp
CC:=g++
CPPFLAGS+=-Wall -ggdb -O0 -std=c++11
CPPFLAGS+=-fPIC
CPPFLAGS+=$(addprefix -I, $(INCLUDES))
CPPFLAGS+=$(addprefix -D, $(PRE_DEFINED))

SOURCE:=$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.$(PS)))

CPPSRCS:=$(notdir $(SOURCE))
OBJS:=$(patsubst %.$(PS), $(OBJDIR)/%.o, $(CPPSRCS))

LIB_FLAGS:=$(addprefix -l, $(LIBS)) $(addprefix -L, $(LIBS_PATH))
SLIB_FLAGS:=-Wl,--whole-archive $(SLIBS) -Wl,--no-whole-archive

TARGET_FILE:=$(OUTPUT)/lib/$(TARGET).so
ifdef VERSION
	TARGET_FILE:=$(OUTPUT)/lib/$(TARGET).so.$(VERSION)
endif

all:$(TARGET) 

$(TARGET):$(OBJS)
	@$(CC) -shared -o $(TARGET_FILE) $(OBJS) $(SLIB_FLAGS) $(LIB_FLAGS)
	@mkdir -p $(INC_DIR)  
	@mkdir -p $(INC_DIR)/$(MODULE) 
	@mkdir -p $(LIB_DIR)     
	@cp -f $(TARGET_FILE) $(LIB_DIR)
	@cd $(LIB_DIR) && ln -snf $(TARGET).so.$(VERSION) $(TARGET).so
	@cp -f $(OUT_HEADS) $(INC_DIR)/$(MODULE)
	@echo 'Build $(TARGET_FILE) Success'

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
ifdef VERSION
	@echo "Start Install `basename $(TARGET_FILE)`"
	@mkdir -p $(INS_INC_DIR)/$(MODULE)  
	@mkdir -p $(INS_LIB_DIR)/$(MODULE)    
	@cp -f $(INC_DIR)/* $(INS_INC_DIR)/$(MODULE)
	@cp -f $(LIB_DIR)/$(TARGET).so.$(VERSION) $(INS_LIB_DIR)/$(MODULE)
	@cd $(INS_LIB_DIR) && ln -snf $(MODULE)/$(TARGET).so.$(VERSION) $(TARGET).so
	@echo "Install `basename $(TARGET_FILE)` to $(INS_LIB_DIR)/$(MODULE) Complete"
endif	

uninstall:
	@echo "Start uninstall `basename $(TARGET_FILE)`"
	@rm -rf $(INS_INC_DIR)/$(MODULE)  
	@rm -rf $(INS_LIB_DIR)/$(MODULE)    
	@rm -f $(INS_LIB_DIR)/$(TARGET).so*
	@echo "Uninstall `basename $(TARGET_FILE)` to $(INS_LIB_DIR)/$(MODULE) Complete"
