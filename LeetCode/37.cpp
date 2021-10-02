#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
class Solution {
    uint16_t row[9], col[9], block[3][3];
    bool check_row(int i, int j, int k) {
        return (row[i] >> (k - 1)) & 1;
    }
    bool check_col(int i, int j, int k) {
        return (col[j] >> (k - 1)) & 1;
    }
    bool check_block(int i, int j, int k) {
        return (block[i / 3][j / 3] >> (k - 1)) & 1;
    }
    bool check_num(int i, int j, int k) {
        return check_row(i, j, k) || check_col(i, j, k) || check_block(i, j, k);
    }
    void set_row(int i, int j, int k) {
        row[i] |= (1 << (k - 1));
    }
    void set_col(int i, int j, int k) {
        col[j] |= (1 << (k - 1));
    }
    void set_block(int i, int j, int k) {
        block[i / 3][j / 3] |= (1 << (k - 1));
    }
    void set_num(int i, int j, int k) {
        set_row(i, j, k), set_col(i, j, k), set_block(i, j, k);
    }
    void clear_row(int i, int j, int k) {
        row[i] ^= (1 << (k - 1));
    }
    void clear_col(int i, int j, int k) {
        col[j] ^= (1 << (k - 1));
    }
    void clear_block(int i, int j, int k) {
        block[i / 3][j / 3] ^= (1 << (k - 1));
    }
    void clear_num(int i, int j, int k) {
        clear_row(i, j, k), clear_col(i, j, k), clear_block(i, j, k);
    }
    bool is_full(vector<vector<char>>& board) {
        // for(int i = 0; i < 9; i++) {
        //     for(int j = 0; j < 9; j++) {
        //         if(board[i][j] == '.') {
        //             return false;
        //         }
        //     }
        // }
		for(int i = 0; i < 9; i++) {
			if(row[i] != (1 << 9) - 1) {
				return false;
			}
		}
        return true;
    }
	int lowbit(int num) {
		return num & (-num);
	}
	int one_step_row(int i, int j) {
		if(~row[i] == lowbit(~row[i])) {
			for(int k = 1; k <= 9; k++) {
				if((~row[i] >> (k - 1)) & 1) {
					return k;
				}
			}
		}
		return -1;
	}
	int one_step_col(int i, int j) {
		if(~col[j] == lowbit(~col[i])) {
			for(int k = 1; k <= 9; k++) {
				if((~col[j] >> (k - 1)) & 1) {
					return k;
				}
			}
		}
		return -1;
	}
	int one_step_block(int i, int j) {
		if(~block[i / 3][j / 3] == lowbit(~block[i / 3][j / 3])) {
			for(int k = 1; k <= 9; k++) {
				if((~block[i / 3][j / 3] >> (k - 1)) & 1) {
					return k;
				}
			}
		}
		return -1;
	}
	void one_step_solution(vector<vector<char>>& board) {
		int one_step_k;
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++) {
				one_step_k = -1;
				if(one_step_k == -1) {
					one_step_k = one_step_row(i, j);
				}
				if(one_step_k == -1) {
					one_step_k = one_step_col(i, j);
				}
				if(one_step_k == -1) {
					one_step_k = one_step_block(i, j);
				}
				if(one_step_k != -1) {
					board[i][j] = '0' + one_step_k;
				}
			}
		}
	}
    bool dfs(vector<vector<char>>& board) {
		one_step_solution(board);
        if(is_full(board)) {
            return true;
        }
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(board[i][j] != '.') {
                    continue;
                }
                for(int k = 1; k <= 9; k++) {
                    if(check_num(i, j, k)) {
                        continue;
                    }
                    board[i][j] = '0' + k;
                    set_num(i, j, k);
                    if(dfs(board)) {
                        return true;
                    }
                    board[i][j] = '.';
                    clear_num(i, j, k);
                }
                return false;
            }
        }
        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(block));
        memset(block, 0, sizeof(block));
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(board[i][j] != '.') {
                    set_row(i, j, board[i][j] - '0');
                    set_col(i, j, board[i][j] - '0');
                    set_block(i, j, board[i][j] - '0');
                }
            }
        }
        dfs(board);
    }
};

int main() {
	Solution sol;
	vector <vector <char>> board = {
		{ '5', '3', '.', '.', '7', '.', '.', '.', '.' },
		{ '6', '.', '.', '1', '9', '5', '.', '.', '.' },
		{ '.', '9', '8', '.', '.', '.', '.', '6', '.' },
		{ '8', '.', '.', '.', '6', '.', '.', '.', '3' },
		{ '4', '.', '.', '8', '.', '3', '.', '.', '1' },
		{ '7', '.', '.', '.', '2', '.', '.', '.', '6' },
		{ '.', '6', '.', '.', '.', '.', '2', '8', '.' },
		{ '.', '.', '.', '4', '1', '9', '.', '.', '5' },
		{ '.', '.', '.', '.', '8', '.', '.', '7', '9' }
	};
	sol.solveSudoku(board);
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			cout << board[i][j] << ' ';
		}
		cout << endl;
	}
}