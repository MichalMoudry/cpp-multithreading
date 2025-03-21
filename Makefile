cpp_version := c++17
path := ./section06/lecture03

run:
	g++ $(path)/main.cpp -std=$(cpp_version) -o ./output/main
	./output/main

assignment:
	g++ ./section06/assignment01/main.cpp -std=$(cpp_version) -o ./output/main
	./output/main