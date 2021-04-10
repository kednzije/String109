#include <vector>
#include <unordered_map>
using namespace std;

int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
    vector <vector <int>> sum(matrix.size() + 1, vector <int>(matrix[0].size() + 1, 0));
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[0].size(); j++) {
            sum[i + 1][j + 1] = sum[i][j + 1] + sum[i + 1][j] - sum[i][j] + matrix[i][j];
        }
    }
    auto calc = [&](int u, int v) {
        unordered_map <int, int> numsCnt;
        int ans = 0, numsSum = 0;
        numsCnt[0] = 1;
        for(int ind = 1; ind <= matrix[0].size(); ind++) {
            numsSum += sum[v][ind] - sum[u - 1][ind] - sum[v][ind - 1] + sum[u - 1][ind - 1];
            ans += numsCnt[numsSum - target];            
            numsCnt[numsSum]++;
        }
        return ans;
    };
    int cnt = 0;
    for(int i = 1; i <= matrix.size(); i++) {
        for(int j = i; j <= matrix[0].size(); j++) {
            cnt += calc(i, j);
        }
    }
    return cnt;
}

#include <iostream>

int main() {
    vector <vector <int>> input(5, vector<int>(6, 0));
    // [[0,1,1,1,0,1],[0,0,0,0,0,1],[0,0,1,0,0,1],[1,1,0,1,1,0],[1,0,0,1,0,0]]
    input[0][1] = input[0][2] = input[0][3] = input[0][5] = 1;
    input[1][5] = 1;
    input[2][2] = input[2][5] = 1;
    input[3][0] = input[3][1] = input[3][3] = input[3][4] = 1;
    input[4][0] = input[4][3] = 1;
    cout << numSubmatrixSumTarget(input, 0);
}