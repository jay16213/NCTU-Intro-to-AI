CC = g++
CODE = main.cpp search.h Coord.h Coord.cpp Bfs.cpp Ids.cpp Astar.cpp

default: main main2

main: $(CODE)
	$(CC) $(CODE) -DORIGINAL_HEURISTIC -o main

main2: $(CODE)
	$(CC) $(CODE) -DIMPROVE_HEURISTIC -o main2

debug: $(CODE)
	$(CC) $(CODE) -DORIGINAL_HEURISTIC -g -o main
	$(CC) $(CODE) -DIMPROVE_HEURISTIC -g -o main2

.PHONY: clean
clean:
	$(RM) *.exe *.out main main2
