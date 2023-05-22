PROG = matrixok_teszt.exe
PROG_O = matrixok_teszt.o
MTRACE_O = memtrace.o

CXX = g++ -std=c++11
CXXFLAGS = -pedantic -Wall -Werror -g -DMEMTRACE

OBJS = $(PROG_O) $(MTRACE_O)

all: clean $(PROG)

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

clean:
	rm -f $(OBJS) $(PROG)