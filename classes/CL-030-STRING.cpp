#include <iostream>

class String{
	char* str;
public:
	String(const char* cstr);

	~String();
	
	size_t length() const;

	char& at(size_t index) const;

	void append(const char*);

	const char* raw() const;
private:
	size_t strlen = 0;
};

String::String(const char* cstr){
	int i = 0;

	while (cstr[i] != '\0'){
		strlen++;
		i++;
	}

	str =(char*) malloc(strlen + 1);

	for (i = 0 ; i < strlen ; i++)
		str[i] = cstr[i];
	str[strlen] = '\0';
}

String::~String(){
	delete []str;
}

size_t String::length() const{
	std::cout << strlen << std::endl;
	return strlen;
}

char& String::at(size_t index) const{
	char& c = str[index];
	return c;
}

void String::append(const char* add){
	size_t addlen = 0, i = 0;
	while (add[i] != '\0'){
		addlen++;
		i++;
	}
	 
	str =(char*)realloc(str , strlen + addlen + 1);

	for (i = 0 ; i < addlen ; i++)
		 str[strlen + i] = add[i];
	str[strlen + addlen] = '\0';

	strlen+=addlen;
}

const char* String::raw() const{
	return str;
}

int main(){
	String s("arkasha_huy");
	s.length();
	s.append("_i_bydlo");
	s.length();
	std::cout << s.raw() << std::endl;
	return 0;
}
