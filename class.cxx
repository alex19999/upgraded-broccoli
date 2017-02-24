#include<iostream>
#include<cstdlib>
#include<cassert>

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
	int Capacity();
	int getsize();
	int verifypoint(int*p);
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

int Stack :: verifypoint(int* p){
	int f;
	f = (p == NULL);
	return !f;
}
void  checkerrors(int errornum) {

        	switch(errornum){
		case 1:cout<<"Stack is full of items"<<endl;
		break;
		case 2:cout<<"No value<<endl";
		break;
		case 3:cout<<"Stack is empty"<<endl;
		break;
 		case 4:cout<<"No adress"<<endl;
		break;
		default:cout<<"No problem"<<endl;
		break;
		}
}
void test(Stack* stack){
	int k;
	double j;
	for(k = 0;k <= 30;k++) {
		checkerrors(stack->push((double)k));
	}
	for(k = 0;k <= 30;k++) {
		checkerrors(stack->pop(&j));
	}
}
int main(int argc,char** argv){
	Stack stack(30);
	test(&stack);
	stack.getsize();
	stack.Capacity();
	stack.empty();
	return 0;
}
