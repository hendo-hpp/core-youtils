# shortcuts using 'make build' and 'make format'
.PHONY: build format

build:
	cmake -B build/ -S . && cmake --build build/

format:
	cmake --build build/ --target format