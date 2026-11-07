#include <iostream>
#include <stack>
#include <fstream>
#include <windows.h>
#include <sstream>
using namespace std;
int BinaryToInt(string binary) {
	int buffer = 0;
	bool error = false;
	for (char c : binary) {
		if (c != '0' and c != '1') error = true;
	} if (!error) {
		int list[binary.size()];
		list[0] = 1;
		for (int i = 1; i < binary.size(); i++) {
			list[i] = list[i - 1] * 2;
		} string tersine = "";
		for (int i = binary.size()-1; i > -1; i--) tersine += binary[i];
		int j = 0;
		for (char c : tersine) {
			if (c == '1') buffer += list[j];
			j++;
		} return buffer;
	}
}
int main() {
	stack<int> stak;
	cout << "Enter a .ws file to run it on Whitespace Interpreter: (note: I made most of it but this is not fully Whitespace Interpreter.)" << endl;
	string fle;
	getline(cin, fle);
	ifstream rf(fle);
	if (!rf.is_open()) {
		cout << "Error: File not found." << endl;
		Sleep(2500);
		exit(1);
	} else if (rf.is_open() && fle.substr(fle.size()-3) != ".ws") {
		cout << "Error: File's extension is not .ws" << endl;
		rf.close();
		Sleep(2500);
		exit(0);
	} stringstream ss;
	ss << rf.rdbuf();
	string buffercode = ss.str();
	string code = "";
	for (char c : buffercode) {
		if (c == ' ' or c == '\t' or c == '\n') code += c;
	} int ip = 0;
	if (code[code.size()-1] == '\n' && code[code.size()-2] == '\n' && code[code.size()-3] == '\n') {
		while (ip < code.length()) {
			char c = code[ip];
			string beraber = "";
			beraber += c;
			beraber += code[ip+1];
			if (beraber == "\t\n") {
				string devam = "";
				devam += code[ip+2];
				devam += code[ip+3];
				if (devam == "  ") { cout << char(stak.top()); stak.pop(); }
				else if (devam == " \t") {cout << stak.top(); stak.pop(); }
				else if (devam == "\t ") {
					char girdi;
					girdi = cin.get();
					stak.push(int(girdi));
				} else if (devam == "\t\t") {
					int girdi;
					cin >> girdi;
					stak.push(girdi);
				} ip += 3;
			} else if (beraber == "\t ") {
				string devam;
				devam += code[ip+2];
				devam += code[ip+3];
				if (devam == "  ") {
					int nmbr1 = stak.top();
					stak.pop();
					int nmbr2 = stak.top();
					stak.pop();
					stak.push(nmbr2 + nmbr1);
				} else if (devam == " \n") {
					int nmbr1 = stak.top();
					stak.pop();
					int nmbr2 = stak.top();
					stak.pop();
					stak.push(nmbr2 * nmbr1);
				} else if (devam == " \t") {
					int nmbr1 = stak.top();
					stak.pop();
					int nmbr2 = stak.top();
					stak.pop();
					stak.push(nmbr2 - nmbr1);
				} else if (devam == "\t ") {
					int nmbr1 = stak.top();
					stak.pop();
					int nmbr2 = stak.top();
					stak.pop();
					stak.push(nmbr2 / nmbr1);
				} else if (devam == "\t\t") {
					int nmbr1 = stak.top();
					stak.pop();
					int nmbr2 = stak.top();
					stak.pop();
					stak.push(nmbr2 % nmbr1);
				}
				ip += 3;
			} else {
				if (c == ' ') {
					string devam = "";
					devam += code[ip+1];
					devam += code[ip+2];
					string substring = code.substr(ip+3);
					substring = substring.substr(0, substring.find('\n'));
					if (devam == "  ") {
						string binarycode = "";
						for (char ch : substring) {
							if (ch == '\t') binarycode += '1';
							else if (ch == ' ') binarycode += '0';
						} stak.push(BinaryToInt(binarycode));
						ip += 2;
						ip += substring.length();
					} else if (devam == " \t") {
						string binarycode = "";
						for (char ch : substring) {
							if (ch == '\t') binarycode += '1';
							else if (ch == ' ') binarycode += '0';
						} stak.push(0-BinaryToInt(binarycode));
						ip += 2;
						ip += substring.length();
					} else if (devam == "\n ") {
						int sayi = stak.top();
						stak.push(sayi);
						ip += 2;
					} else if (devam == "\n\t") {
						int sayi = stak.top();
						stak.pop();
						int sayi2 = stak.top();
						stak.pop();
						stak.push(sayi2);
						stak.push(sayi);
						ip += 2;
					} else if (devam == "\n\n") {stak.pop(); ip += 2;}
				}
			}
			ip++;
		}
	} else {
		cout << "Wspace: Error: Program did not terminated safely." << endl;
		Sleep(2500);
		exit(0);
	} Sleep(2500);
	exit(0);
}
