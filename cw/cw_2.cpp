#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Logger{
public:
	virtual void log(const string& message) = 0;
	virtual ~Logger(){};
};



class FileLogger : public Logger{
	ofstream out;
public:
	FileLogger(string filename) : out(filename, ios_base::app) {};
	~FileLogger(){out.close();};
	void log(const string& message);
};



class SwitchLogger : public Logger{
	vector<Logger*> maslog;
	Logger* currlog;
	int curr;
public:
	SwitchLogger(): currlog(0), curr(-1){};
	void addLogger(Logger* logger);
	void switchNext();
	void log(const string& message);
};



class StderrLogger{
public:
	void log(string message);
};



template <class L>
class PrefixLogger{
	string prefix;
	int count;
	L obj;
public:
	PrefixLogger(string str): count(1), prefix(str){};
	void log(string message);
};



void FileLogger:: log(const string& message){
	out << message;
}

void SwitchLogger:: addLogger(Logger* logger){
	maslog.push_back(logger);
	if (curr == -1)
		curr = 0;
	currlog = maslog[curr];
}

void SwitchLogger:: switchNext(){
	if (currlog != NULL){
		curr++;
		if (curr == maslog.size())
			curr = 0;
		currlog = maslog[curr];
	}
}

void SwitchLogger:: log(const string& message){
	if (currlog)
		currlog -> log(message);
}

template <class L>
void PrefixLogger<L>:: log(string message){
	obj.log(to_string(count) + prefix + message);
	count++;
}

void StderrLogger:: log(string message){
	cerr << message;
}

int main(){
	FileLogger logger("test.txt");
	logger.log("new line!");
	SwitchLogger switchlog;
	switchlog.addLogger(&logger);
	switchlog.switchNext();
	switchlog.log("new line!!!");
	PrefixLogger<StderrLogger> preflog("prefix_");
	preflog.log("message!");
	preflog.log("message!");
}
