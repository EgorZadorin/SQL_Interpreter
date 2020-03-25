#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

class Sotrud{
	map <long, string> sotr_base;
public:
	Sotrud(string filename);
	string get(long number);
};

Sotrud :: Sotrud(string filename){
	ifstream in(filename);
	string str = "", str1;
	long number;
	in >> number;
	for (int i = 0; i < 4; i++){
		in >> str1;
		str += str1;
		str += " ";
	}
	sotr_base.insert(pair<long, string>(number, str));
}

string Sotrud:: get(long number){
	return sotr_base[number];
}

int main(){
	Sotrud base("base.txt");
	cout << base.get(613085);
}

