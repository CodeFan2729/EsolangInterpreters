#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
using namespace std;

int Bellekboyutu = 59049;

long int UsAl(long int a, long int b) {
	int buffer = a;
	if (b == 0) return 1;
	else {
		for (int i = 1; i < b; i++) buffer *= a;
		return buffer;
	}
}
int TernaryToInt(string ternary) {
	if (ternary.size() == 10) {
		int buffer = 0;
		bool hatali = false;
		for (char c : ternary) {
			if (c != '0' && c != '1' && c != '2') hatali = true;
		} if (!hatali) {
			int Liste[ternary.size()];
			string ters = "";
			for (int i = ternary.size() - 1; i > -1; i--) ters += ternary[i];
		
			for (int ip = 0; ip < ters.size(); ip++ ) {
				Liste[ip] = UsAl(3,ip);
			} int j = 0;
			for (char c : ters) {
				int toplam = int(c - '0');
				buffer += toplam * Liste[j];
				j++;
			} return buffer;
		}
	}
} string IntToTernary(int deger) {
	string buffer = "0000000000";
	int kopya = deger;
	int pc = 9;
	while (pc > -1) {
		int mod = kopya % 3;
		buffer[pc] = char(mod + '0');
		kopya /= 3;
		pc--;
	} return buffer;
}
string Crz(string ternary1, string ternary2) {
	if (ternary1.size() == 10 && ternary2.size() == 10) {
		char CrzTablosu[3][3] = {
			{'1','1','2'},
			{'0','0','2'},
			{'0','2','1'}
		}; string buffer = "0000000000";
		int ip = 0;
		while (ip < ternary1.size()) {
			char c1 = ternary1[ip];
			char c2 = ternary2[ip];
			int sayi = c1-'0', sayiiki = c2-'0';
			buffer[ip] = CrzTablosu[sayi][sayiiki];
			ip++;
		} return buffer;
	}
}
string RotRt(string ternarycode) {
	if (ternarycode.size() == 10) {
		bool hatali = false;
		for (char c : ternarycode) {
			if (c != '0' && c != '1' && c != '2') hatali = true;
		} if (!hatali) {
			string yeni = "";
			yeni += ternarycode[9];
			string kopya = ternarycode.substr(0, 9);
			yeni += kopya;
			return yeni;
		}
	}
}

int main() {
	bool programcalisiyor = true;
	int A = 0;
	int C = 0;
	int D = 0;
	int bellek[UsAl(3,10)+1];
	cout << "Enter a .mb file to run it on Malbolge Interpreter:" << endl;
	string file;
	getline(cin, file);
	ifstream rf(file);
	if (!rf.is_open()) {
		cout << "Error: File could not open." << endl;
		Sleep(3500);
		exit(1);
	}
	else if (rf.is_open() && file.substr(file.size()-3) != ".mb") {
		cout << "Error: File's extension is not .mb" << endl;
		Sleep(3500);
		exit(0);
	}
	stringstream ss;
	ss << rf.rdbuf();
	string mbkod = ss.str();
	string encrypttable = "5z]&gqtyfr$(we4{WP)H-Zn,[%\\3dL+Q;>U!pJS72FhOA1CB6v^=I_0/8|jsb9m<.TVac`uY*MK'X~xDl}REokN:#?G\"i@";
	int adrs = mbkod.size();
	
	for (int indx = 0; indx < mbkod.size(); indx++) {
		if (char(mbkod[indx]) != ' ' && char(mbkod[indx]) != '\t' && char(mbkod[indx]) != '\n' && char(mbkod[indx]) != '\r') {
			bellek[indx] = int(mbkod[indx]);
		} else bellek[indx] = 0;
	}
	while (adrs < 59049) {
		string ternaryc1 = IntToTernary(bellek[adrs - 1]);
		string ternaryc2 = IntToTernary(bellek[adrs - 2]);
		bellek[adrs] = TernaryToInt(Crz(ternaryc1, ternaryc2));
		adrs++;
	}

	
	while (programcalisiyor) {
		int desifreli = (((bellek[C] + C)-33)+94) % 94;
		int yedek = C;
		switch (desifreli) {
			case 84: {
				char girdi;
				girdi = cin.get();
				A = int(girdi);
				break;
			}
			case 66:
				cout << char(A % 256);
				break;
			case 48:
				programcalisiyor = false;
				break;
			case 29: {
				string tern1 = IntToTernary(A);
				string tern2 = IntToTernary(bellek[D]);
				string crzversiyon = Crz(tern1, tern2);
				A = TernaryToInt(crzversiyon);
				bellek[D] = A;
				break;
			} case 6: {
				string ternary = IntToTernary(bellek[D]);
				ternary = RotRt(ternary);
				A = TernaryToInt(ternary);
				bellek[D] = A;
				break;
			}
			case 7:
				D = bellek[D];
				break;
			case 65:
				C = bellek[D];
				break;
			default:
				break;
		}
		bellek[yedek] = int(encrypttable[((bellek[yedek] - 33)+94) % 94]);
		C = (C+1) % Bellekboyutu;
		D = (D+1) % Bellekboyutu;
	} Sleep(3500);
}
