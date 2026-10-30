#include <iostream>
#include <sstream>
#include <stack>
#include <fstream>
#include <map>
#include <windows.h>
#include <vector>
using namespace std;
int main() {
	map<int,int> index;
	stack<int> stak;
	cout << "Enter a .chkn file to run it on Chicken Esoteric Programming Language Interpreter:" << endl;
	string file;
	getline(cin, file);
	ifstream rf(file);
	if (!rf.is_open()) {
		cout << "Error: File not found." << endl;
		exit(0);
	} else if (rf.is_open() && file.substr(file.size()-5) != ".chkn") {
		cout << "Error: File's extension is not .chkn" << endl;
		exit(0);
	} vector<string> codes;
	stringstream databuffer;
	databuffer << rf.rdbuf();
	string code = databuffer.str();
	stringstream ss(code);
	string i;
	int pc = 0;
	while (getline(ss, i, '\n')) {
		codes.push_back(i);
		int chknsayisi = 0;
		stringstream jj(i);
		string j;
		while (jj >> j) {
			if (j.find("chicken") != string::npos) chknsayisi++;
		} index[pc] = chknsayisi;
		pc++;
	}
	int ip = 0;
	while (ip < codes.size()) {
		string piece = codes[ip];
		int chickenctr = 0;
		stringstream ssline(piece);
		string j;
		while (ssline >> j) { if (j.find("chicken") != string::npos) chickenctr++; }
		if (chickenctr == 0) { Sleep(4500); exit(0); }
		else if (chickenctr >= 10) stak.push(chickenctr - 10);
		switch (chickenctr) {
			case 1:
				stak.push(0);
				break;
			case 2: {
				while (stak.size() < 2) stak.push(0);
				int x = stak.top();
				stak.pop();
				int y = stak.top();
				stak.pop();
				stak.push(y + x);
				break;
			} case 3: {
				while (stak.size() < 2) stak.push(0);
				int x = stak.top();
				stak.pop();
				int y = stak.top();
				stak.pop();
				stak.push(y - x);
				break;
			} case 4: {
				while (stak.size() < 2) stak.push(0);
				int x = stak.top();
				stak.pop();
				int y = stak.top();
				stak.pop();
				stak.push(y * x);
				break;
			} case 5: {
				while (stak.size() < 2) stak.push(0);
				int x = stak.top();
				stak.pop();
				int y = stak.top();
				stak.pop();
				if (x == y) stak.push(1);
				else stak.push(0);
				break;
			} case 6: {
				if (stak.empty()) stak.push(0);
				int x = stak.top();
				stak.pop();
				if (x <= 0) {
					char girdi;
					girdi = cin.get();
					stak.push(int(girdi));
				} else stak.push(index[x]);
				break;
			} case 7: {
				while (stak.size() < 2) stak.push(0);
				int x = stak.top();
				stak.pop();
				int y = stak.top();
				stak.pop();
				index[x] = y;
				break;
			} case 8: {
				while (stak.size() < 2) stak.push(0);
				int x = stak.top();
				stak.pop();
				int y = stak.top();
				stak.pop();
				if (x != 0) {
					ip += (y-1);
				} break;
			} case 9:
				if (stak.empty()) stak.push(0);
				cout << char(stak.top());
				stak.pop();
				break;
		}
		ip++;
	} Sleep(4500);
	exit(0);
}
