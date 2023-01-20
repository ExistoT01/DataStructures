#pragma once
#include <iostream>
using namespace std;

struct LinkList
{
	float coef;
	int expn;
	LinkList* next;
	LinkList(float coef, int expn, LinkList* next) {
		this->coef = coef;
		this->expn = expn;
		this->next = next;
	}
};

class polynomial
{
public:
	polynomial();
	~polynomial();

	LinkList* getDump() { return dumpNode; }
	LinkList* getHead();
	void setHead(LinkList* node) { dumpNode->next = node; }
	LinkList* getTail();
	int getLength() { return getTail()->expn; }

private:
	LinkList* dumpNode;
};

polynomial::polynomial()
{
	dumpNode = new LinkList(0, 0, nullptr);
}

polynomial::~polynomial()
{
}

inline LinkList* polynomial::getHead()
{
	if (dumpNode->next == nullptr) {
		return nullptr;
	}
	return dumpNode->next;
}

inline LinkList* polynomial::getTail()
{
	LinkList* curNode = getDump();
	while (curNode->next != nullptr) {
		curNode = curNode->next;
	}
	return curNode;
}



LinkList* GetHead(polynomial& p) {
	return p.getHead();
}

LinkList* LocateElem(polynomial& p, LinkList* node) {
	LinkList* cur = p.getHead();
	while (cur != nullptr) {
		if (node->expn == cur->expn) {
			return cur;
		}
		cur = cur->next;
	}
	return nullptr;
}

//输入m项的系数和指数，建立表示一元多项式的有序链表P
void CreatPolyn(polynomial& p, int m) {
	float coef;
	int expn;
	while (m)
	{
		cin >> coef >> expn;
		LinkList* newNode = new LinkList(coef, expn, nullptr);
		LinkList* point = LocateElem(p, newNode);
		if (!point) {
			if (p.getHead() == nullptr)
				p.setHead(newNode);
			else
				p.getTail()->next = newNode;
		}
		m--;
	}
}

//返回一元多项式P中的项数
int PolynLenght(polynomial p) {
	return p.getLength();
}

void DestoryHelper(LinkList* curNode) {
	if (curNode->next == nullptr) {
		delete curNode;
		return;
	}
	DestoryHelper(curNode->next);
	delete curNode;
	return;
}

//销毁一元多项式P
void DestoryPolyn(polynomial& p) {
	LinkList* curNode = p.getHead();
	if (curNode == nullptr)
		return;
	DestoryHelper(curNode);
	return;
}

//打印输出一元多项式P
void PrintPolyn(polynomial p) {
	cout << "P" /*<< p.getLength()*/ << "(x) = ";
	if (p.getHead() == nullptr) {
		cout << "多项式不存在！请先创建！" << endl;
		return;
	}
	LinkList* curNode = p.getHead();
	while (curNode != nullptr) {
		if (curNode != p.getHead()) {
			if (curNode->coef > 0)
				cout << " + ";
			else
				cout << " - ";
		}

		if (fabs(curNode->coef) != 1 || curNode == p.getHead()) {
			if (curNode == p.getHead()) {
				if (curNode->coef == -1) cout << "-";
				else if (curNode->coef != 1) cout << curNode->coef;
			}
			else
				cout << fabs(curNode->coef);
		}
			
		if (curNode->expn != 0) {
			cout << "x";
			if (curNode->expn != 1) {
				cout << "^" << curNode->expn;
			}
		}
		
		curNode = curNode->next;
	}
	cout << endl;
}

void insertNode(polynomial& p, LinkList* node) {
	if (p.getDump()->next == nullptr) {
		p.getDump()->next = node;
		return;
	}
		
	LinkList* curNode = p.getDump();
	while (curNode != nullptr)
	{
		if (curNode->next == nullptr && node->expn > curNode->expn) {
			curNode->next = node;
			return;
		}
		if (node->expn > curNode->expn && node->expn < curNode->next->expn) {
			LinkList* newNode = new LinkList(node->coef, node->expn, nullptr);
			newNode->next = curNode->next;
			curNode->next = newNode;
			return;
		}
		curNode = curNode->next;
	}
}

bool ListEmpty(polynomial p) {
	return p.getHead() == nullptr;
}

void Append(polynomial& pa, polynomial& pb) {
	LinkList* curNode = pa.getDump();
	while (curNode->next != nullptr) {
		curNode = curNode->next;
	}
	LinkList* bNode = pb.getHead();
	while (bNode != nullptr) {
		LinkList* newNode = new LinkList(bNode->coef, bNode->expn, nullptr);
		curNode->next = newNode;
		curNode = curNode->next;
		bNode = bNode->next;
	}
}

//删除节点
void deleteNode(polynomial& p, LinkList* node) {
	LinkList* curNode = p.getDump();
	while (curNode != nullptr) {
		if (curNode->next == node) {
			curNode->next = node->next;
			delete(node);
			return;
		}
		curNode = curNode->next;
	}
	cout << "未找到节点！" << endl;
	return;
}

//完成多项式相加运算,即Pa=Pa+Pb,并销毁一元多项式Pb
void AddPolyn(polynomial& Pa, polynomial& Pb) {

	LinkList* nodeA = Pa.getHead();
	LinkList* nodeB = Pb.getHead();

	cout << "多项式：";
	PrintPolyn(Pa);
	cout << "多项式：";
	PrintPolyn(Pb);

	while (nodeA && nodeB) {
		if (nodeA->expn < nodeB->expn) {
			nodeA = nodeA->next;
		}
		else if (nodeA->expn == nodeB->expn) {
			float coef = nodeA->coef + nodeB->coef;
			if (coef == 0.0) {
				LinkList* delNode = nodeA;
				nodeA = nodeA->next;
				deleteNode(Pa, delNode);
			}
			else {
				nodeA->coef = coef;
				nodeA = nodeA->next;
			}
			LinkList* delNode = nodeB;
			nodeB = nodeB->next;
			deleteNode(Pb, delNode);

		}
		else if (nodeA->expn > nodeB->expn) {
			insertNode(Pa, nodeB);
			LinkList* delNode = nodeB;
			nodeB = nodeB->next;
			deleteNode(Pb, delNode);
		}
	}

	if (!ListEmpty(Pb))
		Append(Pa, Pb);

	cout << "加和结果：";
	PrintPolyn(Pa);

	DestoryPolyn(Pb);

	return;
}

polynomial* MutiPolyn(polynomial& Pa, polynomial& Pb) {
	polynomial* ans = new polynomial();

	LinkList* cur = Pa.getHead();
	
	while (cur) {
		LinkList* target = Pb.getHead();
		while(target){
			LinkList* newNode = new LinkList(cur->coef * target->coef,
				cur->expn + target->expn, nullptr);
			LinkList* point = LocateElem(*ans, newNode);
			if (point) {
				if (point->coef + newNode->coef == 0) {
					deleteNode(*ans, point);
				}
				else {
					point->coef += newNode->coef;
				}
			}
			else {
				insertNode(*ans, newNode);
			}
			target = target->next;
		}

		cur = cur->next;
	}

	return ans;
}




