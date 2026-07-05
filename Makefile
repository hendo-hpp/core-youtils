.PHONY: build format valgrind

build:
	cmake -B build/ -S . && cmake --build build/

format:
	cmake --build build/ --target format

valgrind:
	cmake --build build/ --target valgrind_wc