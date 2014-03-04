all: darithmetic dcomponent dlogger dposix dstl dutil ut_app

clean:
	$(MAKE) -C arithmetic clean
	$(MAKE) -C component clean
	$(MAKE) -C logger clean
	$(MAKE) -C posix clean
	$(MAKE) -C stl clean
	$(MAKE) -C util clean
	$(MAKE) -C ut clean

cleanall:
	$(MAKE) -C arithmetic cleanall
	$(MAKE) -C component cleanall
	$(MAKE) -C logger cleanall
	$(MAKE) -C posix cleanall
	$(MAKE) -C stl cleanall
	$(MAKE) -C util cleanall
	$(MAKE) -C ut cleanall
	rm $(DUYE_LIB) -rf
	rm $(DUYE_BIN) -rf

darithmetic:
	$(MAKE) -C arithmetic

dcomponent:
	$(MAKE) -C component	

dlogger:    
	$(MAKE) -C logger    

dposix:    
	$(MAKE) -C posix
	
dstl:    
	$(MAKE) -C stl

dutil:    
	$(MAKE) -C util

ut_app:
	$(MAKE) -C ut
