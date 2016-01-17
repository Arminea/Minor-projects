#include <iostream>
#include <conio.h>
#include <signal.h>
#include <stdlib.h>
//#include <stdio.h>

#include "parser\nutparser.h"

using namespace std;

void parse(string s) {
	parser::NutParser parser(s);
	string info = parser.GetDebugInfo();
	cout << info << endl;
}

int main(int argc, char* argv[]) {

	string command = "";

	getline(cin, command);

	//cout << "You entered: " << command << endl;

	if (command != "") {
		parse(command);
		command = "";
	}

	//command = "echo ntsnhtio > text.txt";
	//parse(command);

	cin.get();

	return 0;
}