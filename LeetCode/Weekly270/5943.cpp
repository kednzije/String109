/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
		if(head == nullptr) {
			return head;
		}
		if(head->next == nullptr) {
			delete head;
			return nullptr;
		}
        ListNode *fast = head, *slow = head;
		while(fast != nullptr) {
			if(fast->next != nullptr) {
				fast = fast->next->next;
			}
			else {
				fast = fast->next;
			}
			if(fast == nullptr || fast->next == nullptr) {
				ListNode* to_delete = slow->next;
				slow->next = to_delete->next;
				delete to_delete;
				break;
			}
			slow = slow->next;
		}
		return head;
    }
};