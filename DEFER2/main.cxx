#include <cstdio>
#include <cstdlib>
#include "def2.hxx"


int main () {
        Def2 Tree_;
        Node* Tree_one = Tree_.GetG (NULL);
        Diff wf (Tree_one);
        Node* diffTree = wf.determ (Tree_one, NULL);
        tex (Tree_one, diffTree);
        return 0;
}

