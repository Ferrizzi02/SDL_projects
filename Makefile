all:
	g++ -I src/include -L src/lib -o sorter sorter.cpp -lmingw32 -lSDL2main -lSDL2_test -lSDL2