#ifndef _DEF_H_
#define _DEF_H

#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<iostream>
#include<cstring>

class Node {
	public:
	Node* create_tree(FILE* f_in);
	void look(Node* root);
	const char* ret(Node* root);
	int determ(Node* root);
	void print_tree(FILE* f_out,Node* root);
	Node* def(Node* root);
	int priority(Node* root);
 	Node(const char* oper,Node* left,Node* right);
	private:
	const char* oper;
	Node* left;
	Node* right;
};

#endif /* _DEF_H_ */
