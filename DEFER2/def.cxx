#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include "def.hxx"



Diff :: Diff (Node* tree):
    	tree_  (tree),
    	buff (NULL)
{}


Diff :: ~Diff () {
    	delete [] buffer;
} 


Node* Diff :: d_add (Node* curNode, Node* parent){
    	Node* plus   = new Node  (parent, _add, _oper);
    	plus->left_  = determ (curNode-> left_, plus);
    	plus->right_ = determ (curNode->right_, plus);
    	return plus;
}

Node* Diff :: d_sub (Node* curNode, Node* parent) {
    	Node* minus   = new Node  (parent, _sub, _oper);
    	minus->left_  = determ (curNode-> left_, minus);
    	minus->right_ = determ (curNode->right_, minus);
    	return minus;
}

Node* Diff :: d_mul (Node* curNode, Node* parent) {
    	Node* plus   = new Node (parent, _add, _oper);
    	plus->left_  = new Node (plus,   _mul, _oper);
    	plus->right_ = new Node (plus,   _mul, _oper);
    	plus->left_->left_  = determ (curNode-> left_, plus->left_);
    	plus->left_->right_ = copyNode (curNode->right_, plus->left_);
    	plus->right_->left_ = copyNode (curNode->left_, plus->right_);
    	plus->right_->right_= determ (curNode->right_, plus->right_);
    	return plus;
}


Node* Diff::d_div (Node* curNode, Node* parent) {
    	Node* div = new Node (parent, _div, _oper);
    	div->left_ = new Node (div, _sub, _oper);
    	div->right_ = new Node (div, _mul, _oper);
    	div->left_->left_ = new Node (div->left_, _mul, _oper);
    	div->left_->right_ = new Node(div->left_, _mul, _oper);
    	div->left_->left_->left_ = determ(curNode->left_, div->left_->left_);
    	div->left_->left_->right_ = copyNode (curNode->right_, div->left_->left_);
    	div->left_->right_->left_ = copyNode (curNode->left_, div->left_->right_);
    	div->left_->right_->right_ = determ (curNode->right_, div->left_->right_);
    	div->right_->left_  = copyNode (curNode->right_, div->right_);
    	div->right_->right_ = copyNode (curNode->right_, div->right_);
	return div;
}


Node* Diff :: d_ln (Node* curNode, Node* parent) {
    	Node* mul  = new Node  (parent, _mul, _oper);
    	mul->left_ = new Node  (mul, _div, _oper);
    	mul->left_->left_  = new Node (mul->left_, 1, _const);
    	mul->left_->right_ = copyNode (curNode->left_, mul->left_);
    	mul->right_ = determ (curNode->left_, mul);
    	return mul;
}


Node* Diff :: copyNode (Node* curNode, Node* parent) {
   	if (!curNode) return NULL;	
    	Node* _Node = new Node (parent, curNode->data_, curNode->type_);
    	_Node->left_  = copyNode (curNode->left_ , _Node);
    	_Node->right_ = copyNode (curNode->right_, _Node);
    	return _Node;
}


Node* Diff :: determ (Node* curNode, Node* parent) {
    	assert (curNode);
    	switch (curNode->type_) {
        	case _const: {
            		Node* constant = new Node (parent, 0, _const);
            		return constant; 
			break;
        	}
        	case _value: {
            	Node* value = new Node (parent, 1, _const);
            	return value; 
		break;
        	}
        	case _oper: {
            		switch ((int)curNode->data_) {
                		case _add: { 
					return d_add (curNode, parent); 
					break; 
					}
                		case _sub: {
					return d_sub (curNode, parent); 
					break; 
					}

                		case _mul: { 
					return d_mul (curNode, parent); 
					break; 
					}

                		case _div: { 
					return d_div (curNode, parent); 
					break; 
					}

                		case _ln: { 
					return d_ln  (curNode, parent); 
					break; 
					}

                		default: printf ("Error! Unknown operation.\n");
                	printf ("curNode->data_ = %d \n",
                	(int) curNode->data_);
            		}

        	} break;
        	default: printf ("Error! Unknown type.\n");
    }	
    assert (0);
    return NULL;
}
