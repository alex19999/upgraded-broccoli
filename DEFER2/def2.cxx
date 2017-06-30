#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include"def2.hxx"
#include<cassert>
#include<cctype>
#include <unistd.h>
#define MAX_OP 10


Node::Node (Node* parent, double data, type t):
    data_   (data),
    type_   (t),
    left_   (NULL),
    right_  (NULL),
    parent_ (parent)
{}

Def2 :: Def2():
	data(0),
    	ptr(0) {
        	FILE* f_in  = fopen ("f_in.txt", "r");
		fseek (f_in, 0, SEEK_END);
        	long f_size = ftell (f_in);
       	 	rewind (f_in);
		data  = new char [f_size + 1];
        	size_t  c = fread (data,sizeof(char), (size_t) f_size, f_in);
        	assert (c ==  (size_t) f_size);
        	data [f_size] = '\0';
        	PRINT ("file Size = %d\n", (int)f_size);
		int i;
		for (i = 0; i < f_size - 1; i++) {
            			PRINT ("%c", data [i]);
        			}
        	PRINT ("\n");
		fclose (f_in);
    }

Def2 :: ~Def2()
{
    delete[]data;
}

Node* Def2 :: GetN(Node* parent){
    	PRINT ("I am GetN \n");
    	int val = 0;
    	while ('0' <= data[ptr] && data[ptr] <= '9'){
        	val = val*10 + data[ptr] - '0';
        	ptr++;
    }
    	Node* newNode = new Node (parent, val, _const);
    	PRINT ("I've found %d\n", val);
    	return newNode;
}

Node* Def2 :: GetF (Node* parent) {
    	PRINT ("I am GetF\n");
    	while (isalpha (data[ptr])){
        	char op_[MAX_OP] = {};
        	int i = 0;
        	while (isalpha (data[ptr])){
            		op_[i] = data [ptr];
            		ptr++;
            		i++;
        		}
        	PRINT ("%s\n", op_);
        	if (!strcmp (op_, "ln")){
            		PRINT ("I've found ln\n");
            		Node* newNode  = new Node (parent, _ln, _oper);
            		Node* Ln_arg    = GetP (parent);
            		newNode->left_ = Ln_arg;
            		Ln_arg->parent_ = newNode;
            		return newNode;
        	} else 	
			if (!strcmp (op_, "x")) {
            		PRINT ("I've found X\n");
            		Node* newNode = new Node (parent, 0, _value);
            		return newNode;
        	} else {
            		PRINT ("Unknown command!\n");
            		exit (0);
        }
    }
    	return GetP (parent);
}

Node* Def2 :: GetP (Node* parent) {
    	if (data[ptr] == '('){
        	PRINT ("I've found %c\n", data[ptr]);
        	ptr++;
        	Node* val = GetE (parent);
       		PRINT ("I've found %c\n", data[ptr]);
        	assert (data[ptr] == ')');
        	ptr++;
        	return val;
    	} else { 
		return GetN (parent); 
	}
}

Node* Def2 :: GetT (Node* parent) {
    	PRINT ("I am GetT \n");
    	bool fl = false;
    	double s = 0;
    	Node* val = GetF (parent);
    	Node* newNode = NULL;
    	while (data[ptr] == '*' || data[ptr] == '/') {
        	fl = true;
        	int operat = data[ptr];
        	PRINT ("I've found mul or div\n");
        	ptr++;
        	Node* val2 = GetF (parent);
        	(operat == '*')? s = _mul: s = _div;
       	 	newNode = new Node (parent, s, _oper);
        	newNode->left_  = val;
        	newNode->right_ = val2;
        	val->parent_    = newNode;
        	val2->parent_   = newNode;
    	}
    	if (fl == true) { 
		return newNode; 
        } else { 
		return val; 
	}
}

Node* Def2 :: GetE (Node* parent) {
    	PRINT ("I am GetE \n");
    	bool fl = false;
    	double s = 0;
    	Node* val = GetT (parent);
    	Node* newNode = NULL;
    	while(data[ptr] == '+' || data[ptr] == '-') {
        	fl = true;
        	int operat = data[ptr];
        	PRINT ("I've found plus or minus\n");
        	ptr++;
        	Node* val2 = GetT (parent);
        	(operat == '+')? s = _add: s = _sub;
        	newNode = new Node (parent, s, _oper);
        	newNode->left_  = val;
        	newNode->right_ = val2;
        	val->parent_ = newNode;
       	 	val2->parent_ = newNode;
    }
    	if (fl == true) { 
		return newNode; 
	} else { 
		return val; 
	}
}

Node* Def2 :: GetG (Node* parent) {
    	PRINT ("I am GetG \n");
    	Node* head = GetE (parent);
    	PRINT ("!!!%s!!!\n", data);
    	PRINT ("ptr = %d\n", ptr);
    	PRINT ("(ptr - 1) = %c\n", (ptr - 1));
    	PRINT ("(ptr) = %c\n", ptr);
    	PRINT ("(ptr + 1) = %c\n", (ptr + 1));
    	assert (data [ptr + 1] == '\0');
    	return head;
}

void texN (Node* node, FILE* stream) {
    	assert (stream);
    	if (!node) return;
    	if (node->nodeCmp (node, _const)) {
        	fprintf (stream, "{%lg}", node->data_);
    	} else if (node->nodeCmp (node, _value)) {
       		fprintf (stream, "{x}");
    	}	
	else if (node->nodeCmp (node, _oper, _add)) {
        	fprintf (stream, "{(");
        	texN(node->left_ , stream);
        	fprintf (stream, "}+{");
        	texN (node->right_, stream);
        	fprintf (stream, ")}");
    	}
    	else if (node->nodeCmp (node, _oper, _sub)) {
        	fprintf (stream, "{(");
        	texN (node->left_ , stream);
        	fprintf (stream, "}-{");
        	texN (node->right_, stream);
        	fprintf (stream, ")}");
    	}
    	else if (node->nodeCmp (node, _oper, _mul)) {
        	fprintf (stream, "{");
        	texN(node->left_ , stream);
        	fprintf (stream, "}*{");
        	texN (node->right_, stream);
        	fprintf (stream, "}");
    	} 
	else if (node->nodeCmp (node, _oper, _div)) {
        	fprintf (stream, "\\frac{");
        	texN (node->left_, stream);
        	fprintf (stream, "}{");
        	texN (node->right_, stream);
        	fprintf (stream, "}");
    	}	
    	else if (node->nodeCmp (node, _oper, _ln)) {
        	fprintf (stream, "ln");
        	fprintf (stream, "\\left(");
        	texN (node->left_, stream);
        	texN (node->right_, stream);
        	fprintf (stream, "\\right)");
    	}
}

void tex(Node* oldTree, Node* newTree) {
    	assert (oldTree);
    	assert (newTree);
	FILE* stream = fopen ("./TexDump/diff.tex", "w");
    	assert (stream);
    	fprintf (stream,"\\documentclass{article}\n" "\\usepackage[a4paper, margin=6mm]{geometry}\n" "\\usepackage{amsmath}\n" "\\title{Differentiator}\n" "\\begin{document}\n" "\\maketitle\n" "\\begin{eqnarray}\n" "\\left( ");
    	texN (oldTree, stream);
    	fprintf (stream, "\\right) ' = \n");
    	texN (newTree, stream);
    	fprintf (stream, "\\end{eqnarray}\n" "\\end{document}\n"); 
	fclose (stream);
    	chdir  ("./TexDump");
    	system ("pdflatex diff.tex");
    	system ("evince diff.pdf");
    	system ("mv diff.pdf ./../");
}


