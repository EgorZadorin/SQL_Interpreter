#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



class Logger{
public:
	virtual void log(string message) = 0;
};



class FileLogger : public Logger{
	ofstream out;
public:
	FileLogger(string filename) : out(filename,ios_base::app) {};
	~FileLogger(){out.close();};
	void log(string message);
};



class CompositeLogger : public Logger{
	vector<Logger*> maslog;
public:
	void addLogger(Logger* logger);
	void log(string message);
};



class StdoutLogger{
public:
	void log(string message);
};



template <class L>
class PrefixLogger{
	string prefix;
public:
	PrefixLogger(string str = "prefix_"):prefix(str){};
	void log(string message);
};



void FileLogger:: log(string message){
	out << message;
}

void CompositeLogger:: addLogger(Logger* logger){
	maslog.push_back(logger);
}

void CompositeLogger:: log(string message){
	for (int i = 0; i < maslog.size() ; i++){
		maslog[i] -> log(message);
	}
}

void StdoutLogger:: log(string message){
	cout << message << endl;
}

template<class L>
void PrefixLogger<L>:: log(string message){
	L logger;
	logger.log(prefix + message);
}

int main(){
	FileLogger logger("test.txt");
	logger.log("new line!");
	CompositeLogger composelog;
	Logger* p = &logger;
	composelog.addLogger(p);
	composelog.log("new line!!!");
	PrefixLogger<StdoutLogger> prelog("prefix ");
	prelog.log("new line!");
	return 0;
}
