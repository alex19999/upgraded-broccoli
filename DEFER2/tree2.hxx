#ifndef _TREE2_H_
#define _TREE2_H_
enum type{
    _const,
    _value,
    _oper
};

enum oper{
    _add,
    _sub,
    _mul,
    _div,
    _ln,

};

enum prior{
    _low,
    _oper1,
    _oper2,
    _func,
};

class Node{
	public:
	double data_;
    	type type_;
    	Node* left_;
    	Node* right_;
   	Node* parent_;
	Node(Node* parent, double data, type t);
    	~Node();
	void des();
 	bool leftn(Node* tree);
    	bool nodeCmp(Node* node, type t);
    	bool nodeCmp(Node* node, type t, double data);
    	prior get_P (Node* node);
};

#endif // _TREE2_H_ //
