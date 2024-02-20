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
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head)
            return NULL;
        ListNode* rvr_head = head;
        ListNode* go = head->next;
        while(go)
        {
            auto nxt = go->next;
            if(nxt){
                go->next = rvr_head;
                rvr_head = go;
            }
            go = nxt;
        }
        return rvr_head;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
