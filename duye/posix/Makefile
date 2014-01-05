all: dipc dstdio dthread target

clean:
	$(MAKE) -C ipc clean
	$(MAKE) -C stdio clean
	$(MAKE) -C thread clean
	$(MAKE) -C posix clean

cleanall:
	$(MAKE) -C ipc cleanall
	$(MAKE) -C stdio cleanall
	$(MAKE) -C thread cleanall
	$(MAKE) -C posix cleanall
	rm ./lib -rf

dipc:    
	$(MAKE) -C ipc

dstdio:    
	$(MAKE) -C stdio

dthread:    
	$(MAKE) -C thread

target:    
	$(MAKE) -C posix 
