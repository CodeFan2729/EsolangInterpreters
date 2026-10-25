#include <iostream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <fstream>
using namespace std;
int main() {
	string file;
	cout << "Enter a .bf file to run it in Brainf**k interpreter: (note: file's extension must be .bf, and this is full brainf**k.)" << endl;
	getline(cin, file);
	vector<unsigned char> memorytape(30000,0);
	int ptr = 0;
	int pc = 0;
	ifstream readfile(file);
	if (!readfile.is_open()) {
		cout << "Error: File not found." << endl;
		Sleep(2500);
		exit(0);
	} else if (readfile.is_open() && file.substr(file.size()-3) != ".bf") {
		cout << "Error: File's extension is not .bf" << endl;
		Sleep(2500);
		exit(0);
	} else {
		stringstream filereader;
		filereader << readfile.rdbuf();
		string code = filereader.str();
		cout << endl;
		while (pc < code.size()) {
			char c = code[pc];
			switch (c) {
				case '+':memorytape[ptr]++; break;
				case '-':memorytape[ptr]--; break;
				case '>': ptr++; break;
				case '<': ptr--; break;
				case '.': cout << char(memorytape[ptr]); break;
				case ',': memorytape[ptr] = cin.get(); break;
				case '[':
					if (memorytape[ptr] == 0) {
						int loopcounter = 1;
						while (loopcounter > 0) {
							pc++;
							if (code[pc] == '[') loopcounter++;
							else if (code[pc] == ']') loopcounter--;
						}
					} break;
				case ']':
					if (memorytape[ptr] != 0) {
						int loopcounter = 1;
						while (loopcounter > 0) {
							pc--;
							if (code[pc] == '[') loopcounter--;
							else if (code[pc] == ']') loopcounter++;
						}
					} break;
			}
			pc++;
		}
	} Sleep(5000);
	exit(0);
}
