#pragma once
#include <iostream>

using namespace std;


class Creature
{
public:
	double x = 0;
	double y = 0;
	Creature();
	~Creature();
	double getFit();
	double getHonestFit();
	friend Creature operator|(Creature left, Creature right);
	friend void operator~(Creature& a);
	friend ostream& operator<<(ostream& left, Creature right);
};

