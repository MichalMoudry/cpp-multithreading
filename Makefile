cpp_version := c++17
path := ./section08/lecture12

run:
	g++ $(path)/main.cpp -std=$(cpp_version) -o ./output/main
	./output/main

assignment:
	g++ ./section07/assignment02/main.cpp -std=$(cpp_version) -o ./output/main
	./output/main