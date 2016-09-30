all:
	$(MAKE) -f module_shared.mk
	$(MAKE) -f module_static.mk
	@echo '===== lib code total lines '`find -name \*.[c,h]* | xargs cat | wc -l` '====='

clean:
	$(MAKE) -f module_shared.mk clean
	$(MAKE) -f module_static.mk clean

cleanall:
	$(MAKE) -f module_shared.mk cleanall
	$(MAKE) -f module_static.mk cleanall

install:
	$(MAKE) -f module_shared.mk install
	$(MAKE) -f module_static.mk install	

uninstall:
	$(MAKE) -f module_shared.mk uninstall
	$(MAKE) -f module_static.mk uninstall	
