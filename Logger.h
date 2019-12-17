#pragma once
#include <fstream>
#include "Creature.h"
#include <vector>
#include <string>

using namespace std;

class Logger
{
	ofstream* file;
	const string extension = ".txt";
	const string path = "C:\\Tsisa\\log_";
public:
	Logger(string i);
	~Logger();
	friend void operator<<(Logger& left, Creature right);
	static void store(size_t i, size_t m, vector<Creature> guys);
};

