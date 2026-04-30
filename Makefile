all: build

build:
	g++ -std=c++17 main.cpp -O2 -o meetsync

clean:
	rm -f meetsync
