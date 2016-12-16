.PHONY: all clean tests

LIBNAME := libRaytrace.so

CPPFLAGS := -I./
CFLAGS :=
CXXFLAGS += -fPIC -std=c++11 -O3
LDFLAGS += -shared -pthread

SOURCES = $(wildcard aux/*.cpp) \
          $(wildcard lib/*.cpp)
HEADERS = $(wildcard aux/%.hpp) \
          $(wildcard lib/%.hpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

all : $(LIBNAME) tests

$(LIBNAME) : $(OBJECTS) Makefile
	$(CXX) -o $@ $(LDFLAGS) $(OBJECTS)

tests:
	cd tests && $(MAKE)

%.o: %.cpp $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(OUTPUT_OPTION) $<

clean:
	@echo "Clean."
	-rm -f $(OBJECTS) $(LIBNAME)
	cd tests && $(MAKE) clean
