all: darithmetic dcomponent dvector dstllib

clean:
	$(MAKE) -C arithmetic clean
	$(MAKE) -C component clean
	$(MAKE) -C vector clean
	$(MAKE) -C dstl clean

cleanall:
	$(MAKE) -C arithmetic cleanall
	$(MAKE) -C component cleanall
	$(MAKE) -C vector cleanall
	$(MAKE) -C dstl cleanall
	rm ./lib -rf

darithmetic:    
	$(MAKE) -C arithmetic

dcomponent:    
	$(MAKE) -C component 

dvector:    
	$(MAKE) -C vector

dstllib:    
	$(MAKE) -C dstl 
