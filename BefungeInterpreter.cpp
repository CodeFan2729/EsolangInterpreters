#include <iostream>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <ctime>
using namespace std;

class Yorumlayici {
public:
	void RunBfCode(string kod) {
		srand(time(0));
		stringstream parcalayici(kod);
		string ayrilmisparca;
		while (getline(parcalayici,ayrilmisparca,'\n')) kodlar.push_back(ayrilmisparca);
		while (true) {
			char c = kodlar[y][x];
			switch (c) {
				case '>':
					if (!sm) mod = "sag";
					break;
				case '<':
					if (!sm) mod = "sol";
					break;
				case 'v':
					if (!sm) mod = "asagi";
					break;
				case '^':
					if (!sm) mod = "yukari";
					break;
				case '?': {
					if (!sm) {
						int randsayi = rand() % 4;
						switch (randsayi) {
							case 0:
								mod = "sag";
								break;
							case 1:
								mod = "sol";
								break;
							case 2:
								mod = "asagi";
								break;
							case 3:
								mod = "yukari";
								break;
							
						}
					} break;
				}
				case '.':
					if (!sm) {
						if (!stack.empty()) {
							cout << stack.back();
							stack.pop_back();
						}
					}
					break;
				case ',':
					if (!sm) {
						if (!stack.empty()) {
							cout << char(stack.back());
							stack.pop_back();
						}
					}
					break;
				case '+':
					if (!sm) {
						if (stack.empty() || stack.size() <= 1) stack.push_back(0);
						else {
							int xx = stack.back();
							stack.pop_back();
							int yy = stack.back();
							stack.pop_back();
							stack.push_back(yy + xx);
						}
					} break;
				case '-':
					if (!sm) {
						if (stack.empty() || stack.size() <= 1) stack.push_back(0);
						else {
							int xx = stack.back();
							stack.pop_back();
							int yy = stack.back();
							stack.pop_back();
							stack.push_back(yy - xx);
						}
					} break;
				case '*':
					if (!sm) {
						if (stack.empty() || stack.size() <= 1) stack.push_back(0);
						else {
							int xx = stack.back();
							stack.pop_back();
							int yy = stack.back();
							stack.pop_back();
							stack.push_back(yy * xx);
						}
					} break;
				case '/':
					if (!sm) {
						if (stack.empty() || stack.size() <= 1) stack.push_back(0);
						else {
							int xx = stack.back();
							stack.pop_back();
							int yy = stack.back();
							stack.pop_back();
							stack.push_back(yy / xx);
						}
					} break;
				case '%':
					if (!sm) {
						if (stack.empty() || stack.size() <= 1) stack.push_back(0);
						else {
							int xx = stack.back();
							stack.pop_back();
							int yy = stack.back();
							stack.pop_back();
							stack.push_back(yy % xx);
						}
					} break;
				case '$':
					if (!sm && !stack.empty()) {
						stack.pop_back();
					} break;
				case '"':
					sm = true;
					HareketEt();
					while (kodlar[y][x] != '"') {
						stack.push_back(int(kodlar[y][x]));
						HareketEt();
					} sm = false;
					break;
				case ':':
					if (!sm) {
						if (stack.empty()) stack.push_back(0);
						stack.push_back(stack.back());
					} break;
				case '~':
					if (!sm) {
						char girdi;
						girdi = cin.get();
						stack.push_back(int(girdi));
					} break;
				case '&':
					if (!sm) {
						int girdi;
						cin >> girdi;
						stack.push_back(girdi);
					} break;
				case '_':
					if (!sm) {
						if (stack.empty()) stack.push_back(0);
						int sayi = stack.back();
						stack.pop_back();
						if (sayi == 0) mod = "sag";
						else if (sayi != 0) mod = "sol";
					} break;
				case '#':
					if (!sm) {
						HareketEt();
					} break;
				case 'p':
					if (!sm) {
						if (stack.empty() or stack.size() < 3) gridmatris[0][0] = 0;
						else {
							int yy = stack.back();
							stack.pop_back();
							int xx = stack.back();
							stack.pop_back();
							int veri = stack.back();
							stack.pop_back();
							gridmatris[yy][xx] = veri;
						}
					} break;
				case 'g':
					if (!sm) {
						if (stack.empty() || stack.size() < 2) stack.push_back(gridmatris[0][0]);
						else {
							int yy = stack.back();
							stack.pop_back();
							int xx = stack.back();
							stack.pop_back();
							stack.push_back(gridmatris[yy][xx]);
						}
					} break;
				case '\\':
					if (!sm) {
						if (stack.empty() || stack.size() < 2) { stack.push_back(0); stack.push_back(0);}
						else {
							int xx = stack.back();
							int yy = stack[stack.size() - 2];
							stack.pop_back();
							stack.pop_back();
							stack.push_back(xx);
							stack.push_back(yy);
						}
					} break;
				case '|':
					if (!sm) {
						if (stack.empty()) stack.push_back(0);
						if (stack.back() == 0) mod = "asagi";
						else mod = "yukari";
						stack.pop_back();
					} break;
				case ' ':
					if (!sm) HareketEt();
			} if (c == '@' && !sm) break;
			if (c >= '0' && c <= '9') {if (!sm) stack.push_back(c-'0'); };
			HareketEt();
		}
	}
private:
	vector<int> stack;
	int gridmatris[25][80];
	int x = 0, y = 0;
	bool sm = false;
	vector<string> kodlar;
	string mod = "sag";
	void HareketEt() {
		if (mod == "sag") x++;
		else if (mod == "sol") x--;
		else if (mod == "yukari") y--;
		else if (mod == "asagi") y++;
	}
}; int main() {
	srand(time(0));
	Yorumlayici yorumlayici;
	cout << "Enter a .bf file to run it on Befunge Interpreter: (note: I've done most of this interpreter but this is not fully Befunge-93. For code in full Befunge : tio.run/#befunge)" << endl;
	string koddosyasi;
	getline(cin,koddosyasi);
	ifstream file(koddosyasi);
	if (!file.is_open()) { cout << "Error: File not found." << endl; exit(0); }
	else if (file.is_open() && koddosyasi.substr(koddosyasi.size()-3) != ".bf") {cout << "Error: File's extension is not .bf" << endl; exit(0); }
	else {
		cout << endl;
		stringstream okuyucu;
		okuyucu << file.rdbuf();
		string kod = okuyucu.str();
		yorumlayici.RunBfCode(kod);
		Sleep(5000);
		exit(0);
	}
}
