cpp_version := c++17
path := ./section03/lecture01

run:
	g++ $(path)/main.cpp -std=$(cpp_version) -o ./output/main
	./output/main

assignment:
	g++ ./section03/assignment01/main.cpp -std=$(cpp_version) -o ./output/main
	./output/main