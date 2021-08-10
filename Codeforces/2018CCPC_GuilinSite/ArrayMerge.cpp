#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <cstdlib>
#include <ctime>
#include <assert.h>
using namespace std;
constexpr int MAXN = 1e5 + 10;
using ll = long long;

ll n[2], nums[2][MAXN];

int sections[2][MAXN];
ll sectionSize[2][MAXN], sectionSum[2][MAXN];
inline int getSection(int ind, int i) {
	if(sections[ind][i] != i) {
		sections[ind][i] = getSection(ind, sections[ind][i]);
	}
	return sections[ind][i];
}
void mergeSection(int ind, int a, int b) {
	static int sec[2];
	sec[0] = getSection(ind, a), sec[1] = getSection(ind, b);
	if(sec[0] == sec[1]) {
		return;
	}
	srand(time(NULL));
	if(rand() % 2) {
		swap(sec[0], sec[1]);
	}
	// a <- b, sec[0] <- sec[1]
	sections[ind][sec[1]] = sec[0];
	sectionSize[ind][sec[0]] += sectionSize[ind][sec[1]];
	sectionSum[ind][sec[0]] += sectionSum[ind][sec[1]];
}
struct Section {
	int sectionInd, sectionGrp;
	bool operator < (const Section& other) const {
		return sectionSum[sectionInd][getSection(sectionInd, sectionGrp)] * sectionSize[other.sectionInd][getSection(other.sectionInd, other.sectionGrp)]
				< sectionSum[other.sectionInd][getSection(other.sectionInd, other.sectionGrp)] * sectionSize[sectionInd][getSection(sectionInd, sectionGrp)]; 
	}
};
void mergeAll(int ind) {
	bool is_finished = false;
	while(!is_finished) {
		is_finished = true;
		for(int i = n[ind]; i >= 2; i--) {
			if(Section{ ind, i - 1 } < Section{ ind, i }) {
				mergeSection(ind, i - 1, i);
				is_finished = false;
			}
		}
	}
}

int printSection(int ind, int beginPtr, ll &ans, int &ptr) {
	int endPtr = beginPtr;
	while(getSection(ind, beginPtr) == getSection(ind, endPtr)) {
		// cout << nums[ind][endPtr] << ' ';
		ans += nums[ind][endPtr] * ptr;
		endPtr++, ptr++;
	}
	return endPtr;
}

int main() {
	int T;
	// cin >> T;
	scanf("%d", &T);
	for(int ind = 1; ind <= T; ind++) {
		// initial
		memset(nums, 0, sizeof(nums));
		memset(sections, 0, sizeof(sections));
		memset(sectionSize, 0, sizeof(sectionSize));
		memset(sectionSum, 0, sizeof(sectionSum));

		// cin >> n[0] >> n[1];
		scanf("%lld %lld", &n[0], &n[1]);
		for(int i = 0; i < 2; i++) {
			for(int j = 1; j <= n[i]; j++) {
				// cin >> nums[i][j];
				scanf("%lld", &nums[i][j]);
				sections[i][j] = j;
				sectionSize[i][j] = 1;
				sectionSum[i][j] = nums[i][j];
			}
		}

		mergeAll(0), mergeAll(1);

		int ptr[3] = { 1, 1, 1 };
		ll ans = 0;
		while(ptr[0] <= n[0] || ptr[1] <= n[1]) {
			if(ptr[1] > n[1]) {
				ptr[0] = printSection(0, ptr[0], ans, ptr[2]);
			}
			else if (ptr[0] > n[0]) {
				ptr[1] = printSection(1, ptr[1], ans, ptr[2]);
			}
			else if(Section{ 1, ptr[1] } < Section{ 0, ptr[0] }) {
				ptr[0] = printSection(0, ptr[0], ans, ptr[2]);
			}
			else {
				ptr[1] = printSection(1, ptr[1], ans, ptr[2]);
			}
		}

		printf("Case %d: %lld\n", ind, ans);
	}
}