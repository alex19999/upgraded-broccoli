#ifndef _DEF_H_
#define _DEF_H_
#include"tree2.hxx"

class Diff{
	public:
    	Node* tree_;
    	char* buff;
    	FILE* in_;
    	Diff(Node* tree);
    	~Diff();
    	void read();
    	Node* determ(Node* curNode, Node* parent);
    	Node* d_add(Node* curNode, Node* parent);
   	Node* d_sub(Node* curNode, Node* parent);
    	Node* d_mul(Node* curNode, Node* parent);
    	Node* d_div(Node* curNode, Node* parent);
    	Node* d_ln(Node* curNode, Node* parent);
    	Node* copyNode(Node* curNode, Node* parent);
};

    	void treeDump(Node* tree);
    	void nodeDump(Node* tree, FILE* ptrFile);
    	void tex(Node* oldTree, Node* newTree);
    	void texN(Node* tree, FILE* ptrFile);

#endif // _DEF_H_ //
