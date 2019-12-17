#include "Logger.h"
#include <filesystem>

using namespace std;

Logger::Logger(string i)
{
	experimental::filesystem::path wey(path + i + extension);
	file = new ofstream(wey);
}


Logger::~Logger()
{
	file->close();
	delete file;
}


void operator<<(Logger& left, Creature right) {
	(*(left.file)) << "(" << right.x << ";" << right.y << ")\n";
}




void Logger::store(size_t i, size_t m, vector<Creature> guys) {
	string name = to_string(i) + "_" + to_string(m);
	double max = -INFINITY;
	Creature best_boy;
	double sum = 0;
	Logger log(name);
	for (int j = 0; j < guys.size(); ++j) {
		double fit = guys[j].getHonestFit();
		sum += fit;
		if (max < fit) {
			max = fit;
			best_boy = guys[j];
		}
	}
	sum /= guys.size();
	cout << "Iterration: " << name << "\n";
	cout << "Creatures: " << guys.size() << "\n";
	for (auto guy : guys) {
		cout << guy << "[" << guy.getHonestFit() << "]" << "\n";
		log << guy;
	}
	cout << "\n Max: [" << max << "] at " << best_boy << "\t " << "Middle: " << sum << "\n\n";
}