#include <iostream>
#include <cstdio>
#include <map>
#include <string>
#include <utility>
using namespace std;

map <pair <int, int>, long long> seen;

int main() {
	int t;
	scanf("%d", &t);

	string s;
	int x = 0, y = 0, l;
	long long cnt = 0;
	while(t--) {
		x = 0, y = 0, cnt = 0, seen.clear();
		seen[make_pair(0, 0)] = 1;
		
		cin >> l >> s;
		for(int i = 0; i < l; i++) {
			switch (s[i])
			{
			case 'U':
				y += 1;
				cnt += seen[make_pair(x, y)];
				seen[make_pair(x, y)]++;
				break;
			case 'D':
				y -= 1;
				cnt += seen[make_pair(x, y)];
				seen[make_pair(x, y)]++;
				break;
			case 'L':
				x -= 1;
				cnt += seen[make_pair(x, y)];
				seen[make_pair(x, y)]++;
				break;
			case 'R':
				x += 1;
				cnt += seen[make_pair(x, y)];
				seen[make_pair(x, y)]++;
				break;
			default:
				break;
			}
		}
		printf("%lld\n", cnt);
	}
}