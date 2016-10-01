all:
	@$(MAKE) -C server 
	@$(MAKE) -C serversdk 
	@$(MAKE) -C client 
	@$(MAKE) -C clientsdk 
	@echo '===== lib code total lines '`find -name \*.[c,h]* | xargs cat | wc -l` '====='

clean:
	@cd server && $(MAKE) clean 
	@cd serversdk && $(MAKE) clean 
	@cd client && $(MAKE) clean 
	@cd clientsdk && $(MAKE) clean 

cleanall:
	@cd server && $(MAKE) cleanall 
	@cd serversdk && $(MAKE) cleanall 
	@cd client && $(MAKE) cleanall
	@cd clientsdk && $(MAKE) cleanall 

install:
	@cd server && $(MAKE) install 
	@cd serversdk && $(MAKE) install 
	@cd client && $(MAKE) install
	@cd clientsdk && $(MAKE) install

uninstall:
	@cd server && $(MAKE) uninstall 
	@cd serversdk && $(MAKE) uninstall 
	@cd client && $(MAKE) uninstall
	@cd clientsdk && $(MAKE) uninstall
