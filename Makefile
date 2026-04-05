.PHONY: clean
main: main.cpp fractaler.cpp
	g++ --std=c++20 -o main main.cpp fractaler.cpp -lraylib -lopengl32 -lgdi32 -lwinmm -fopenmp
utils-test: test/utils.cpp
	g++ --std=c++20 -o utils-test test/utils.cpp
clean:
	rm -rf *.exe