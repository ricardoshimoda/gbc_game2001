#pragma once
#include <iostream>
using namespace std;
class Unit
{
private:
	string m_sName;
public:
	Unit(const string s) : m_sName(s) {}
	friend ostream& operator<<(ostream& s, const Unit& u);
};

ostream& operator<<(ostream& s, const Unit& u)
{
	s << u.m_sName;
	return s;
}
