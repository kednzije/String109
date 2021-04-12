#include <string>
#include <regex>
#include <map>
#include <queue>
#include <sstream>
#include <iostream>
using namespace std;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        map <int, TreeNode*> table;
        map <TreeNode*, int> ind;
        queue <TreeNode*> que;
        que.push(root);
        table[1] = root;
        ind[root] = 1;
        int n = 1;
        while(!que.empty()) {
            TreeNode* node = que.front();
            que.pop();
            if(node->left != NULL) {
                que.push(node->left);
                table[ind[node] * 2] = node->left;
                ind[node->left] = ind[node] * 2;
                n = max(n, ind[node] * 2);
            }
            if(node->right != NULL) {
                que.push(node->right);
                table[ind[node] * 2 + 1] = node->right;
                ind[node->right] = ind[node] * 2 + 1;
                n = max(n, ind[node] * 2 + 1);
            }
        }   
        string series;     
        for(int i = 1; i <= n; i++) {
            if(table[i] == NULL) {
                series += "null,";
            }
            else {
                series += to_string(table[i]->val) + ',';
            }
        }
        series.pop_back();
        return series;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        regex reg(",");
        sregex_token_iterator pos(data.begin(), data.end(), reg, -1);
        decltype(pos) end;
        int i = 1;
        map <int, TreeNode*> table;
        for(; pos != end; pos++) {
            if(pos->str() == "") {
                continue;
            }
            string val = pos->str();
            if(val == "null") {
                i++;
                continue;
            }
            int num;
            stringstream stream;
            stream << val;
            stream >> num;
            TreeNode* node = new TreeNode(num);
            table[i] = node;
            if(i / 2) {
                if(i % 2) {
                    table[i / 2]->right = node;
                }
                else {
                    table[i / 2]->left = node;
                }
            }
            i++;
        }
        // for(int j = 1; j <= i; j++) {
        //     if(table[j]) {
        //         cout << table[j]->val << ' ';
        //     }
        //     else {
        //         cout << "null" << ' ';
        //     }
        // }
        // cout << endl;
        return table[1];
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

int main() {
    string str;
    Codec ser, deser;
    cin >> str;
    cout << ser.serialize(deser.deserialize(str));
    return 0;
}