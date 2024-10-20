CC = gcc
#link raylib statically, GL does not have a static lib, cant use -static 
#atleast the final user wont need to already have raylib's .so
RAY_FLAGS = -lGL -lm -lpthread -ldl -lrt -lX11 -L./raylib/ -lraylib  


update:
	${CC} src/main.c ${RAY_FLAGS} -o main
	./main
