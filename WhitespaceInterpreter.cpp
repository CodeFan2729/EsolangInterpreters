#include <windows.h>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <fstream>
using namespace std;
string Reverse(string s) {
	string buffer = "";
	for (int i = s.size()-1; i > -1; i--) {
		buffer += s[i];
	} return buffer;
}
long int BinaryToInt(string binary) {
	long int buffer = 0;
	int boyut = binary.length();
	bool hatali = false;
	for (char ch : binary) {
		if (ch != '0' && ch != '1') hatali = true;
	} if (hatali) {
		cout << "ERROR: BINARY DOESN'T FROM JUST 0 AND 1" << endl;
	} else {
		vector<long int> binaryvectoru;
		binaryvectoru.push_back(1);
		for (int i = 1; i < boyut; i++) {
			binaryvectoru.push_back(binaryvectoru[i-1]*2);
		} string tersbinary = Reverse(binary);
		for (int ip = 0; ip < boyut; ip++) {
			char ch = tersbinary[ip];
			if (ch == '0') buffer += 0;
			else if (ch == '1') {  buffer += binaryvectoru[ip]; }
		} return buffer;
	}
}
int main() {
	stack<long int> stak;
	vector<string> bolunmuskodlar;
	cout << "Enter a .ws file to run it on Whitespace Interpreter: (Note: I have done most of it but this is not full Whitespace Interpreter.)" << endl;
	string dosya;
	getline(cin, dosya);
	ifstream file(dosya);
	if (!file.is_open()) {
		cout << "Error: File could not open." << endl;
		exit(0);
	} else if (file.is_open() && dosya.substr(dosya.length()-3) != ".ws") {
		cout << "Error: File's extension isn't .ws." << endl;
		exit(0);
	} else {
		cout << endl;
		stringstream okuyucu;
		okuyucu << file.rdbuf();
		string kod = okuyucu.str();
		if (kod[kod.length()-1] == '\n' && kod[kod.length()-2] == '\n' && kod[kod.length()-3] == '\n') {
			stringstream ssbir(kod);
			string c;
			while (getline(ssbir, c,'\n')) { bolunmuskodlar.push_back(c); bolunmuskodlar.back() += '\n'; }
			int pc = 0;
			while (pc < bolunmuskodlar.size()) {
				string s = bolunmuskodlar[pc];
				if (s[0] == ' ' && s[1] == ' ' && s.length() >= 5) {
					if (s[2] == ' ') {
						string whitebinary = s.substr(3,s.find('\n'));
						string binary = "";
						for (char ch : whitebinary) {
							if (ch == ' ') binary += '0';
							else if (ch == '\t') binary += '1';
						} long int ascii = BinaryToInt(binary);
						stak.push(ascii);
					} else if (s[2] == '\t') {
						string whitebinary = s.substr(3,s.find('\n'));
						string binary = "";
						for (char ch : whitebinary) {
							if (ch == ' ') binary += '0';
							else if (ch == '\t') binary += '1';
						} long int ascii = BinaryToInt(binary);
						stak.push(0-ascii);
					}
				} else if (s == "  \n") {
					if (bolunmuskodlar[pc-1] == "\t\n" && !stak.empty()) {
						cout << char(stak.top());
						stak.pop();
					}
				} else if (s == " \t\n" && !stak.empty()) {
					if (bolunmuskodlar[pc-1] == "\t\n") {
						cout << stak.top();
						stak.pop();
					}
				} else if (s == "\t   \n") {
					if (!stak.empty()) {
						int x = stak.top();
						stak.pop();
						int y = stak.top();
						stak.pop();
						stak.push(y + x);
					}
				} else if (s == "\t  \t\n") {
					if (!stak.empty()) {
						int x = stak.top();
						stak.pop();
						int y = stak.top();
						stak.pop();
						stak.push(y - x);
					}
				} else if (s == "\t  \n") {
					if (!stak.empty()) {
						int x = stak.top();
						stak.pop();
						int y = stak.top();
						stak.pop();
						stak.push(y * x);
					}
				} else if (s == "\t \t \n") {
					if (!stak.empty()) {
						int x = stak.top();
						stak.pop();
						int y = stak.top();
						stak.pop();
						stak.push(y / x);
					}
				} else if (s == "\t \t\t\n") {
					if (!stak.empty()) {
						int x = stak.top();
						stak.pop();
						int y = stak.top();
						stak.pop();
						stak.push(y % x);
					}
				} else if (s == " \n" && bolunmuskodlar[pc+1] == "\n" && bolunmuskodlar[pc+2] == "\n") {
					if (!stak.empty()) {
						stak.pop();
					}
				} else if (s == "\t \n") {
					if (bolunmuskodlar[pc-1] == "\t\n") {
						char girdi;
						girdi = cin.get();
						stak.push(int(girdi));
					}
				} else if (s == "\t\t\n") {
					if (bolunmuskodlar[pc-1] == "\t\n") {
						int girdi;
						cin >> girdi;
						stak.push(girdi);
					}
				}
				pc++;
			}
		} else {
			cout << "Wspace: Error: There is no code found to safely terminate the program." << endl;
		}
	} Sleep(2500);
	exit(0);
}
