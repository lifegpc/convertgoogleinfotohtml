if [ ! -d "bin" ]; then
mkdir bin
fi
g++ -O3 -o bin/main.o -c src/main.cpp
g++ -O3 -o bin/help.o -c src/help.cpp
g++ -O3 -o bin/string.o -c src/string.cpp
g++ -O3 -o bin/json.o -c -w src/json.cpp
g++ -O3 -o convert bin/main.o bin/help.o bin/string.o bin/json.o -ljson-c
