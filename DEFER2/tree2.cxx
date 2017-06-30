#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include "tree2.hxx"

Node :: Node (Node* parent, double data, type t):
    	data_   (data),
    	type_   (t),
    	left_   (NULL),
    	right_  (NULL),
    	parent_ (parent)
{}


Node :: ~Node () { left_ = right_ = parent_ = NULL; }


bool Node :: leftn (Node* curNode) {
    	assert (curNode->parent_);
    	return (curNode == curNode->parent_->left_);
}

void Node :: des () {
    	if (left_)   left_->des ();
    	if (right_) right_->des ();
    	if (this) { delete this; }
}

bool Node::nodeCmp (Node* node, type t, double data) {
    	if (!node) return false;
    	return (node->type_ == t && (int) node->data_ == (int) data)? true: false;
}

bool Node :: nodeCmp (Node* node, type t){
    	if (!node) return false;
    	return (node->type_ == t)? true: false;
}

Prior Node :: get_P(Node* node){
    	if (node->nodeCmp(node, _oper, _add)) return _oper1;
    	if (node->nodeCmp(node, _oper, _sub)) return _oper1;
    	if (node->nodeCmp(node, _oper, _mul)) return _oper2;
    	if (node->nodeCmp(node, _oper, _div)) return _oper2;
    	if (node->nodeCmp(node, _oper, _ln )) return _func;
    	return _low;
}
