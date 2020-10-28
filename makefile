main: main.o InputStream.o OutputStream.o
	g++ -o main main.o InputStream.o OutputStream.o

main.o: main.cpp
	g++ -c -o main.o main.cpp

InputStream.o: InputStream.h InputStream.cpp
	g++ -c -o InputStream.o InputStream.cpp

OutputStream.o: OutputStream.h OutputStream.cpp
	g++ -c -o OutputStream.o OutputStream.cpp

clear:
	rm main.o main.exe InputStream.o OutputStream.o
