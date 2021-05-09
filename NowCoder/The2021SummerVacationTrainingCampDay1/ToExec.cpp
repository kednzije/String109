#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream in("table.txt");
	ofstream out("Lines.txt");
	while(true) {
		int a, b;
		in >> a >> b;
		if(a == 5000) {
			break;
		}
		if(a > b) { continue; }
		out << "t[mp(" << a << ", " << b << ")] = 1;" << endl;
	}
}