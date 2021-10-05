#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
constexpr int MAXN = 2e5 + 30;
using ll = long long;

ll get_min(ll a, ll b) {
	return a < b ? a : b;
}

map <int, vector <int>> msgs;
vector <pair <int, int>> sum_helper;
int ans[50];

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		int msg, k;
		cin >> msg >> k;
		if(msgs.count(msg) == 0) {
			msgs[msg] = vector <int>(21, 0);
		}
		msgs[msg][k]++;
	}

	ll sum = -1, num = 1;
	for(int i = 1; i <= get_min(20, msgs.size()); i++) {
		sum_helper.clear();
		for(auto msg: msgs) {
			int msg_k_sum = 0;
			for(int j = 1; j <= 20; j++) {
				msg_k_sum += get_min(i, j) * msg.second[j];
			}
			sum_helper.push_back({ msg_k_sum, msg.first });
		}
		sort(sum_helper.rbegin(), sum_helper.rend());

		ll tmp_sum = 0;
		for(int tmp_i = 0; tmp_i < i; tmp_i++) {
			for(int j = 1; j <= 20; j++) {
				tmp_sum += get_min(i, j) * msgs[sum_helper[tmp_i].second][j];
			}
		}
		if(sum * i < tmp_sum * num) {
			sum = tmp_sum, num = i;
			for(int ind = 0; ind < num; ind++) {
				ans[ind] = sum_helper[ind].second;
			}
		}
	}
	cout << num << endl;
	for(int i = 0; i < num; i++) {
		cout << ans[i] << ' ';
	}
}