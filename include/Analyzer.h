#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <iomanip>
#include <cmath> 

using TableRow = std::vector<std::string>;

class Analyzer{
	struct UserApp{
		std::string category;
		float rating;
		int installs;
		bool revenueStream; // free or paid

		//if free - what is the price
		float price;
	};
	
	UserApp inApp; // app that has to be analyzed
public:
	std::set<std::string> categories;

	Analyzer(std::vector<TableRow> &);
	std::string getCategory();
	void getUserData();
	float getRating();
	int getInstalls();
	bool paidOrFree();
	float getPrice();

	void sortByRev(std::vector<TableRow> &, std::vector<int> &);
	void analysis(std::vector<TableRow> &);

	int findGreatest(std::vector<TableRow> &, std::vector<int> &);
	int findClosest(std::vector<TableRow> &, std::vector<int> &);
	void createNewCSV(std::vector<TableRow> &, int, int);

	
};
