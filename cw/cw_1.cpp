#include <iostream>

struct Student{
	long number;
	int mark;
};

class Vedomost{
	Student* Ved;
	int length;
public:
	Vedomost(int);
	Vedomost(Vedomost&);
	~Vedomost();
	void SetNumber(long num, int pos);
	void SetMark(int newmark , long num);
	int GetMark(int pos) const;
	long GetNumber(int pos) const;
	Vedomost& operator = (const Vedomost&);
	int& operator [] (long num);
	friend struct Str;
};

struct Str{
	std::ostream& out;
	Vedomost& ved;
	Str(std::ostream& oobj, Vedomost& vobj):out(oobj), ved(vobj){};
	Str operator << (long num);
	Str operator << (const char* str);
};

Vedomost::Vedomost(int N){
	Ved = new Student[N];
	for (int i = 0 ; i < N ; i++){
		Ved[i].number = 0;
		Ved[i].mark = 0;
	}
	length = N;
}

Vedomost::Vedomost(Vedomost& obj){
	length = obj.length;
	Ved = new Student[length];
	for (int i = 0 ; i < length ; i++){
		Ved[i].number = obj.Ved[i].number;
		Ved[i].mark =obj.Ved[i].mark;
	}
}

Vedomost::~Vedomost(){
	delete []Ved;
}

void Vedomost::SetNumber(long num , int pos){
	if (pos > length){
		throw 1;
	}	
	Ved[pos-1].number = num;
}

void Vedomost::SetMark(int newmark , long num){
	if ((newmark > 5) || (newmark < 2)){
		throw 1;
	}
	int i = 0;
	while (Ved[i].number != num){
		i++;
	}
	if (i == length){
		throw 'a';
	}
	Ved[i].mark = newmark;
}

int Vedomost::GetMark(int pos) const{
	return Ved[pos-1].mark;
}

long Vedomost::GetNumber(int pos) const{
	return Ved[pos-1].number;
}

Vedomost& Vedomost::operator = (const Vedomost& obj){
	delete[] Ved;
	length = obj.length;
	Ved = new Student[length];
	for (int i = 0 ; i < length ; i++){
		Ved[i].number = obj.Ved[i].number;
		Ved[i].mark =obj.Ved[i].mark;
	}
	return *this;
}

int& Vedomost::operator [] (long num){
	int i = 0;
	while ((Ved[i].number != num) && (i < length))
		i++;
	if (i == length){
		std::cout << "No such number!" << std::endl;
		throw 3;
	}
	else
		return Ved[i].mark;
}

Str operator << (std::ostream& oobj, Vedomost& vobj){
	Str S(oobj, vobj);
	return S;
}

Str Str::operator << (long num){
	int i = 0;
	while ((this -> ved.Ved[i].number) != num){
		i++;
	}
	(this -> out) << this -> ved.Ved[i].mark;
	return *this;
}

Str Str::operator << (const char *str){
	(this -> out) << str;
	return *this;
}


int main(){
	Vedomost V(5);

	try {V.SetNumber(2180405 , 3);}
	catch(int){
		std::cout << "Position is out of range!" << std::endl;
		return 1;
	}

	try {V.SetMark(2 , 2180405);}
	catch(int){
		std::cout << "No such student number!" << std::endl;
		return 1;
	}
	catch(char){
		std::cout << "Invalid mark!" << std::endl;
		return 1;
	}

	Vedomost A(10);
	std::cout << V.GetNumber(3) << " " << V.GetMark(3) << std::endl;
	std::cout << A.GetNumber(3) << " " << A.GetMark(3) << std::endl;

	V[2180405] = 3;

	std::cout << V.GetNumber(3) << " " << V.GetMark(3) << std::endl;
	std::cout << A.GetNumber(3) << " " << A.GetMark(3) << std::endl;

	std::cout << V << 2180405 << "stroka!" << 2180405 << "\n";

	return 0;
}
