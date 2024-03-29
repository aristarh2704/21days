OUTFILE = bin/21days
CXX = g++
OBJS = obj/main.o obj/game.o obj/interface.o  obj/sys.o

CXXFLAGS = -Wno-write-strings

all: $(OUTFILE)

dirs: 
	test -d bin || mkdir -p bin
	test -d obj || mkdir -p obj

$(OUTFILE): dirs $(OBJS)
	$(CXX) -o $(OUTFILE) $(OBJS)

obj/%.o:  %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -D__linux__

clean: 
	rm -f $(OBJS) $(OUTFILE)
	rm -rf bin
	rm -rf obj
	
rebuild: clean $(OUTFILE)

.PHONY: dirs clean rebuild
