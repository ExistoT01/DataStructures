#include "kmp.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#define _USE_MATH_DEFINES

using namespace std;

int main() {
	ofstream myFile;
	string line;

	//cout << INT_MAX;

	ifstream myfile("Pi_200million.txt");
	if (myfile.is_open())
	{
		myfile >> line;
		//cout << "finished";
		cout << "patternStr start at: " << kmp_algo(line, "19260817");
		
		myfile.close(); 
	}

	


	//const int max_terms = 10000000000000;
	//double Sm = 1;
	//double sum = 1;

	//for (int m = 1; m < max_terms; m++)
	//{
	//	Sm *= m / (2.0 * m + 1);
	//	sum += Sm;
	//}

	//cout << fixed << setprecision(500) << 2 * sum << endl;

	return 0;
}