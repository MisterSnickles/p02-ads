all: p02
p02: clean main.o Utility.o
	g++ -o p02 main.o Utility.o
main.o: main.cpp
	g++ -c -g main.cpp
utility.o: Utility.cpp
	g++ -c -g Utility.cpp
clean:
	rm -f *.o *.exe