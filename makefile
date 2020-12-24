CPPFLAG=g++
EXEC=main exp1_3 Experiment1 randjump extsort

all: $(EXEC)

main: main.o InputStream.o OutputStream.o InputStream1.o OutputStream1.o InputStream2.o OutputStream2.o InputStream3.o OutputStream3.o InputStream4.o OutputStream4.o
	$(CPPFLAG) -o $@ $^
randjump: randjump.o InputStream.o OutputStream.o InputStream1.o OutputStream1.o InputStream2.o OutputStream2.o InputStream3.o OutputStream3.o InputStream4.o OutputStream4.o GraphFileGenerator.o
	$(CPPFLAG) -o $@ $^
extsort: extsort.o InputStream.o OutputStream.o InputStream2.o OutputStream2.o
	$(CPPFLAG) -o $@ $^
exp1_3: exp1_3.o InputStream.o OutputStream.o InputStream1.o OutputStream1.o InputStream2.o OutputStream2.o InputStream3.o OutputStream3.o InputStream4.o OutputStream4.o GraphFileGenerator.o
	$(CPPFLAG) -o $@ $^
Experiment1: Experiment1.o InputStream.o OutputStream.o InputStream1.o OutputStream1.o InputStream2.o OutputStream2.o InputStream3.o OutputStream3.o InputStream4.o OutputStream4.o
	$(CPPFLAG) -o $@ $^
%.o: %.cpp
	$(CPPFLAG) -o $@ -c $^
clean:
	rm -rf *.o
mrproper: clean
	rm -rf find
