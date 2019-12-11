#include <iostream>
#include <vector>
#include "Creature.h"
#include <random>
#include <string>
#include "Logger.h"

using namespace std;

#define amount 4
#define time 10



double _abs_(double x) {
	return x * (2 * (x > 0) - 1);
}


double randomizer(double a, double b) {
	static mt19937 engine(random_device{}());
	auto generator = uniform_real_distribution<double>(a, b);
	return generator(engine);
}

Creature random_creature() {
	Creature result;
	result.x = randomizer(-2, 2);
	result.y = randomizer(-2, 2);
	return result;
}

void sort_by_fit(vector<Creature> &a) {
	for(int i = 0; i < a.size()-1; ++i) {
		for(int j = i+1; j < a.size(); ++j) {
			if(a[j].getFit() > a[i].getFit())
				std::swap(a[i], a[j]);
		}
	}
}

void mate_and_mutate(vector<Creature>& a) {
	sort_by_fit(a);
	vector<Creature> b = a;
	for(int i=1; i<b.size();++i){
		Creature embrione = (b[0])|(b[i]);
		~embrione;
		a.push_back(embrione);
	}
}

vector<Creature> kill_roulette(vector<Creature> a) {
	double sum = 0;
	double prob = 0;
	for (int i = 0; i < a.size(); ++i)
		sum += a[i].getFit();
	int size = a.size();
	while (size > amount){
		int chosen = rand() % a.size();
		double fit = a[chosen].getFit();
		prob = fit / sum;
		if (randomizer(0, 1) > prob) {
			a.erase(a.begin()+chosen, a.begin()+chosen+1);
			sum -= fit;
			size -= 1;
		}
	}
	return a;
}


void logger(int i, vector<Creature> guys) {
	double max = -INFINITY;
	double sum = 0;
	Logger log("log" + to_string(i) + ".txt");
	for (int j = 0; j < guys.size(); ++j) {
		double fit = guys[j].getHonestFit();
		sum += fit;
		if (max < fit) {
			max = fit;
		}
	}
	sum /= guys.size();
	cout << "Iterration: " << i<<"\n";
	cout << "Guys: " << guys.size() << "\n";
	for (auto guy : guys) {
		cout << guy << "\t";
		log << guy;
	}
	cout << "\n Max:"<<max<<"\t "<<"Middle: "<<sum<<"\n\n";
}



int main() {
	const size_t max = time;
	vector<Creature> field;
	field.resize(amount);
	for (int i = 0; i < amount; ++i)
		field[i] = random_creature();
	logger(0, field);
	for (int i = 1; i<max; ++i) {
		if (field.size() < 2) {
			cout << "Everybody died!!\n";
			break;
		}
		mate_and_mutate(field);
		field = kill_roulette(field);
		logger(i, field);
	}
}