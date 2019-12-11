#include "Creature.h"
#include <cmath>
#include <utility>

using namespace std;

double randomizer(double,double);


Creature::Creature()
{
}

Creature::~Creature()
{
}


double Creature::getHonestFit() {
	return sin(x) / (1 + x * x + y * y);
}

double Creature::getFit(){
	return sin(x)/(1 + x*x + y*y)+5;
}

Creature operator|(Creature left, Creature right) {
	if (rand() % 2) {
		swap(left, right);
	}
	Creature result;
	result.x = left.x;
	result.y = right.y;
	return result;
}



void operator~(Creature& a) {
	if (rand() % 4 != 0) return;
	double ranx = randomizer(-0.1, 0.1);
	double rany = randomizer(-0.1, 0.1);
	a.x = ranx+a.x;
	a.y = rany+a.y;
	if (a.x > 2) a.x = 2;
	if (a.y > 2) a.y = 2;
	if (a.x < -2) a.x = -2;
	if (a.y < -2) a.y = -2;
}


ostream& operator<<(ostream& left, Creature right) {
	left << "(" << right.x << "; " << right.y << ")";
	return left;
}
