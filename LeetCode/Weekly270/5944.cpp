/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#include <string>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

// class Solution {
// 	map <int, long long> val_to_ind;
// 	void dfs(TreeNode *node, long long ind) {
// 		if(node == nullptr) {
// 			return;
// 		}
// 		val_to_ind[node->val] = ind;
// 		dfs(node->left, ind * 2), dfs(node->right, ind * 2 + 1);
// 	}
// public:
//     string getDirections(TreeNode* root, int startValue, int destValue) {
//         dfs(root, 1);
// 		int startIndex = val_to_ind[startValue], destIndex = val_to_ind[destValue];
// 		string path[2];
// 		while((int)log2(startIndex) > (int)log2(destIndex)) {
// 			path[0].push_back('U');
// 			startIndex /= 2;
// 		}
// 		while((int)log2(startIndex) < (int)log2(destIndex)) {
// 			path[1] = (destIndex % 2 == 0 ? 'L' : 'R') + path[1];
// 			destIndex /= 2;
// 		}
// 		while(startIndex != destIndex) {
// 			path[0].push_back('U');
// 			startIndex /= 2;
// 			path[1] = (destIndex % 2 == 0 ? 'L' : 'R') + path[1];
// 			destIndex /= 2;
// 		}
// 		return path[0] + path[1];
//     }
// };

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
	bool getPath(TreeNode *node, const int val, string &path) {
		if(node->val == val) {
			return true;
		}
		if(node->left != nullptr && getPath(node->left, val, path)) {
			path = "L" + path;
			return true;
		}
		if(node->right != nullptr && getPath(node->right, val, path)) {
			path = "R" + path;
			return true;
		}
		return false;
	}
public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        string startPath, destPath;
		getPath(root, startValue, startPath);
		getPath(root, destValue, destPath);
		int layerIndex;
		for(layerIndex = 0; 
			layerIndex < startPath.length()
			&& layerIndex < destPath.length()
			&& startPath[layerIndex] == destPath[layerIndex]; 
			layerIndex++);
		string toFather(startPath.length() - layerIndex, 'U');
		return toFather + destPath.substr(layerIndex, destPath.length());
    }
};