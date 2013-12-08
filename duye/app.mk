INCLUDES += $(DUYE_ROOT) 	

LIBS += 

LIBS_PATH += 

#create dir
$(shell mkdir -p $(BUILD_PATH)/output/bin)
$(shell mkdir -p $(BUILD_PATH)/output/obj)

OBJDIR = $(BUILD_PATH)/output/obj
SRCDIR = $(BUILD_PATH)/src

RM := rm -f
PS=cpp
CC=g++
CPPFLAGS = -Wall -g -O0 -Wall -march=i686
CPPFLAGS += -MMD
CPPFLAGS += $(addprefix -I, $(INCLUDES))
CPPFLAGS += $(addprefix -D, $(PRE_DEFINED))

SOURCE := $(wildcard $(BUILD_PATH)/src/*.$(PS))
CPPSRCS := $(notdir $(SOURCE))
OBJS := $(patsubst %.$(PS), $(OBJDIR)/%.o, $(CPPSRCS))
DEPS := $(patsubst %.o, $(OBJDIR)/%.d, $(CPPSRCS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)), $(DEPS))

$(TARGET) : $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(BUILD_PATH)/output/bin/$(TARGET) $(addprefix -l, $(LIBS)) $(addprefix -L, $(LIBS_PATH))
	@echo "++++++++++Build $(TARGET) Success++++++++++"
	$(MAKE) install

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	@echo $<, `more $<|wc -l` lines
	$(CC) -c $(CPPFLAGS) -o $@ $< 

.PHONY : all install clean 

install :
	@echo "start install $(TARGET) ..."
	mkdir $(DUYE_BIN) -p
	cp -ax $(BUILD_PATH)/output/bin/$(TARGET) $(DUYE_BIN)
	@echo 'install $(TARGET) complete ...'

clean :
	$(RM) $(BUILD_PATH)/output -rf
	#@touch `find . -name "*.cpp" | xargs`

cleanall :
	$(RM) $(BUILD_PATH)/output -rf
	$(RM) $(DUYE_BIN)/$(TARGET) -rf
	#@touch `find . -name "*.cpp" | xargs`

ifneq ($(MISSING_DEPS),)
$(MISSING_DEPS) :
	@$(RM) $(patsubst %.d, %.o, $@)
endif
