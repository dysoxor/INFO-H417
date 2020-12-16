CPPFLAG=g++
EXEC=main

all: $(EXEC)

main: main.o InputStream1.o OutputStream1.o InputStream2.o OutputStream2.o InputStream3.o OutputStream3.o InputStream4.o OutputStream4.o
	$(CPPFLAG) -o $@ $^

experiment1: main.o InputStream1.o InputStream2.o  InputStream3.o InputStream4.o Experiment1.o
	$(CPPFLAG) -o $@ $^
%.o: %.cpp
	$(CPPFLAG) -o $@ -c $^
clean:
	rm -rf *.o
mrproper: clean
	rm -rf find
