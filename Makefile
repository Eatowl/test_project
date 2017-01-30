all:
	g++ -Wall -o run main.cpp
	gcc -Wall -o out main.c
	gcc -Wall -o thread pthread.c -pthread