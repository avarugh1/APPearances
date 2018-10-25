CXX = g++
FLAGS = -c -std=c++11 -g -Wextra -Wall -pedantic
INCLUDE = -I ./include

all: APPearances

APPearances: CSVReader.o driver.o Analyzer.o
	$(CXX) $^ -o $@

CSVReader.o: src/CSVReader.cpp
	$(CXX) $(FLAGS) -o $@ $^ $(INCLUDE)

driver.o: src/driver.cpp
	$(CXX) $(FLAGS) -o $@ $^ $(INCLUDE)

Analyzer.o: src/Analyzer.cpp
	$(CXX) $(FLAGS) -o $@ $^ $(INCLUDE)
	
clean:
	rm *.o APPearances
