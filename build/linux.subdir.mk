all:
	for dir in ${SUBDIR} ; do	\
		cd $$dir ; make ; cd -; done 
.PHONY:clean
clean:
	for dir in ${SUBDIR} ; do	\
	cd $$dir ; make clean; cd -;done 
	
