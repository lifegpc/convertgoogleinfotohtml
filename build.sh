if [ ! -d "bin" ]; then
mkdir bin
fi
cd bin
if [ ! -d "convert" ]; then
mkdir convert
fi
cd ..
g++ -O3 -o bin/main.o -c src/main.cpp
g++ -O3 -o bin/help.o -c src/help.cpp
g++ -O3 -o bin/string.o -c src/string.cpp
g++ -O3 -o bin/json.o -c -w src/json.cpp
g++ -O3 -o bin/convert/browserhistory.o -c -w src/convert/browserhistory.cpp
g++ -O3 -o convert bin/main.o bin/help.o bin/string.o bin/json.o bin/convert/browserhistory.o -ljson-c
