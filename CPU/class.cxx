#include<iostream>
#include<cstdlib>
#include<cassert>
#include<cstdio>



using namespace std;





class Stack{
	private:
	int capacity_;
	double *data_;
	int size_;
	public:
	unsigned int push(double value);
	unsigned int pop(double* location);
	unsigned int empty();
	unsigned char Broke();
	void dump(FILE* f);
	int Capacity();
	int getsize();
	int verifypoint(void*p);
	Stack(int capacity);
	~Stack();
};

unsigned int  Stack :: push(double value) {
		if(size_<capacity_) {
			if(value){
				this->data_[this->size_++] = value;
			} else return 2;
		} else return 1;
	}
		
unsigned int Stack ::pop(double* location){
		if (capacity_ > 0){
			if(location) {
				*location = data_[--size_];
			} else return 4;
		} else return 3;
	}
	
Stack::Stack(int capacity):
		capacity_ (capacity),
		size_(0)
		{
		data_ = (double*)calloc(capacity,sizeof(double));
		

	}
		
	
unsigned int Stack ::  empty() {
		size_ = 0;
		return 0;
		}
int Stack :: Capacity() {
		return capacity_;
	}
int Stack :: getsize() {
		return size_;
	}
	Stack :: ~ Stack(){
		free(data_);
	}
unsigned char Stack :: Broke() {
	char  f = 0;
	 f = (f + !verifypoint(data_) + (size_ > capacity_)*2 +(capacity_ <= 0)*4);
	return f;
}

int Stack :: verifypoint(void* p){
	int f;
	f = (p == NULL);
	return !f;
}
void  checkerrors(int errornum) {

        	switch(errornum){	
		case 1:printf("Stack is full of items\n");
		break;
		case 2:printf("No value\n");
		break;
		case 3:printf("Stack is empty\n");
		break;
 		case 4:printf("No adress\n");
		break;
		default:printf("No problem\n");
		break;
	
		}
}
void Stack::dump(FILE* f){
	unsigned char err;
	err = Broke();
	fprintf(f, "Stack object at <%p>:\n", this);
	fprintf(f, "\t valid:\t");
	if(!err){
		fprintf(f,"No problem\n");
	} else {
		fprintf(f, "[err %d]\n", err);
	}
	
	fprintf(f, "\t Data pointer:\t<%p>\n", data_);
	fprintf(f, "\t Capacity:\t%d\n", capacity_);
	fprintf(f, "\t Size:\t\t%d\n", size_);
	
	
}
void test(Stack* stack){
	int k;
	double j;
	for(k = 0;k <= 30;k++) {
		checkerrors(stack->push((double)k));
	}
	for(k = 0;k <= 30;k++) {
		checkerrors(stack->pop(&j));
		printf("%f\n",j);
	}

}

//class Newfunctions {
/*	
int main(int argc,char** argv){
	Stack stack(30);
	test(&stack);
	stack.getsize();
	stack.Capacity();
	stack.empty();
	stack.dump(stdout);
	return 0;
}
*/
