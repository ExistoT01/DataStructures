#include <iostream>
#include "LinkList.h"
using namespace std;

int main() {

	//polynomial p1, p2;
	//CreatPolyn(p1, 2);
	//CreatPolyn(p2, 3);

	//AddPolyn(p1, p2);

	polynomial p3, p4;
	CreatPolyn(p3, 2);
	CreatPolyn(p4, 3);

	cout << "����ʽ��";
	PrintPolyn(p3);
	cout << "����ʽ��";
	PrintPolyn(p4);
	
	cout << "��˽����";
	PrintPolyn(*MutiPolyn(p3, p4));

	return 0;
}