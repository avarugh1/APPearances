#include <CSVReader.h>

CSVReader::CSVReader(std::string fName){
	fileName = fName;
}

//reading all data in line by line
std::vector<std::string> CSVReader::readData(){
	std::ifstream inFile(fileName);
	std::vector<std::string> data;
	std::string line;

	if(!inFile){
		std::cerr << "opening file failed errno =  " << strerror(errno) << std::endl;
		exit(0);
	}

	while(getline(inFile, line, '\n')){
		data.push_back(line);
	}

	return data;
}

// breaking up data in each line
// comma is main delimiter but "" supercedes b/c of CSV standards
std::vector<TableRow> CSVReader::splitData(std::vector<std::string> &inData){
	std::vector<TableRow> retData;

	// breaking line and taking into account "" vs , parsing
	for(std::string rowUnparsed : inData){
		TableRow row;
		std::stringstream ss(rowUnparsed);
		std::string line;
		while(getline(ss, line)){
			const char *valueStart = line.c_str();
			bool inQuotes = false;
			for(const char *pos = valueStart; *pos; pos++){
				// reached the end of a value
				// now add that value to the row
				if((*pos == ',') && (inQuotes == false)){
					std::string value(valueStart, pos-valueStart);
					row.push_back(value);
					// start reading next field
					valueStart = pos + 1;
				// reached the beg or end of a quote
				}else if(*pos == '"'){
					inQuotes = !inQuotes;
				}
			}
		}
		retData.push_back(row);
	}

	return retData;

}
