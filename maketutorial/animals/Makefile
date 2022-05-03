
dog_program : 
	clang++ dog.o main.o -o dog_program
dog.o : 
	clang++ -c dog.cpp
main.o : main.cpp
	clang++ -c main.cpp
clean :
	rm dog_program *.o
