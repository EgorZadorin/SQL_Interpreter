#include <iostream>


class MaxSeq{
	int *A;
public:
	MaxSeq(){
		A = NULL;
	}

	~MaxSeq(){
		free (A);
	}

	void add(int n);

	int max();
	
	size_t count();
private:
	size_t counter = 0;
};

void MaxSeq::add(int n){
	counter++;
	A = (int*)realloc(A , counter * sizeof(int));
	A[counter-1] = n; 
}

int MaxSeq::max(){
	try{
		if(counter == 0){throw 0;}
	}
	catch(int){std::cout << "Empty!" << std::endl;}
	
	int max = A[0];

	for (int i = 0 ; i < counter ; i++)
		if(A[i] > max)
			max = A[i];

	std::cout << max << std::endl;
	return max;
}

size_t MaxSeq::count(){m
	std::cout << counter << std::endl;
	return counter;
}

int main(){
	MaxSeq S;
	S.add(3);
	S.add(10);
	S.add(1);
	S.count();
	S.max();
}
