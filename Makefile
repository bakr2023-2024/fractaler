.PHONY: clean
main: main.cpp fractaler.cpp utils.cpp
	g++ --std=c++20 -o main main.cpp fractaler.cpp utils.cpp -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows -fopenmp
utils-test: test/utils.cpp utils.cpp
	g++ --std=c++20 -o utils-test test/utils.cpp utils.cpp
clean:
	rm -rf *.exe