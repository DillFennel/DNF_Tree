all: main

main: dnf_tree.o dnf_tests.o main.o
	g++ dnf_tree.o dnf_tests.o main.o -o main

dnf_tree.o:
	g++ -c dnf_tree.cpp

dnf_tests.o:
	g++ -c dnf_tests.cpp

main.o:
	g++ -c main.cpp

clean:
	rm -rf *.o *.gch main