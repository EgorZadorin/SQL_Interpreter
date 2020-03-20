#include <iostream>
#include <fcntl.h>
#include <unistd.h>

class TextFileReader{
	int fd;
public:
	TextFileReader(const char* path);
	~TextFileReader();
};

TextFileReader::TextFileReader(const char* path){
	fd = open(path , 0);
}

TextFileReader::~TextFileReader(){
	close(fd);
}

int main(){
	TextFileReader File("text.txt");
	return 0;
}
