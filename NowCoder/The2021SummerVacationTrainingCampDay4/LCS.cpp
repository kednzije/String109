#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

pair <int, int> limit[5];
string s[5];

int main() {
	int n;
	for(int i = 1; i <= 3; i++) {
		cin >> limit[i].first;
		limit[i].second = i;
	}
	sort(limit + 1, limit + 4);
	cin >> n;
	if(limit[2].first + limit[3].first - limit[1].first > n) {
		cout << "NO" << endl;
		return 0;
	}
	int ind;
	switch (limit[1].second)
	{
	case 1:
		for(int i = 1; i <= limit[1].first; i++) {
			for(int j = 1; j <= 3; j++) {
				s[j].push_back('a');
			}
		}
		for(int i = 1; i <= n - limit[1].first; i++) {
			s[1].push_back('b'), s[2].push_back('c');
		}
		ind = 3;
		break;
	case 2:
		for(int i = 1; i <= limit[1].first; i++) {
			for(int j = 1; j <= 3; j++) {
				s[j].push_back('a');
			}
		}
		for(int i = 1; i <= n - limit[1].first; i++) {
			s[2].push_back('b'), s[3].push_back('c');
		}
		ind = 1;
		break;
	case 3:
		for(int i = 1; i <= limit[1].first; i++) {
			for(int j = 1; j <= 3; j++) {
				s[j].push_back('a');
			}
		}
		for(int i = 1; i <= n - limit[1].first; i++) {
			s[3].push_back('b'), s[1].push_back('c');
		}
		ind = 2;
		break;
	default:
		ind = 0;
		break;
	}

	switch (limit[2].second)
	{
	case 1:
		for(int i = 1; i <= limit[2].first - limit[1].first; i++) {
			s[ind].push_back(s[3 - ind][limit[1].first]);
		}
		break;
	case 2:
		for(int i = 1; i <= limit[2].first - limit[1].first; i++) {
			s[ind].push_back(s[5 - ind][limit[1].first]);
		}
		break;
	case 3:
		for(int i = 1; i <= limit[2].first - limit[1].first; i++) {
			s[ind].push_back(s[4 - ind][limit[1].first]);
		}
		break;
	
	default:
		break;
	}
	switch (limit[3].second)
	{
	case 1:
		for(int i = 1; i <= limit[3].first - limit[1].first; i++) {
			s[ind].push_back(s[3 - ind][limit[1].first]);
		}
		break;
	case 2:
		for(int i = 1; i <= limit[3].first - limit[1].first; i++) {
			s[ind].push_back(s[5 - ind][limit[1].first]);
		}
		break;
	case 3:
		for(int i = 1; i <= limit[3].first - limit[1].first; i++) {
			s[ind].push_back(s[4 - ind][limit[1].first]);
		}
		break;
	
	default:
		break;
	}
	for(int i = 1; i <= n + limit[1].first - limit[2].first - limit[3].first; i++) {
		s[ind].push_back('d');
	}

	for(int i = 1; i <= 3; i++) {
		cout << s[i] << endl;
	}
}