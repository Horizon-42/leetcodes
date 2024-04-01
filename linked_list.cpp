#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode *prev;
    ListNode(int val_, ListNode *next_, ListNode *prev_) : val(val_), next(next_), prev(prev_) {}
};

class LinkedList
{

public:
    ListNode *GetHead() { return head_; }

    LinkedList()
    {
        head_ = NULL;
        tail_ = NULL;
        size_ = 0;
    }

    int get(int index)
    {
        if (index < 0 || index >= size_)
            return -1;
        return get_iter_at(index)->val;
    }

    void addAtHead(int val)
    {
        ListNode *n = new ListNode{val, NULL, NULL};
        if (head_ == NULL)
            tail_ = n;
        n->next = head_;
        if (head_ != NULL)
            head_->prev = n;
        head_ = n;
        size_++;
    }

    void addAtTail(int val)
    {
        ListNode *n = new ListNode{val, NULL, NULL};
        if (tail_ == NULL)
            head_ = n;
        n->prev = tail_;
        if (tail_ != NULL)
            tail_->next = n;
        tail_ = n;
        size_++;
    }

    void addAtIndex(int index, int val)
    {
        if (index < 0 || index > size_)
            return;
        if (index == size_)
        {
            return addAtTail(val);
        }
        if (index == 0)
        {
            return addAtHead(val);
        }
        ListNode *pos = get_iter_at(index);
        ListNode *n = new ListNode{val, NULL, NULL};
        pos->prev->next = n;
        n->prev = pos->prev;
        pos->prev = n;

        n->next = pos;
        size_++;
    }

    void deleteAtIndex(int index)
    {
        if (index < 0 || index >= size_)
            return;
        auto pos = get_iter_at(index);
        if (pos->prev == NULL)
            head_ = pos->next;
        else
            pos->prev->next = pos->next;
        if (pos->next == NULL)
            tail_ = pos->prev;
        else
            pos->next->prev = pos->prev;
        delete (pos);
        size_--;
    }

    void print_vals()
    {
        for (int i = 0; i < size_; i++)
            std::cout << get(i) << "\t";
        std::cout << "\n";
    }

private:
    ListNode *head_;
    ListNode *tail_;
    int size_;

    ListNode *get_iter_at(int index)
    {
        ListNode *step = head_;
        while (index > 0)
        {
            step = step->next;
            index--;
        }

        return step;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */

/*
["MyLinkedList","addAtHead","addAtTail","addAtIndex","get","deleteAtIndex","get"]
[[],[1],[3],[1,2],[1],[0],[0]]
*/

/*
["MyLinkedList","addAtIndex","addAtIndex","addAtIndex","get"]
[[],[0,10],[0,20],[1,30],[0]]
*/

/*
["MyLinkedList","addAtHead","addAtIndex","addAtTail","addAtHead","addAtIndex","addAtTail","addAtTail","addAtIndex","deleteAtIndex","deleteAtIndex","addAtTail"]
[[],[0],[1,4],[8],[5],[4,3],[0],[5],[6,3],[7],[5],[4]]
*/

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
class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (!head)
            return NULL;
        ListNode *rvr_head = head;
        ListNode *go = head->next;
        while (go)
        {
            ListNode *nxt = go->next;
            go->next = rvr_head;
            rvr_head = go;
            go = nxt;
        }
        head->next = NULL;
        return rvr_head;
    }

    ListNode *oddEvenList(ListNode *head)
    {
        if (!head)
            return NULL;
        auto odd = head;
        auto even = head->next;
        auto e_start = even;
        while (even)
        {
            odd->next = even->next;
            if (!odd->next)
                break;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = e_start;
        return head;
    }

    bool isPalindrome(ListNode *head)
    {
        if (!head || !head->next)
            return true;
        int len = 0;
        ListNode *tail = NULL, *head2 = NULL;
        auto go = head;
        while (go)
        {
            len++;
            go = go->next;
        }
        cout << len << "\n";
        int tail_id, head2_id;
        if (len % 2 == 0)
        {
            tail_id = len / 2 - 1;
            head2_id = len / 2;
        }
        else
        {
            tail_id = len / 2 - 1;
            head2_id = len / 2 + 1;
        }
        go = head;
        len = 0;
        while (go)
        {
            if (len == tail_id)
                tail = go;
            if (len == head2_id)
            {
                head2 = go;
                break;
            }
            go = go->next;
            len++;
        }

        cout << tail->val << "\t" << head2->val << "\n";

        // 逆转后半链表
        tail->next = NULL;

        auto rv_head2 = head2;
        go = head2->next;
        while (go)
        {
            auto tmp = go->next;
            go->next = rv_head2;
            rv_head2 = go;
            go = tmp;
        }
        head2->next = NULL;
        while (head && rv_head2)
        {
            if (head->val != rv_head2->val)
                return false;
            head = head->next;
            rv_head2 = rv_head2->next;
        }
        return head == NULL && rv_head2 == NULL;
    }
};

int main()
{
    LinkedList *obj = new LinkedList();
    // obj->addAtHead(1);
    // obj->addAtTail(3);
    // obj->addAtIndex(1,2);
    // std::cout<<obj->get(1)<<"\n";
    // obj->deleteAtIndex(0);
    // std::cout<<obj->get(0)<<"\n";
    // obj->addAtIndex(0,10);
    // obj->addAtIndex(0,20);
    // obj->addAtIndex(1,30);
    // std::cout<<obj->get(0)<<"\n";

    // obj->addAtHead(0);
    // obj->print_vals();

    // obj->addAtIndex(1,4);
    // obj->print_vals();

    // obj->addAtTail(8);
    // obj->print_vals();

    // obj->addAtHead(5);
    // obj->print_vals();

    // obj->addAtIndex(4,3);
    // obj->print_vals();

    // obj->addAtTail(0);
    // obj->print_vals();

    // obj->addAtTail(5);
    // obj->print_vals();

    // obj->addAtIndex(6,3);
    // obj->print_vals();

    // obj->deleteAtIndex(7);
    // obj->print_vals();

    // obj->deleteAtIndex(5);
    // obj->print_vals();

    // obj->addAtTail(4);
    // std::cout<<"Final: ";
    // obj->print_vals();

    // obj->addAtTail(1);
    // obj->addAtTail(2);
    // obj->addAtTail(3);
    // obj->addAtTail(4);
    // obj->addAtTail(5);

    obj->addAtTail(1);
    obj->addAtTail(2);
    obj->addAtTail(3);
    obj->addAtTail(2);
    obj->addAtTail(1);

    Solution *sol = new Solution();
    // ListNode* rvr = sol->reverseList(obj->GetHead());
    // std::cout<<"\n";
    // while(rvr)
    // {
    //     std::cout<<rvr->val<<"\t";
    //     rvr = rvr->next;
    // }

    // auto odd_even = sol->oddEvenList(obj->GetHead());
    // std::cout<<"\n";
    // while(odd_even)
    // {
    //     std::cout<<odd_even->val<<"\t";
    //     odd_even = odd_even->next;
    // }

    std::cout << sol->isPalindrome(obj->GetHead()) << "\n";

    std::string s;
    s.substr();

    return 0;
}