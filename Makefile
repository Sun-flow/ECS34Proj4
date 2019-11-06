CXX=g++

CSVLIBDIR=libcsv-3.0.3
CSVLIB=libcsv.a

INCDIR=./include
SRCDIR=./src
BINDIR=./bin
OBJDIR=./obj
TESTBINDIR=./testbin

CXXFLAGS = --std=c++14 -I $(INCDIR) -I $(CSVLIBDIR)
TESTLDFLAGS= -lgtest -lgtest_main -lpthread

CSVOBJS=$(OBJDIR)/CSVReader.o

CSVTEST=testcsv


all: $(CSVLIBDIR)/.libs/$(CSVLIB) directories RUNTESTS

RUNTESTS: RUNCSVTEST

RUNCSVTEST: $(TESTBINDIR)/$(CSVTEST)
	$(TESTBINDIR)/$(CSVTEST)

$(CSVLIBDIR)/.libs/$(CSVLIB): $(CSVLIBDIR)/Makefile
	cd $(CSVLIBDIR); make; cd ..


$(CSVLIBDIR)/Makefile:
	cd $(CSVLIBDIR); ./configure ; cd ..

$(TESTBINDIR)/$(CSVTEST): $(OBJDIR)/testcsv.o $(CSVOBJS) $(CSVLIBDIR)/.libs/$(CSVLIB)
	$(CXX) $(CXXFLAGS) $(OBJDIR)/testcsv.o $(CSVOBJS) $(CSVLIBDIR)/.libs/$(CSVLIB) -o $(TESTBINDIR)/$(CSVTEST) $(TESTLDFLAGS)

$(OBJDIR)/testcsv.o: $(SRCDIR)/testcsv.cpp $(INCDIR)/CSVReader.h
	$(CXX) $(CXXFLAGS) $(SRCDIR)/testcsv.cpp -c -o $(OBJDIR)/testcsv.o

$(OBJDIR)/testcsv.o: $(SRCDIR)/CSVReader.cpp $(INCDIR)/CSVReader.h
	$(CXX) $(CXXFLAGS) $(SRCDIR)/CSVReader.cpp -c -o $(OBJDIR)/CSVReader.o




directories: $(BINDIR) $(OBJDIR) $(TESTBINDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TESTBINDIR):


clean:
	cd $(CSVLIBDIR); make clean ; cd ..
	rm -f $(CSVLIBDIR)/Makefile
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/*
	rm -f $(TESTBINDIR)/*
	rm -f