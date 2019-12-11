#pragma once
#include <fstream>
#include "Creature.h"


using namespace std;

class Logger
{
	ofstream* file;
public:
	Logger(string i);
	~Logger();
	friend void operator<<(Logger& left, Creature right);
};

