#include <iostream>
#include <vector>
#include <windows.h>
#include <sstream>
#include <fstream>
using namespace std;
int main() {
	vector<unsigned char> serid(30000,0);
	int ptr = 0;
	int pc = 0;
	cout << "Enter a .ook file to run it on Ook! Esolang Interpreter: (Note: this is full Ook Interpreter)" << endl;
	string file;
	getline(cin,file);
	ifstream openedfile(file);
	stringstream filereaderss;
	if (!openedfile.is_open()) {
		cout << "Error: File could not opened." << endl;
		exit(0);
	} else if (openedfile.is_open() && file.substr(file.size() - 4) != ".ook") {
		cout << "Error: File's extension isn't .ook" << endl;
		exit(0);
	}
	vector<string> kodlar;
	filereaderss << openedfile.rdbuf();
	string code = filereaderss.str();
	openedfile.close();
	stringstream ss(code);
	string i;
	vector<string> full;
	while (ss >> i) kodlar.push_back(i);
	int ip = 0;
	while (ip < kodlar.size()) {
		full.push_back(kodlar[ip]);
		full.back() += ' ';
		full.back() += kodlar[ip+1];
		ip += 2;
	} while (pc < full.size()) {
		string s = full[pc];
		if (s == "Ook. Ook.") serid[ptr]++;
		else if (s == "Ook! Ook!") serid[ptr]--;
		else if (s == "Ook. Ook?") ptr++;
		else if (s == "Ook? Ook.") ptr--;
		else if (s == "Ook! Ook.") cout << serid[ptr];
		else if (s == "Ook. Ook!") serid[ptr] = cin.get();
		else if (s == "Ook! Ook?") {
			if (serid[ptr] == 0) {
				int loopctr = 1;
				while (loopctr > 0) {
					pc++;
					if (full[pc] == "Ook! Ook?") loopctr++;
					else if (full[pc] == "Ook? Ook!") loopctr--;
				}
			}
		} else if (s == "Ook? Ook!") {
			if (serid[ptr] != 0) {
				int loopctr = 1;
				while (loopctr > 0) {
					pc--;
					if (full[pc] == "Ook! Ook?") loopctr--;
					else if (full[pc] == "Ook? Ook!") loopctr++;
				}
			}
		} else { pc++; }
		pc++;
	} Sleep(5000);
	exit(0);
}
