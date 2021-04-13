#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution {
    struct Board {
        vector <vector <int>> board;
        int zx, zy;
        Board() {
            board = vector <vector <int>>(2, vector <int>(3));
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 3; j++) {
                    board[i][j] = i * 3 + j;
                }
            }
            board[1][2] = 0;
            zx = 1, zy = 2;
        }
        Board(vector <vector <int>> b) {
            board = b;
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 3; j++) {
                    if(!board[i][j]) {
                        zx = i, zy = j;
                    }
                }
            }
        }
        Board move(int k) {
            Board b = Board(board);
            switch(k) {
            case 0: case 2:
                if(zx + (k - 1) < 2 && zx + (k - 1) >= 0) {
                    swap(b.board[zx][zy], b.board[zx + (k - 1)][zy]);
                }
                return b;
            case 1: case 3:
                if(zy + (k - 2) < 3 && zy + (k - 2) >= 0) {
                    swap(b.board[zx][zy], b.board[zx][zy + (k - 2)]);
                }
                return b;
            default:
                return b;
            }
        }
        int hash() const {
            int h = 0;
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 3; j++) {
                    h = h * 10 + board[i][j];
                }
            }
            return h;
        }
        int _f, _g, _h;
        int StarH() {
            int h = 0;
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 3; j++) {
                    int k = i * 3 + j;
                    h += abs((board[i][j] ? board[i][j] : 5) - k);
                }
            }
            return h;
        }
        void setG(int g) {
            _g = g, _h = StarH();
            _f = _g + _h;
        }
        bool operator < (const Board& b) {
            return _f > b._f;
        }
    };
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        Board target = Board();
        unordered_set <int> seen;
        Board root = Board(board);
        root.setG(0);
        seen.insert(root.hash());
        priority_queue <Board> que;
        que.push(root);
        while(!que.empty()) {
            Board head = que.top();
			que.pop();
			for(int i = 0; i < 4; i++) {
				Board b = head.move(i);
				if(seen.count(b.hash())) {
					continue;
				}
				b.setG(head._g + 1);
				if(b.hash() == target.hash()) {
					return b._g;
				}
				que.push(b);
			}
        }
		return -1;
    }
};