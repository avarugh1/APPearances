#include "Analyzer.h"

Analyzer::Analyzer(std::vector<TableRow> &table){
	for(auto it = table.begin(); it != table.end(); ++it){
		categories.insert((*it)[1]);
	}

	getUserData();
	
	//std::cout << "done " <<std::endl;
}

std::string Analyzer::getCategory(){
	std::string category;
	std::cout << "~~~CATEGORIES: " << std::endl;
	for(auto it = categories.begin(); it != categories.end(); ++it){
		std::cout << *it << ", ";
	}
	std::cout << "\n~~~~~~~~~~~~~~" << std::endl;
	std::cout << "Please enter category or type 'LIST' for list of categories: ";
	std::cin >> category;
	std::transform(category.begin(),category.end(),category.begin(), ::toupper);

	while((category == "LIST") || (categories.find(category) == categories.end())){

		std::cout << std::endl;
		if(category == "LIST"){
			for(auto it = categories.begin(); it != categories.end(); ++it){
				std::cout << *it << ", ";
			}
		}
		std::cout << std::endl;

		std::cout << "Please enter proper category or type 'LIST' for list of categories: ";
		std::cin >> category;
		std::transform(category.begin(),category.end(),category.begin(), ::toupper);
	}

	return category;
}

float Analyzer::getRating(){
	std::string rating;
	std::cout << "Please enter rating of app: ";
	std::cin >> rating;
	return stof(rating);
}

int Analyzer::getInstalls(){
	std::string installNum;
	std::cout << "Please enter number of installs: ";
	std::cin >> installNum;
	return stoi(installNum);
}

bool Analyzer::paidOrFree(){
	std::string paid;
	std::cout << "Please insert [P/F] for either paid for free app: ";
	std::cin >> paid;
	return (paid == "P");
}

float Analyzer::getPrice(){
	std::string price;
	std::cout << "Please enter cost of app: ";
	std::cin >> price;
	return stof(price);
}

void Analyzer::getUserData(){
	inApp.category = getCategory();
	inApp.rating = getRating();
	inApp.installs = getInstalls();
	inApp.revenueStream = paidOrFree();
	if(inApp.revenueStream){ // paid app
		inApp.price = getPrice();
	}else{
		inApp.price = .018; // avg rev for a free app
	}
}

// get all apps with same category
// then sort by revenue
// show app name, estimated revenue, downloads, and store rating
void Analyzer::analysis(std::vector<TableRow> &table){
	std::vector<int> eligibleRows;
	for(size_t i=0;i<table.size();i++){
		TableRow row = table[i];
		if(inApp.category == row[1]){
			eligibleRows.push_back(i);
		}
	}

	sortByRev(table, eligibleRows);
	
	//std::cout << "Size of eligible is == " << eligibleRows.size() << std::endl;
}

void Analyzer::sortByRev(std::vector<TableRow> &table, std::vector<int> &rows){

	// sanitizing table for easy analysis
	for(int i : rows){
		// sanitizing column of download number
		table[i][5].erase(std::remove(table[i][5].begin(), table[i][5].end(), ','), table[i][5].end());
		table[i][5].erase(std::remove(table[i][5].begin(), table[i][5].end(), '+'), table[i][5].end());
		table[i][5].erase(std::remove(table[i][5].begin(), table[i][5].end(), '"'), table[i][5].end());

		// removing $
		if(table[i][6] == "Paid"){
			table[i][7].erase(std::remove(table[i][7].begin(), table[i][7].end(), '$'), table[i][7].end());
		}
	}

	//std::cout << "table[rows[0]][5] == " << table[rows[0]][5] << std::endl;
	int gNum = findGreatest(table, rows);
	int cNum = findClosest(table, rows);
	createNewCSV(table, gNum, cNum);

}

// finds app with the greatest revenue in the same category
int Analyzer::findGreatest(std::vector<TableRow> &table, std::vector<int> &rows){
	double revenue = 0.0;
	int rowNum = 0;

	for(int ele : rows){
		double rowRev = 0.0;
		if(table[ele][6] == "Free"){
			rowRev = std::stod(table[ele][5]) * 0.018;
		}else{
			rowRev = std::stod(table[ele][5]) * std::stod(table[ele][7]);
		}

		if(rowRev > revenue){
			revenue = rowRev;
			rowNum = ele;
		}
	}

	return rowNum;
}

// finds app with the closest revenue in the same category
int Analyzer::findClosest(std::vector<TableRow> &table, std::vector<int> &rows){
	double revenueDiff = std::numeric_limits<double>::max();
	int rowNum = 0;

	for(int ele : rows){
		double rowRev = 0.0;

		if(table[ele][6] == "Free"){
			rowRev = std::stod(table[ele][5]) * 0.018;
		}else{
			rowRev = std::stod(table[ele][5]) * std::stod(table[ele][7]);
		}

		double inAppRev = inApp.installs * inApp.price;

		if(abs(rowRev - inAppRev) < revenueDiff){
			revenueDiff = abs(rowRev - inAppRev);
			rowNum = ele;
		}
	}

	return rowNum;
}

void Analyzer::createNewCSV(std::vector<TableRow> &table, int gNum, int cNum){
	std::vector<std::string> labels = {"App Name: ", "Category: ", "Rating: ", "Reviews: ", "Size: ", "Installs: ", "Type: ", "Price: ", "Content Rating: ", "Genres: ", "Last Updated: ", "Current Version: ", "Android Version: "}; 

	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "\nAll Free Apps are given $0.018 for each install" << std::endl;
	std::cout << "\nApp with the Highest Revenue in the same category is as follows:" << std::endl;

	int ctr = 0;
	for(std::string piece : table[gNum]){
		std::cout << labels[ctr] << piece << std::endl;
		ctr++;
	}

	std::cout << "Revenue is: $";

	double gRowRev = 0.0;
	if(table[gNum][6] == "Free"){
		gRowRev = std::stod(table[gNum][5]) * 0.018;
	}else{
		gRowRev = std::stod(table[gNum][5]) * std::stod(table[gNum][7]);

	}
	std::cout << std::setprecision(15) <<  gRowRev << std::endl;

	std::cout << "\n\nApp with the Closest Revenue in the same category is as follows:" << std::endl;

	ctr = 0;
	for(std::string piece : table[cNum]){
		std::cout << labels[ctr] << piece << std::endl;
		ctr++;
	}

	std::cout << "Revenue is: $";
	double cRowRev = 0.0;
	if(table[cNum][6] == "Free"){
		cRowRev = std::stod(table[cNum][5]) * 0.018;
	}else{
		cRowRev = std::stod(table[cNum][5]) * std::stod(table[cNum][7]);
	}

	std::cout << std::setprecision(15) <<  cRowRev << std::endl;
	
}

