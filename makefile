CPPFLAG=g++
EXEC=main

all: $(EXEC)

main: main.o InputStream1.o OutputStream1.o InputStream2.o OutputStream2.o
	$(CPPFLAG) -o $@ $^
%.o: %.cpp
	$(CPPFLAG) -o $@ -c $^
clean:
	rm -rf *.o
mrproper: clean
	rm -rf find