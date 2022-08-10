CXX = g++
CPPFLAGS = -Og --std=c++17
CXXFLAGS = -Wall
LDFLAGS =

string_sort: string_sort.o custom_string.o
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^

test: custom_string_tests.o custom_string.o
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^

%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf string_sort test *.o
