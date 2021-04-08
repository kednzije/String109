#include <vector>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int size1 = nums1.size(), size2 = nums2.size();
        int left = 0, right = size1;
        int left_max = 0, right_min = 0;

        while (left <= right) {
            int i = (left + right) / 2;
            int j = (size1 + size2 + 1) / 2 - i;

            int left_part_tail1 = (i == 0 ? INT_MIN : nums1[i - 1]);
            int right_part_head1 = (i == size1 ? INT_MAX : nums1[i]);
            int left_part_tail2 = (j == 0 ? INT_MIN : nums2[j - 1]);
            int right_part_head2 = (j == size2 ? INT_MAX : nums2[j]);

            if (left_part_tail1 <= right_part_head2) {
                left_max = max(left_part_tail1, left_part_tail2);
                right_min = min(right_part_head1, right_part_head2);
                left = i + 1;
            } 
            else {
                right = i - 1;
            }
        }

        return (size1 + size2) % 2 ? left_max : (left_max + right_min) / 2.0;
    }
};