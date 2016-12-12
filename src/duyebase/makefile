all:
	$(MAKE) -f module_shared.mk
	@echo '===== lib code total lines '`find -name \*.[c,h]* | xargs cat | wc -l` '====='

clean:
	$(MAKE) -f module_shared.mk clean

cleanall:
	$(MAKE) -f module_shared.mk cleanall

install:
	$(MAKE) -f module_shared.mk install

uninstall:
	$(MAKE) -f module_shared.mk uninstall
