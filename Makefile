all:
	em++ -std=c++11 src/main.cpp -o assets/main.js -s EXPORTED_FUNCTIONS="['_sam']"
