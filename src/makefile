all:
	cd duyebase; make; cd -
	cd duyestore; make; cd -
	cd duyenets; make; cd -
	@echo '===== lib code total lines '`find -name \*.[c,h]* | xargs cat | wc -l` '====='

clean:
	cd duyebase; make clean; cd -
	cd duyestore; make clean; cd -
	cd duyenets; make clean; cd -

cleanall:
	cd duyebase; make cleanall; cd -
	cd duyestore; make cleanall; cd -
	cd duyenets; make cleanall; cd -

install:
	cd duyebase; make install; cd -
	cd duyestore; make install; cd -
	cd duyenets; make install; cd -

uninstall:
	cd duyebase; make uninstall; cd -
	cd duyestore; make uninstall; cd -
	cd duyenets; make uninstall; cd -
