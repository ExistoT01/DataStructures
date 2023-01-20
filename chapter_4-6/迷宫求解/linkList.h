#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>
using namespace std;
#include <string>

struct PosType
{
	int x;
	int y;
	string dir;//·½Ïò
	int index;//ÐòºÅ
	PosType() : x(0), y(0), dir(""), index(0) {}
	PosType(int x, int y, string dir, int index) :x(x), y(y), dir(dir), index(index) {}
};

struct ListNode {
	PosType val;
	ListNode* next;
	ListNode() : val(PosType()), next(nullptr) {}
	ListNode(PosType p) : val(p), next(nullptr) {}
	ListNode(PosType p, ListNode* next) : val(p), next(next) {}
};

