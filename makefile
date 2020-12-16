CPPFLAG=g++
EXEC=main exp1_3

all: $(EXEC)

main: main.o InputStream1.o OutputStream1.o InputStream2.o OutputStream2.o InputStream3.o OutputStream3.o InputStream4.o OutputStream4.o
	$(CPPFLAG) -o $@ $^

experiment1: Experiment1.o InputStream1.o InputStream2.o  InputStream3.o InputStream4.o
	$(CPPFLAG) -o $@ $^
exp1_3: exp1_3.o InputStream1.o OutputStream1.o InputStream2.o OutputStream2.o InputStream3.o OutputStream3.o
	$(CPPFLAG) -o $@ $^
%.o: %.cpp
	$(CPPFLAG) -o $@ -c $^
clean:
	rm -rf *.o
mrproper: clean
	rm -rf find
