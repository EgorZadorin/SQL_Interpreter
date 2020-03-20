#include <iostream>

class IntVector{
	int* Vector;
public:
	void set(int i , int value);

	int get(int i);

	IntVector(){
		Vector = NULL;
	}

	~IntVector(){
		free(Vector);
	}
private:
	size_t length = 0;
};

void IntVector::set(int i , int value){
	if (length <= i){
		Vector = (int*)realloc(Vector , (i+1)*sizeof(int));
		Vector[i] = value;
		for (int j = length ; j < i ; j++)
			Vector[j] = 0;
		length = i + 1;
	}
	else 
		Vector[i] = value;
}

int IntVector::get(int i){
	try{
		if (i >= length){throw 0;}
	}
	catch (int){
		std::cout << "Out of range!" << std::endl;
		exit;
	}
	
	std::cout << Vector[i] << std::endl;
	return Vector[i];
}

int main(){
	IntVector A;
	A.set(1, 2);
	A.get(0);
	A.get(1);
	return 0;
}
