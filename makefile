main: main.o InputStream.o
	g++ -o main main.o InputStream.o

main.o: main.cpp
	g++ -c -o main.o main.cpp

InputStream.o: InputStream.h InputStream.cpp
	g++ -c -o InputStream.o InputStream.cpp

clear:
	rm main.o main.exe InputStream.o
