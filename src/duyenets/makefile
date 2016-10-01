all:
	$(MAKE) -f module_shared.mk
	$(MAKE) -f module_static.mk
	@echo '===== lib code total lines '`find -name \*.[c,h]* | xargs cat | wc -l` '====='
	@cd test/file_server_test && $(MAKE)

clean:
	$(MAKE) -f module_shared.mk clean
	$(MAKE) -f module_static.mk clean
	@cd test/file_server_test && $(MAKE) clean

cleanall:
	$(MAKE) -f module_shared.mk cleanall
	$(MAKE) -f module_static.mk cleanall
	@cd test/file_server_test && $(MAKE) cleanall

install:
	$(MAKE) -f module_shared.mk install
	$(MAKE) -f module_static.mk install	
	@cd test/file_server_test && $(MAKE) install 

uninstall:
	$(MAKE) -f module_shared.mk uninstall
	$(MAKE) -f module_static.mk uninstall	
	@cd test/file_server_test && $(MAKE) uninstall 
