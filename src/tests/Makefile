.PHONY: all, clean

TESTS := basicRaytracing

CPPFLAGS := -I../ -L../
CFLAGS :=
CXXFLAGS += -fPIC -std=c++11
LDFLAGS += -L../ -pthread -lRaytrace

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard %.hpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

all : $(TESTS)

$(TESTS) : $(OBJECTS) Makefile
	$(CXX) -o $@ $(LDFLAGS) $(OBJECTS)

%.o: %.cpp $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(OUTPUT_OPTION) $<

clean:
	@echo "Clean."
	-rm -f $(OBJECTS) $(TESTS)
