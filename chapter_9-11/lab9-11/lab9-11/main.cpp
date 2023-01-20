#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <iomanip>
using namespace std;

// huffman tree node
struct TreeNode
{
	char val;// the data of the node
	int weight;

	TreeNode* left, * right;

	TreeNode(char _val, int _weight) {
		this->val = _val;
		this->weight = _weight;
		left = right = NULL;
	}
};

// struct for compare tree node
struct Compare
{
	bool operator()(TreeNode* left, TreeNode* right) {
		return (left->weight > right->weight);
	}
};

class Solution {
private:
	int n;// size
	vector<char> arr;
	vector<int> weight;
	
	unordered_map<char, int> freq;// to store the frequency of character of the input data
	unordered_map<char, string> prefixCodes;// each character's prefix code

	TreeNode* root;// huffman tree

	vector<string> tree;// tree in graph

public:
	Solution() { 
		root = NULL;
		n = 0;
	}

	void Menu() {
		cout << "------------------|| huffmanCode Program ||------------------" << endl;
		cout << endl;
		cout << "                     1.Initialization" << endl;
		cout << "                     2.Encoding" << endl;
		cout << "                     3.Decoding" << endl;
		cout << "                     4.Print" << endl;
		cout << "                     5.Tree printing" << endl;
		cout << "                     0.Exit" << endl;
		cout << endl;
		cout << "------------------|| 20020007095 YePeng  ||------------------" << endl;

		cout << "Your choice: ";
	}

	// 5 main functions
	void Initialization();
	void Encoding();
	void Decoding();
	void Print();
	void TreePrinting();

	TreeNode* BuildHuffmanTree();// build the tree
	void calcAllNeeded();// calulate num of character and the frequence of character
	void storeCodes(TreeNode* node, string prefix);// store each character's prefix code
	void prettyPrintTree(TreeNode* node, vector<string>& tree, string prefix = "", bool isLeft = true);// Print tree
};

int main() {
	Solution solution;
	int choice;
	bool flag = true;
	
	while (flag) {
		system("cls");
		solution.Menu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			solution.Initialization();
			break;
		case 2:
			system("cls");
			solution.Encoding();
			break;
		case 3:
			system("cls");
			solution.Decoding();
			break;
		case 4:
			system("cls");
			solution.Print();
			break;
		case 5:
			system("cls");
			solution.TreePrinting();
			break;
		case 0:
			flag = false;
			break;
		default:
			system("cls");
			cout << "Error: choice not valid";
			system("timeout -t 5");
			system("cls");
			break;
		}
	}

	return 0;
}

// ���ն˶����ַ�����Сn���Լ�n���ַ���n��Ȩֵ���������������������������ļ�hfmTree�С�
void Solution::Initialization()
{
	// Manual input
	
	//cout << "the size of input: ";
	//cin >> n;
	//arr.resize(n);
	//weight.resize(n);

	//cout << "the characters: ";
	//for (int i = 0; i < n; ++i)cin >> arr[i];
	//cout << "the weights: ";
	//for (int i = 0; i < n; ++i)cin >> weight[i];	

	// store data in hfmTree.txt

	// automatic input
	calcAllNeeded();
	n = freq.size();
	arr.resize(n);
	weight.resize(n);

	int cnt = 0;
	for (auto it = freq.begin(); it != freq.end(); ++it) {
		arr[cnt] = (*it).first;
		weight[cnt] = (*it).second;
		cnt++;
	}

	fstream file;
	file.open("hfmTree.txt", ios::in | ios::out | ios::trunc);

	file << n;
	file << endl;
	for (int i = 0; i < n; ++i)file << arr[i] << " ";
	file << endl;
	for (int i = 0; i < n; ++i)file << weight[i] << " ";

	file.close();

	// build the tree
	root = BuildHuffmanTree();

	cout << "------------------||     Prefix Codes    ||------------------" << endl;
	cout << setw(20) << right << "Character" << setw(20) << right << "Preix Code" << endl;
	cout << endl;
	for (auto it = prefixCodes.begin(); it != prefixCodes.end(); ++it) {
		cout << setw(20) << right << (*it).first << setw(20) << right << (*it).second << endl;
	}
	cout << endl;
	cout << "------------------|| huffmanCode Program ||------------------" << endl;

	system("pause");
}

// �����ѽ��õĹ����������粻���ڴ棬����ļ�hfmTree�ж��룩�����ļ�ToBeTran�е����Ľ��б��룬Ȼ�󽫽�������ļ�CodeFile�С�
void Solution::Encoding()
{
	fstream file;
	// check if tree exist
	if (root == NULL) {
		// read data from hfmTree.txt
		file.open("hfmTree.txt", ios::in);

		file >> n;
		arr.resize(n);
		weight.resize(n);

		for (int i = 0; i < n; ++i)file >> arr[i];
		for (int i = 0; i < n; ++i)file >> weight[i];

		file.close();

		root = BuildHuffmanTree();
	}

	file.open("ToBeTran.txt", ios::in);

	string text;
	file >> text;

	file.close();

	file.open("CodeFile.txt", ios::in | ios::out | ios::trunc);

	for (int i = 0; i < text.size(); ++i) {
		file << prefixCodes[text[i]];
	}

	file.close();

	cout << "------------------||   Encoding Process  ||------------------" << endl;

	cout << setw(40) << right << "Successfully encoded!" << endl;

	cout << "------------------|| huffmanCode Program ||------------------" << endl;

	system("pause");
}

