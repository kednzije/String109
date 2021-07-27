#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <map>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <vector>
using namespace std;
constexpr int MAXN = 1e3;
inline int min(int a, int b) {
	return a < b ? a : b;
}
using ll = long long;

int degree[MAXN];
ll dis[MAXN][MAXN];
vector <pair <int, int>> edges;
double q[MAXN];
vector <int> N[MAXN];

int main() {
	memset(degree, 0, sizeof(degree));
	for(int i = 0; i < MAXN; i++) {
		for(int j = 0; j < MAXN; j++) {
			dis[i][j] = (i == j) ? 0 : INT_MAX;
		}
	}

	srand(time(NULL));
	for(int i = 0; i < MAXN; i++) {
		for(int j = i + 1; j < MAXN; j++) {
			if(rand() % 100 < 5) {
				dis[i][j] = dis[j][i] = 1;
				degree[i]++, degree[j]++;
				edges.push_back(make_pair(i, j));
				N[i].push_back(j), N[j].push_back(i);
			}
		}
	}

	map <int, int> degreeDistribution;
	for(int i = 0; i < MAXN; i++) {
		degreeDistribution[degree[i]]++;
	}
	ofstream f_degDistribution("degreeDistribution.txt");
	for(auto &deg: degreeDistribution) {
		f_degDistribution << deg.first << ' ' << 1.0 * deg.second / MAXN << endl;
	}
	f_degDistribution.close();

	for(int k = 0; k < MAXN; k++) {
		for(int i = 0; i < MAXN; i++) {
			for(int j = 0; j < MAXN; j++) {
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}

	ll totDis = 0;
	for(int i = 0; i < MAXN; i++) {
		for(int j = i + 1; j < MAXN; j++) {
			totDis += dis[i][j];
		}
	}
	double avgDis = 1.0 * totDis / (MAXN * (MAXN - 1) / 2);
	printf("AvgDis: %.6lf\n", avgDis);

	map <pair <int, int>, int> _e;
	for(auto &edge: edges) {
		_e[make_pair(degree[edge.first], degree[edge.second])]++;
		_e[make_pair(degree[edge.second], degree[edge.first])]++;
	}
	map <pair <int, int>, double> e;
	for(auto &_e_ij: _e) {
		e[_e_ij.first] = 1.0 * _e_ij.second / (edges.size() * 2);
	}

	auto p = [&](int i)->double {
		return 1.0 * degreeDistribution[i] / MAXN;
	};

	double sum_i_pi = 0;
	for(int i = 0; i < MAXN; i++) {
		sum_i_pi += i * p(i);
	}
	for(int i = 0; i < MAXN; i++) {
		q[i] = i * p(i) / sum_i_pi;
	}
	double sigma_2 = 0;
	for(int i = 0; i < MAXN; i++) {
		sigma_2 += i * q[i];
	}
	sigma_2 = -(sigma_2 * sigma_2);
	for(int i = 0; i < MAXN; i++) {
		sigma_2 += i * i * q[i];
	}

	double r = 0;
	for(auto &e_ij: e) {
		r += e_ij.first.first * e_ij.first.second * (e_ij.second - q[e_ij.first.first] * q[e_ij.first.second]);
	}
	r /= sigma_2;
	printf("r: %.6lf\n", r);

	ofstream deg_c_i("Degree_ClusteringCoefficient.txt");
	for(int i = 0; i < MAXN; i++) {
		int c = 0;
		for(auto &u: N[i]) {
			for(auto &v: N[i]) {
				c += (dis[u][v] == 1);
			}
		}
		c /= 2;
		deg_c_i << degree[i] << ' ' << setprecision(6) << fixed << 2.0 * c / (N[i].size() * (N[i].size() - 1)) << endl;
	}

	getchar(); getchar();
}