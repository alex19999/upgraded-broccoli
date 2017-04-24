
void Node :: akinator(Node* root) {
        char* answer;
        char* data;
        int len = 0;
        look(root);
        data = (char*)calloc(MAX_SYM,sizeof(char));
        answer = (char*)calloc(MAX_PREP,sizeof(char));
        fscanf(stdin,"%s",answer);
        if(!strcmp(answer,"no")) {
                if(root->left != NULL) {
                        akinator(root->left);
                } else {
                        fprintf(stderr,"Who is it?\n");
                        fscanf(stdin,"%s",answer);
                        fprintf(stderr,"What does  %s differs from %s\n",answer,root->question);
                        getc(stdin);
                        fgets(data,MAX_SYM,stdin);
                        len = strlen(data);
                        data[len-1] = '?';
                        root->left = new Node(root->question,NULL,NULL);
                        root->right = new Node(answer,NULL,NULL);
                        root->question = data;
                        look(root->left);
                        look(root->right);
                        look(root);
                        return;
                 }
        } else {
                akinator(root->right);
        }
}


