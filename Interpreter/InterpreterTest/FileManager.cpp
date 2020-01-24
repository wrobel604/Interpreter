#include "FileManager.hpp"

FileManager::FileManager()
{
	fileName = "";
}

FileManager::~FileManager()
{
	if (file.is_open()) {
		file.close();
	}
}

bool FileManager::open(std::string filename)
{
	fileName = filename;
	file.open(fileName);
	return file.is_open();
}

void FileManager::close()
{
	file.close();
	fileName = "";
}

void FileManager::write(std::string text)
{
	if (file.is_open()) {
		file << text;
		setPosition(getPosition());
	}
	else {
		throw std::exception{ "File isn't open" };
	}
}

std::string FileManager::read(int count)
{
	std::string result = "";
	std::string bufor;
	int size = 0;
	while (file >> bufor) {
		size = bufor.size();
		if (size < count) {
			result += bufor;
			count -= size;
			if (count != 0) { result += " "; }
		}
		else {
			result += bufor.substr(0, count);
		}
	}
	setPosition(getPosition());
	return result;
}

bool FileManager::isOpen() const
{
	return file.is_open();
}

void FileManager::setPosition(int pos)
{
	file.seekg(pos, std::fstream::beg);
	file.seekp(pos, std::fstream::beg);
}

int FileManager::getPosition() 
{
	return (file.tellg()>file.tellp())? file.tellg():file.tellp();
}

int FileManager::getFileSize()
{
	int pos = getPosition(), res;
	file.seekg(0, std::fstream::end);
	res = file.tellg();
	setPosition(pos);
	return res;
}

bool FileManager::createFile(std::string filename)
{
	if (isFileExist(filename)) { return false; }
	std::ofstream out;
	out.open(filename);
	if (out.is_open()) {
		out.close();
		return true;
	}
	return false;
}

bool FileManager::isFileExist(std::string filename)
{
	std::ifstream in;
	in.open(filename);
	if (in.is_open()) { in.close(); return true; }
	return false;
}
