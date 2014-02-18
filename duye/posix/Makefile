all: dipc dstdio dthread dsocket target

clean:
	$(MAKE) -C ipc clean
	$(MAKE) -C stdio clean
	$(MAKE) -C thread clean
	$(MAKE) -C posix clean
	$(MAKE) -C societ clean

cleanall:
	$(MAKE) -C ipc cleanall
	$(MAKE) -C stdio cleanall
	$(MAKE) -C thread cleanall
	$(MAKE) -C posix cleanall
	$(MAKE) -C socket cleanall
	rm ./lib -rf

dipc:    
	$(MAKE) -C ipc

dstdio:    
	$(MAKE) -C stdio

dthread:    
	$(MAKE) -C thread

dsocket:    
	$(MAKE) -C socket 

target:    
	$(MAKE) -C posix 
