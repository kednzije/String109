#include <iostream>
using namespace std;

string numbers[21] = {
	"Zero",
	"One",
	"Two",
	"Three",
	"Four",
	"Five",
	"Six",
	"Seven",
	"Eight",
	"Nine",
	"Ten",
	"Eleven",
	"Twelve",
	"Thirteen",
	"Fourteen",
	"Fifteen",
	"Sixteen",
	"Seventeen",
	"Eighteen",
	"Nineteen",
	"Twenty",
};

string tens[] = {
	"",
	"",
	"Twenty",
	"Thirty",
	"Forty",
	"Fifty",
	"Sixty",
	"Seventy",
	"Eighty",
	"Ninety",
};

void printNum(int n) {
	if(n / 100 != 0) {
		cout << (numbers[n / 100] + " Hundred");
		if(n % 100 != 0) {
			cout << ' ';
		}
	}
	if(n % 100 != 0) {
		if(n % 100 <= 20) {
			cout << numbers[n % 100];
		}
		else if((n % 100) % 10 != 0) {
			cout << (tens[(n % 100) / 10] + " " + numbers[n % 10]);
		}
		else {
			cout << (tens[(n % 100) / 10]);
		}
	}
}

string unit[4] = {
	"",
	"Thousand",
	"Million",
	"Billion",
};

int main() {
	int n;
	cin >> n;
	if(n == 0) {
		cout << numbers[0];
		return 0;
	}
	int num[4];
	for(int i = 0; i < 4; i++) {
		num[i] = n % 1000;
		n /= 1000;
	}

	for(int i = 3; i >= 0; i--) {
		if(0 == num[i]) {
			continue;
		}
		printNum(num[i]);
		cout << ' ' << unit[i] << ' ';
	}
}