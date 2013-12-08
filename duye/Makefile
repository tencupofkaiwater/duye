all: dposix dstl dutil

clean:
	$(MAKE) -C stl clean
	$(MAKE) -C posix clean
	$(MAKE) -C util clean

cleanall:
	$(MAKE) -C stl cleanall
	$(MAKE) -C posix cleanall
	$(MAKE) -C util cleanall
	rm ./lib -rf

dstl:    
	$(MAKE) -C stl

dposix:    
	$(MAKE) -C posix

dutil:    
	$(MAKE) -C util

