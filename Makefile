CC = gcc
CXX = g++
SWIG = swig

SWIGFLAGS = -c++ -lua

CFLAGS = -O3
CXXFLAGS = $(CFLAGS)

SOURCES = main.cpp luaconf.cpp luaconf_wrap.cxx
OBJECTS = main.o luaconf.o luaconf_wrap.o
TARGETS = luaconf

.SUFFIXES: .c .cc .cxx .cpp .o

all: $(TARGETS)

run: luaconf
	./$<

clean-objs:
	rm -f $(OBJECTS)

clean-targets:
	rm -f $(TARGETS) luaconf_wrap.cxx

clean: clean-objs clean-targets

.cpp.o: $(SOURCES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.cxx.o: $(SOURCES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.cc.o: $(SOURCES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

luaconf_wrap.cxx: luaconf.i
	$(SWIG) $(SWIGFLAGS) $<

luaconf: $(OBJECTS)
	$(CXX) $(CFLAGS) $^ -o $@ -llua
