#ifndef _DEF2_H_
#define _DEF2_H_

#include "def.hxx"
#define PRINT(...)

class Def2{
        public:
        char* data;
        int ptr;
        Def2();
        ~Def2();
        Node* GetN (Node* parent);
        Node* GetF (Node* parent);
        Node* GetP (Node* parent);
        Node* GetT (Node* parent);
        Node* GetE (Node* parent);
        Node* GetG (Node* parent);
};

#endif // _DEF2_H_ //

