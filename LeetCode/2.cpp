// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* res = new ListNode();
        for(ListNode* i = l1, * j = res; i != nullptr; i = i->next, j = j->next) {
            j->val = i->val;
            if(i->next != nullptr) {
                j->next = new ListNode();
            }
        }
        int carry = 0;
        for(ListNode* i = l2, * j = res; i != nullptr; i = i->next, j = j->next) {
            j->val += i->val + carry;
            carry = j->val / 10;
            j->val %= 10;
            if(j->next == nullptr) {
                if(i->next != nullptr) {
                    j->next = new ListNode();
                }
                else if(carry) {
                    j->next = new ListNode(carry);
                    break;
                }
            }
            else if(i->next == nullptr && carry) {
                for(ListNode* _j = j->next; _j != nullptr; _j = _j->next) {
                    _j->val += carry;
                    carry = _j->val / 10;
                    _j->val %= 10;
                    if(_j->next == nullptr && carry) {
                        _j->next = new ListNode(carry);
                        break;
                    }
                }
            }
        }
        return res;
    }
};