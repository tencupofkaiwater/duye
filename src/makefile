sub_dirs=duyebase duyestore duyenets

all:
	@for subdir in $(sub_dirs);\
	do\
		cd $$subdir;make;cd -;\
	done
	@echo '===== lib code total lines '`find -name \*.[c,h]* | xargs cat | wc -l` '====='

clean:
	@for subdir in $(sub_dirs);\
	do\
		cd $$subdir;make clean;cd -;\
	done

cleanall:
	@for subdir in $(sub_dirs);\
	do\
		cd $$subdir;make cleanall;cd -;\
	done
	@rm -rf ./release

install:
	@for subdir in $(sub_dirs);\
	do\
		cd $$subdir;make install;cd -;\
	done

uninstall:
	@for subdir in $(sub_dirs);\
	do\
		cd $$subdir;make uninstall;cd -;\
	done