// �����ѽ��õĹ����������ļ�CodeFile�еĴ���������룬��������ļ�TextFile�С�
void Solution::Decoding()
{
	fstream file;
	// check if tree exist
	if (root == NULL) {
		// read data from hfmTree.txt
		file.open("hfmTree.txt", ios::in);

		file >> n;
		arr.resize(n);
		weight.resize(n);

		for (int i = 0; i < n; ++i)file >> arr[i];
		for (int i = 0; i < n; ++i)file >> weight[i];

		file.close();

		root = BuildHuffmanTree();
	}

	file.open("CodeFile.txt", ios::in);
	string code;
	file >> code;
	file.close();

	file.open("TextFile.txt", ios::in | ios::out | ios::trunc);

	TreeNode* cur = root;
	for (int i = 0; i < code.size(); ++i) {
		if (code[i] == '0')cur = cur->left;
		else cur = cur->right;

		// if leaf
		if (!cur->left && !cur->right) {
			file << cur->val;
			cur = root;
		}
	}

	file.close();

	cout << "------------------||   Decoding Process  ||------------------" << endl;

	cout << setw(40) << right << "Successfully decoded!" << endl;

	cout << "------------------|| huffmanCode Program ||------------------" << endl;

	system("pause");
}

// ���ļ�CodeFile�Խ��ո�ʽ��ʾ���ն��ϣ�ÿ��50�����롣ͬʱ�����ַ���ʽ�ı����ļ�д���ļ�CodePrin�С�
void Solution::Print()
{
	// read from CodeFile
	fstream file;
	file.open("CodeFile.txt", ios::in);
	string code;
	file >> code;
	file.close();

	file.open("CodePrin.txt", ios::in | ios::out | ios::trunc);

	cout << "-------------||       CodeFile      ||-------------" << endl;
	for (int i = 0; i < code.size(); ++i) {
		if (i % 50 == 0) {
			cout << endl;
			if(i)file << endl;
		}
		cout << code[i];
		file << code[i];
	}
	cout << endl;
	cout << endl;
	cout << "-------------|| huffmanCode Program ||-------------" << endl;
	system("pause");
}

// �������ڴ��еĹ���������ֱ�۵ķ�ʽ�����������ʽ����ʾ���ն��ϣ�ͬʱ�����ַ���ʽ�Ĺ�������д���ļ�TreePrint�С�
void Solution::TreePrinting()
{
	fstream file;
	// check if tree exist
	if (root == NULL) {
		// read data from hfmTree.txt
		file.open("hfmTree.txt", ios::in);

		file >> n;
		arr.resize(n);
		weight.resize(n);

		for (int i = 0; i < n; ++i)file >> arr[i];
		for (int i = 0; i < n; ++i)file >> weight[i];

		file.close();

		root = BuildHuffmanTree();
	}

	file.open("TreePrint.txt", ios::in | ios::out | ios::trunc);

	prettyPrintTree(root, tree, "", true);
	for (int i = 0; i < tree.size(); ++i) file << tree[i];

	file.close();

	system("pause");
}

TreeNode* Solution::BuildHuffmanTree()
{
	int n = arr.size();// get the size

	priority_queue<TreeNode*, vector<TreeNode*>, Compare> nodes;

	for (int i = 0; i < n; ++i)nodes.emplace(new TreeNode(arr[i], weight[i]));

	while (nodes.size() != 1) {
		auto left = nodes.top();
		nodes.pop();

		auto right = nodes.top();
		nodes.pop();

		auto newNode = new TreeNode('$', left->weight + right->weight);
		newNode->left = left;
		newNode->right = right;

		nodes.emplace(newNode);
	}

	// store codes
	storeCodes(nodes.top(), "");

	return nodes.top();
}

void Solution::calcAllNeeded()
{
	// read from ToBeTran
	fstream file;
	file.open("ToBeTran.txt", ios::in);
	string text;
	file >> text;
	
	// count each character
	for (int i = 0; i < text.size(); ++i)freq[text[i]]++;

	file.close();
}

void Solution::storeCodes(TreeNode* node, string prefix)
{
	if (!node)return;
	if (node->val != '$')
		prefixCodes[node->val] = prefix;
	storeCodes(node->left, prefix + '0');
	storeCodes(node->right, prefix + '1');
}

void Solution::prettyPrintTree(TreeNode* node, vector<string>& tree, string prefix, bool isLeft)
{
	if (node == nullptr) {
		cout << "Empty tree";
		return;
	}

	if (node->right) {
		prettyPrintTree(node->right, tree, prefix + (isLeft ? "��   " : "    "), false);
	}

	cout << prefix + (isLeft ? "������ " : "������ ") + node->val + '[' + to_string(node->weight) + ']' + "\n";
	tree.emplace_back(prefix + (isLeft ? "������ " : "������ ") + node->val + '[' + to_string(node->weight) + ']' + "\n");


	if (node->left) {
		prettyPrintTree(node->left, tree, prefix + (isLeft ? "    " : "��   "), true);
	}
}
