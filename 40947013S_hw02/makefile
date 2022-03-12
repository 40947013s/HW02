all: hw0201.o func0201.c hw0202.o func0202.c hw0204.o func0204.c 
	gcc func0201.c hw0201.o -o hw0201
	gcc func0202.c hw0202.o -o hw0202 -lm
	gcc func0204.c hw0204.o -o hw0204 

hw0201: hw0201.c
	gcc -c hw0201.c -o hw0201.o 
	gcc -shared hw0201.o -o libhw0201.so

hw0202: hw0202.c
	gcc -c hw0202.c -o hw0202.o 
	gcc -shared hw0202.o -o libhw0202.so

hw0204: hw0204.c
	gcc -c hw0204.c -o hw0204.o 
	gcc -shared hw0204.o -o libhw0204.so
