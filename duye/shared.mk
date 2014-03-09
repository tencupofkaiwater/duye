INCLUDES += $(DUYE_ROOT) 	

SLIBS +=

LIBS += 

LIBS_PATH += 

#create dir
$(shell mkdir -p $(BUILD_PATH)/output/lib)
$(shell mkdir -p $(BUILD_PATH)/output/obj)

OBJDIR = $(BUILD_PATH)/output/obj
SRCDIR = $(BUILD_PATH)/src

RM := rm -f
PS=cpp
CC=g++
#CPPFLAGS = -Wall -g -O0 -Wall -march=i686
CPPFLAGS += -fPIC 
#CPPFLAGS += -MMD
CPPFLAGS += $(addprefix -I, $(INCLUDES))
CPPFLAGS += $(addprefix -D, $(PRE_DEFINED))

SOURCE += $(wildcard $(BUILD_PATH)/src/*.$(PS))

CPPSRCS := $(notdir $(SOURCE))
OBJS := $(patsubst %.$(PS), $(OBJDIR)/%.o, $(CPPSRCS))
DEPS := $(patsubst %.o, $(OBJDIR)/%.d, $(CPPSRCS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)), $(DEPS))

$(TARGET) : $(OBJS)
	$(CC) -shared $(OBJS) $(SLIBS) -o $(BUILD_PATH)/output/lib/$(TARGET).so $(addprefix -L, $(LIBS_PATH)) $(addprefix -l, $(LIBS)) 
	@echo "++++++++++Build $(TARGET).so Success++++++++++"
	$(MAKE) install

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	@echo $<, `more $<|wc -l` lines
	$(CC) -c $(CPPFLAGS) -o $@ $< 

.PHONY : all install clean cleanall 

install :
	@echo "start install $(TARGET).so ..."
	mkdir $(DUYE_LIB) -p
	cp -ax $(BUILD_PATH)/output/lib/$(TARGET).so $(DUYE_LIB)
	@echo 'install $(TARGET).so complete ...'

clean :
	$(RM) $(BUILD_PATH)/output -rf
	@#touch `find . -name "*.cpp" | xargs`

cleanall :
	$(RM) $(BUILD_PATH)/output -rf
	$(RM) $(DUYE_LIB)/$(TARGET).so -rf
	@#touch `find . -name "*.cpp" | xargs`

ifneq ($(MISSING_DEPS),)
$(MISSING_DEPS) :
	@$(RM) $(patsubst %.d, %.o, $@)
endif
