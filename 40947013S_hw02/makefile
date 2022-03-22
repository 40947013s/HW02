all: hw0201.o func0201.c hw0202.o func0202.c hw0203.o func0203.c hw0204.o func0204.c hw0205.o func0205.c 
	gcc func0201.c hw0201.o -o hw0201
	gcc func0202.c hw0202.o -o hw0202 -lm
	gcc func0203.c hw0203.o -o hw0203 -lm
	gcc func0201.c func0204.c hw0204.o -o hw0204 
	gcc func0205.c hw0205.o -o hw0205 -lm

hw0201: hw0201.c
	gcc -c func0201.c hw0201.c -o hw0201.o 
	gcc -shared hw0201.o -o libhw0201.so

hw0202: hw0202.c
	gcc -c func0202.c hw0202.c -o hw0202.o -lm
	gcc -shared hw0202.o -o libhw0202.so

hw0203: hw0203.c
	gcc -c func0203.c hw0203.c -o hw0203.o -lm
	gcc -shared hw0203.o -o libhw0203.so

hw0204: hw0204.c
	gcc -c func0201.c func0204.c hw0204.c -o hw0204.o 
	gcc -shared hw0204.o -o libhw0204.so

hw0205: hw0205.c
	gcc -c func0205.c hw0205.c -o hw0205.o -lm
	gcc -shared hw0205.o -o libhw0205.so