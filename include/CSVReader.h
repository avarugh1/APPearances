#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>

using TableRow = std::vector<std::string>;

class CSVReader{
	std::string fileName;
public:
	CSVReader(std::string fName);
	std::vector<std::string> readData();
	std::vector<TableRow> splitData(std::vector<std::string> &);

};
