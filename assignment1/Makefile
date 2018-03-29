CODE = main.cpp Coord.h Coord.cpp Bfs.cpp Ids.cpp Astar.cpp

default: main main2

main: $(CODE)
	g++ $(CODE) -DORIGINAL_HEURISTIC -o main

main2: $(CODE)
	g++ $(CODE) -DIMPROVE_HEURISTIC -o main2

debug: $(CODE)
	g++ $(CODE) -g -o main

.PHONY: clean
clean:
	$(RM) *.exe *.out main
