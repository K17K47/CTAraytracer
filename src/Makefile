.PHONY: all, clean

LIBNAME := libRaytrace.so

CPPFLAGS := -I./
CFLAGS :=
CXXFLAGS += -fPIC -std=c++11
LDFLAGS += -shared -pthread

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard %.hpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

all : $(LIBNAME)

$(LIBNAME) : $(OBJECTS) Makefile
	$(CXX) -o $@ $(LDFLAGS) $(OBJECTS)

%.o: %.cpp $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(OUTPUT_OPTION) $<

clean:
	@echo "Clean."
	-rm -f $(OBJECTS) $(LIBNAME)

