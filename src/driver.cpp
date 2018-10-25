#include <iostream>
#include "CSVReader.h"
#include <set>
#include <algorithm>
#include "Analyzer.h"

using namespace std;

// starts with 0 index for the first row!
void printRows(vector<TableRow> &table, int start, int end){
	for(int i=start;i<end;i++){
		TableRow row = table[i];
		cout << "Row #" << i << ": ";
		for(string piece : row){
			cout << piece << "||";
		}
		cout << endl;
	}
}

int main(){
	CSVReader parser("data/googleplaystore.csv");
	vector<string> data = parser.readData();
	vector<TableRow> table = parser.splitData(data);


	// all rows must have twelve fields
	// one doesn't when I checked so removing that anomoly row
	auto isAnomoly = [](const TableRow &tmp){
		return (tmp.size() != 12);
	};


	table.erase(std::remove_if(table.begin(), table.end(), isAnomoly));

	table.erase(table.begin(), table.begin()+1);

	set<string> categories;
	for(TableRow row : table){
		categories.insert(row[1]);
	}

	Analyzer engine(table);
	engine.analysis(table);

	return 0;
}
