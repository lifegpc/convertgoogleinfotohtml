if [ ! -d "bin" ]; then
mkdir bin
fi
g++ -O3 -o bin/main.o -c src/main.cpp
g++ -O3 -o bin/help.o -c src/help.cpp
g++ -O3 -o convert bin/main.o bin/help.o
