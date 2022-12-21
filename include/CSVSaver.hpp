#ifndef CSVWriter_h
#define CSVWriter_h 1

#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<tuple>
#include <direct.h>


typedef std::tuple<std::string, std::string, std::string, std::string, std::string> Row;


template<typename Ts>
class CSVWriter {
public:
	
	void set_dir(std::string dir) {
		this->dir = dir;
		_mkdir(this->dir.c_str());
	}

	void open_file(std::string filename) {
		this->filename = filename;
		this->out.open(dir+filename);
	};
	void close() {
		this->out.close();
	};

	void write(std::vector<std::string> a) {
		std::string s;
		for (auto i : a) {
			s += i;
			s += ";";
		}
		out.write(s.c_str(), s.size()-1);
		out.write("\n", 1);
	};

	//void write(Ts);
	//void setHeaders(std::string args...);
	
	std::string dir;
	std::ofstream out;
	std::string filename;
	CSVWriter<Ts>() {};
	
	//inline static CSVWriter& instance = 0;
};

template<typename Ts>
class StaticWriter {
	inline static CSVWriter<Ts>* writer = new CSVWriter<Ts>;

public:
	inline static std::map<std::string, std::string> globals;
	static CSVWriter<Ts>* getWriter() {
		return writer;
	}
};

#endif


typedef StaticWriter < Row > CSVTable;

