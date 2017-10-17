files=linked-list.c sorting-algo.c braam.c binary-tree.c array.c
header=linked-list.h sorting-algo.h binary-tree.h array.h
obs=braam.o linked-list.o sorting-algo.o binary-tree.o array.o
all:braam
braam:${obs} ${header} 
	gcc $^ -o braam 
%.o:%.c
	gcc -c $^ 	
.PHONY:clean
clean:
	rm -rf ${obs} braam
run:
	./braam
