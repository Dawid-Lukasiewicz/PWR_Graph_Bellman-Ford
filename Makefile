FLAGS= -Iinc -pedantic -std=c++17

__start__: compile

compile: main.cpp Graph_Matrix.hh Graph_List.hh Vertex.hh
	g++ ${FLAGS} -o bf_graf main.cpp Graph_Matrix.hh Graph_List.hh Vertex.hh

clean:
	rm -f *.o *.gch *.out