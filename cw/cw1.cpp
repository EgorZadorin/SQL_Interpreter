#include <iostream>

class Student{
	char* surname;
	char* name;
	long number;
	int fives;
	int fours;
	int threes;
public:
	Student(const char* , const char* , long , int , int , int);
	Student(Student&);
	~Student();
	double average() const;
	Student& operator = (const Student&);
	Student& operator ++ ();
	Student operator ++(int);
	friend std::ostream& operator << (std::ostream& ,const Student&);
};

void conststrcpy(char*& str , const char* conststr){
	size_t strlen = 0 , i = 0;
	if (conststr == NULL){
		str = new char;
		*str = '\0';
		return;
	}

	while (conststr[i] != '\0'){
		strlen++;
		i++;
	}

	str = new char[strlen+1];
	for (i = 0 ; i < strlen ; i++){
		str[i] = conststr[i];
	}
	str[strlen] = '\0';
}


Student::Student(const char* s1 = NULL , const char* s2 = NULL , long num = 0 , int fi = 0 , int fo = 0 , int th = 0) {
	conststrcpy(surname , s1);
	conststrcpy(name , s2);
	number = num;
	fives = fi;
	fours = fo;
	threes = th;
}

Student::Student(Student& Obj){
	conststrcpy(surname , Obj.surname);
	conststrcpy(name , Obj.name);
	number = Obj.number;
	fives = Obj.fives;
	fours = Obj.fours;
	threes = Obj.threes;
}

Student::~Student(){
	delete []surname;
	delete []name;
}

Student& Student::operator =  (const Student& Obj){
	delete []surname;
	delete []name;

	conststrcpy(surname , Obj.surname);
	conststrcpy(name , Obj.name);
	number = Obj.number;
	fives = Obj.fives;
	fours = Obj.fours;
	threes = Obj.threes;

	return *this;
}

std::ostream& operator << (std::ostream& out ,const Student& Obj){
	out << Obj.surname << " " << Obj.name << " " << Obj.number << " " << Obj.fives << " " << Obj.fours << " " << Obj.threes;
	return out;
}

Student Student::operator ++ (int){
	Student tmp(*this);
	number++;
	return tmp;
}

Student& Student::operator ++ (){
	number++;
	return *this;
}

double Student::average() const{
	double sum = ((fives * 5) + (fours * 4) + (threes * 3));
	double kol = (fives + fours + threes);
	return sum/kol;
}

int main(){
	Student Egor("Egor" , "Zadorin" , 2185468 , 10 , 8 , 7);
	Student Arkady("Arkady" , "Vladimirov" , 2180392 , 10 , 10 , 10);

	std::cout << Arkady.average() << std::endl;
	std::cout << Egor.average() << std::endl;

	Egor = Arkady;

	std::cout << Arkady.average() << std::endl;
	std::cout << Egor.average() << std::endl;

	std::cout << Arkady << std::endl;

	Arkady++;

	std::cout << Arkady << std::endl;

	++Arkady;

	std::cout << Arkady << std::endl;
}

