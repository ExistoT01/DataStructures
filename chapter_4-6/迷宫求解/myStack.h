#pragma once
#include "linkList.h"



class MyStack {
private:
    ListNode* dump;
    ListNode* head;

public:
    MyStack() {
        dump = new ListNode(PosType());
        head = nullptr;
    }

    ListNode* getHead() { return head; }

	void push(PosType p) {
		ListNode* newNode = new ListNode(p);
		if (empty()) {
			head = newNode;
			dump->next = head;
		}
		else {
			newNode->next = head;
            head = newNode;
            dump->next = head;
		}
	}

    bool pop() {
        if (empty()) return false;
        ListNode* delNode = head;
        head = head->next;
        dump->next = head;
        delete delNode;
        return true;
    }

    PosType top() {
        if (empty())return PosType(-1, -1, "", 0);
        return head->val;
    }

    bool empty() {
        if (dump->next) return false;
        else return true;
    }

    void printStack() {
        if (empty())return;
        ListNode* cur = head;
        while (cur) {
            cout << "( " << cur->val.x << ", " << cur->val.y << " ) -> ";
            cur = cur->next;
        }
        cout << endl;
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
