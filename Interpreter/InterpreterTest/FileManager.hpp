#pragma once
#include<iostream>
#include<string>
#include<fstream>

class FileManager
{
	std::string fileName;
	std::fstream file;
public:
	FileManager();
	~FileManager();

	bool open(std::string filename);
	void close();

	void write(std::string text);
	std::string read(int count);
	bool isOpen() const;

	void setPosition(int pos);
	int getPosition();
	int getFileSize();

	static bool createFile(std::string filename);
	static bool isFileExist(std::string filename);
};

