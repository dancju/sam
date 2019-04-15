CC := /usr/lib/emscripten/em++
CFLAGS := -std=c++14 -O3

assets/main.js: src/main.cpp
	${CC} $(CFLAGS) $^ -o $@ --bind
