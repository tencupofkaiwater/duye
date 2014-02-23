all: dipc dmemory dstdio dthread dsocket target

clean:
	$(MAKE) -C ipc clean
	$(MAKE) -C memory clean
	$(MAKE) -C stdio clean
	$(MAKE) -C thread clean
	$(MAKE) -C posix clean
	$(MAKE) -C socket clean

cleanall:
	$(MAKE) -C ipc cleanall
	$(MAKE) -C memory cleanall
	$(MAKE) -C stdio cleanall
	$(MAKE) -C thread cleanall
	$(MAKE) -C posix cleanall
	$(MAKE) -C socket cleanall
	rm ./lib -rf

dipc:    
	$(MAKE) -C ipc

dmemory:    
	$(MAKE) -C memory 

dstdio:    
	$(MAKE) -C stdio

dthread:    
	$(MAKE) -C thread

dsocket:    
	$(MAKE) -C socket 

target:    
	$(MAKE) -C posix 
