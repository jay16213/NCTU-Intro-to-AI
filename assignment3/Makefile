CC=g++

all: main
	$(CC) *.o -o random_forest -std=c++11

main:
	$(CC) -c -std=c++11 main.cpp
	$(CC) -c -std=c++11 Forest.cpp
	$(CC) -c -std=c++11 TreeNode.cpp

.PHONY: clean
clean:
	rm -rf *.o

