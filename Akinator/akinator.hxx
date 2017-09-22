#ifndef  _AKINATOR_H_
#define _AKINATOR_H_

#include<cstdlib>
#include<cstdio>
#include<iostream>
class Node {
	public:
	char* data;
	Node(char* question,Node* no,Node* yes);
	Node* create_tree(FILE* f_in);
	void print_tree(FILE* f_out,Node* root);
	void look(Node* root);
	void akinator(Node* root);
	private:
	char* question;
	Node* left;
	Node* right;
};









































#endif /* _AKINATOR_H_ */
