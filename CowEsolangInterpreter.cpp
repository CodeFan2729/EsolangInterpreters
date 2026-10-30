#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;
vector<int> memory(30000,0);
class COW_Interpreter {
public:
	void RunCode(string code) {
		stringstream ss(code);
		string i;
		while (ss >> i) moocodes.push_back(i);
		while (pc < moocodes.size()) {
			string s = moocodes[pc];
			if (s == "MoO") memory[pointer]++;
			else if (s == "MOo") memory[pointer]--;
			else if (s == "moO") { if (pointer >= memory.size()) memory.push_back(0); pointer++; }
			else if (s == "mOo") pointer--;
			else if (s == "Moo") {
				if (memory[pointer] != 0) cout << char(memory[pointer]);
				else {
					unsigned char girdi;
					girdi = cin.get();
					memory[pointer] = int(girdi);
				}
			} else if (s == "OOM") cout << memory[pointer];
			else if (s == "oom") {
				int sayi;
				cin >> sayi;
				memory[pointer] = sayi;
			} else if (s == "OOO") memory[pointer] = 0;
			else if (s == "MMM") {
				if (memory[pointer] != 0) {
					pano = memory[pointer];
					memory[pointer] = 0;
				} else {
					memory[pointer] = pano;
				}
			} else if (s == "MOO") {
				if (memory[pointer] == 0) {
					int loopctr = 1;
					while (loopctr > 0) {
						pc++;
						if (moocodes[pc] == "MOO") loopctr++;
						else if (moocodes[pc] == "moo") loopctr--;
					}
				}
			} else if (s == "moo") {
				if (memory[pointer] != 0) {
					int loopctr = 1;
					while (loopctr > 0) {
						pc--;
						if (moocodes[pc] == "MOO") loopctr--;
						else if (moocodes[pc] == "moo") loopctr++;
					}
				}
			} else if (s == "mOO") {
				if (memory[pointer] != 3) {
					switch (memory[pointer]) {
						case 0:
							moocodes[pc] = "moo";
							pc--;
							break;
						case 1:
							moocodes[pc] = "mOo";
							pc--;
							break;
						case 2:
							moocodes[pc] = "moO";
							pc--;
							break;
						case 4:
							moocodes[pc] = "MOo";
							pc--;
							break;
						case 5:
							moocodes[pc] = "MoO";
							pc--;
							break;
						case 6:
							moocodes[pc] = "MOO";
							pc--;
							break;
						case 7:
							moocodes[pc] = "OOO";
							pc--;
							break;
						case 8:
							moocodes[pc] = "MMM";
							pc--;
							break;
						case 9:
							moocodes[pc] = "OOM";
							pc--;
							break;
						case 10:
							moocodes[pc] = "oom";
							pc--;
							break;
						case 11:
							moocodes[pc] = "Moo";
							pc--;
							break;
					}
				}
			}
			pc++;
		}
	} 
private:
	
	vector<string> moocodes;
	int pointer = 0;
	int pc = 0;
	int pano;
}; int main() {
	string file;
	cout << "Enter a .cow file to run it on COW Interpreter: (note: this is full COW Esolang Interpreter.)" << endl;
	getline(cin, file);
	ifstream rf(file);
	if (!rf.is_open()) {
		cout << "Error: File could not opened." << endl;
		exit(0);
	} else if (rf.is_open() && file.substr(file.size()-4) != ".cow") {
		cout << "Error: File's extension is not .cow" << endl;
		exit(0);
	} stringstream rfss;
	rfss << rf.rdbuf();
	string cowcode = rfss.str();
	rf.close();
	COW_Interpreter Interpreter;
	Interpreter.RunCode(cowcode);
	Sleep(6000);
	exit(0);
}
