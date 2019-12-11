#include "Logger.h"

using namespace std;

Logger::Logger(string i)
{
	file = new ofstream(i);
}


Logger::~Logger()
{
	file->close();
	delete file;
}


void operator<<(Logger& left, Creature right) {
	(*(left.file)) << "(" << right.x << ";" << right.y << ")\n";
}