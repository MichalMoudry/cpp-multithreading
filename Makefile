cpp_version := c++17
path := ./section02/lecture05

run:
	g++ $(path)/main.cpp -std=$(cpp_version) -o ./output/main
	./output/main