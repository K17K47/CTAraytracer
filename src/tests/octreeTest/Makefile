.PHONY: all, clean

TEST := octreeTest

CPPFLAGS := -I../../
CFLAGS :=
CXXFLAGS += -g -std=c++11
LDFLAGS += -g -L../../ -pthread -lRaytrace

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard %.hpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

all : $(TEST)

$(TEST) : $(OBJECTS) Makefile
	$(CXX) -o $@ $(LDFLAGS) $(OBJECTS)

%.o: %.cpp $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(OUTPUT_OPTION) $<

clean:
	@echo "Clean."
	-rm -f $(OBJECTS) $(TEST)
