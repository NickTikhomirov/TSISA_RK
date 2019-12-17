#include <iostream>
#include <vector>
#include "Creature.h"
#include <random>
#include <string>
#include "Logger.h"

using namespace std;

#define amount 4



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
			if(a[j].getHonestFit() > a[i].getHonestFit())
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
	double min = 0; //нужно только для борьбы с отрицательными fit-функциями, поэтому 0
	for (int i = 0; i < a.size(); ++i){
		sum += a[i].getHonestFit();
		if (a[i].getHonestFit() < min) 
			min = a[i].getHonestFit();
	}
	int size = a.size();
	sum -= min * size;
	while (size > amount){
		int chosen = rand() % a.size();
		double fit = a[chosen].getHonestFit()-min;
		prob = fit / sum;
		if (randomizer(0, 1) > prob) {
			a.erase(a.begin()+chosen, a.begin()+chosen+1);
			sum -= fit;
			size -= 1;
		}
	}
	return a;
}




int main() {
	cout << "Pattern: \n	Creature: (x,y)[fit]\n";
	for (size_t max : {10, 100}) {
		cout << "Cycling for " << max << " generations\n";
		vector<Creature> field;
		field.resize(amount);
		for (int i = 0; i < amount; ++i)
			field[i] = random_creature();
		Logger::store(0, max, field);
		for (int i = 1; i <= max; ++i) {
			if (field.size() < 2) {
				cout << "Everybody died!!\n";
				break;
			}
			mate_and_mutate(field);
			field = kill_roulette(field);
			if(max!=100 || !(i%10)) 
				Logger::store(i, max, field);
		}
		cout << "===============================\n";
	}
}