#include <iostream>
#include <vector>
#include <windows.h>
#include <bitset>
#include <fstream>
#include <sstream>
using namespace std;
void WaitExit(int exitcode) {
	Sleep(3500);
	exit(exitcode);
}
int main() {
	int A = 0;
	cout << "Enter a .evil file to run it on Evil (1999) Esolang Interpreter: (note: I have done most of it but it's not fully evil Interpreter. For full Interpreter: tio.run/#evil)" << endl;
	string file;
	getline(cin,file);
	ifstream dosyaoku(file);
	vector<int> tekerlek(1,0);
	vector<int> tekerlek2(5,0);
	bool standartmode = true;
	int ptr2 = 0;
	int ptr = 0;
	if (!dosyaoku.is_open()) {
		cout << "Error: File could not open." << endl;
		WaitExit(1);
	} else if (dosyaoku.is_open() && file.substr(file.size()-5) != ".evil") {
		cout << "Error: File's extension is not .evil" << endl;
		WaitExit(0);
	} stringstream ss;
	ss << dosyaoku.rdbuf();
	string kod = ss.str();
	int pc = 0;
	while (pc < kod.size()) {
		char c = kod[pc];
		switch (c) {
			case 'a': A++; break;
			case 'u': A--; break;
			case 'z': A = 0; break;
			case 'i':
				ptr = (ptr+1) % tekerlek.size();
				break;;
			case 'o':
				ptr = (ptr-1+tekerlek.size()) % tekerlek.size();
				break;
			case 'e': {
				bitset<8> bitset1(A);
				string binary = bitset1.to_string();
				string binary2 = "        ";
				binary2[2] = binary[0];
				binary2[0] = binary[1];
				binary2[4] = binary[2];
				binary2[1] = binary[3];
				binary2[6] = binary[4];
				binary2[3] = binary[5];
				binary2[7] = binary[6];
				binary2[5] = binary[7];
				bitset<8> bitset2(binary2);
				A = bitset2.to_ullong();
				break;
			} case 'w':
				cout << char(A);
				break;
			case 'c': {
				vector<int> liste;
				for (int i = tekerlek.size()-1; i > ptr; i--) {
					liste.push_back(tekerlek[i]);
					tekerlek.pop_back();
				} tekerlek.push_back(0);
				for (int i = 0; i < liste.size(); i++) {
					tekerlek.push_back(liste[i]);
				}
				break;
			}
			case 'd':
				if (tekerlek.size() > 1) {
					vector<int> liste;
					for (int i = tekerlek.size()-1; i > ptr; i--) {
						liste.push_back(tekerlek[i]);
						tekerlek.pop_back();
					}  tekerlek.pop_back();
					for (int i = 0; i < liste.size(); i++) {
						tekerlek.push_back(liste[i]);
					}
				}
				else tekerlek[ptr] = 0;
				break;
			case 'p':
				A = tekerlek[ptr];
				break;
			case 'v':
				tekerlek[ptr] = A;
				break;
			case 'q': {
				int a = tekerlek[ptr];
				int b = A;
				A = a;
				tekerlek[ptr] = b;
				break;
			} case 'r': {
				char girdi;
				girdi = cin.get();
				A = int(girdi);
				break;
			} case 'h':
				ptr2 = (ptr2+1) % tekerlek2.size();
				break;
			case 'n':
				ptr2 = (ptr2-1+tekerlek2.size()) % tekerlek.size();
				break;
			case 'g':
				A = tekerlek2[ptr2];
				break;
			case 'k':
				tekerlek2[ptr2] = A;
				break;
			case 'y': {
				int a = tekerlek2[ptr2];
				int b = A;
				A = a;
				tekerlek2[ptr2] = b;
				break;
			} case 's':
				if (A == 0) pc++;
				break;
			case 't':
				if (A != 0) pc++;
				break;
			case 'l': {
				int yedek = tekerlek[ptr];
				tekerlek[ptr] = A;
				A = yedek;
				break;
			} case 'x':
				if (standartmode) standartmode = false;
				else if (!standartmode) standartmode = true;
				break;
		}
		pc++;
	} WaitExit(0);
}
