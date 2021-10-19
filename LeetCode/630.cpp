#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	int scheduleCourse(vector<vector<int>>& courses) {
		sort(courses.begin(), courses.end(), [](const vector<int> &a, const vector<int> &b) {
			return a[1] < b[1];
		});

		priority_queue<int> que;
		
		int total = 0;

		for (const auto& course: courses) {
			int ti = course[0], di = course[1];
			if (total + ti <= di) {
				total += ti;
				que.push(ti);
			}
			else if (!que.empty() && que.top() > ti) {
				total -= que.top(), total += ti;
				que.pop(), que.push(ti);
			}
		}

		return que.size();
	}
};