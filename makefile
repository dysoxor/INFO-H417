main: main.o InputStream4.o OutputStream4.o
	g++ -o main main.o InputStream4.o OutputStream4.o

main.o: main.cpp
	g++ -c -o main.o main.cpp

InputStream4.o: InputStream4.h InputStream4.cpp
	g++ -c -o InputStream4.o InputStream4.cpp

OutputStream4.o: OutputStream4.h OutputStream4.cpp
	g++ -c -o OutputStream4.o OutputStream4.cpp

clear:
	rm main.o main.exe InputStream4.o OutputStream4.o
