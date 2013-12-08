all: dposix dstl dutil

clean:
	$(MAKE) -C stl clean
	$(MAKE) -C posix clean
	$(MAKE) -C util clean

cleanall:
	$(MAKE) -C stl cleanall
	$(MAKE) -C posix cleanall
	$(MAKE) -C util cleanall
	rm $(DUYE_LIB) -rf
	rm $(DUYE_BIN) -rf

dstl:    
	$(MAKE) -C stl

dposix:    
	$(MAKE) -C posix

dutil:    
	$(MAKE) -C util

