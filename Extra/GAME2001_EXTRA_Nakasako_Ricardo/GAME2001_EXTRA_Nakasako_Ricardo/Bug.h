#pragma once
#include <iostream>
#include <string>

using namespace std;

class Bug {
private:
	char m_cPriority;
	string m_sDesc;

public:
	const char GetPriority() {
		return m_cPriority;
	}
	const string GetDescription() {
		return m_sDesc;
	}
	Bug (char priority, string desc):m_cPriority(priority), m_sDesc(desc) {
	}

};

ostream& operator<<(ostream& s, Bug& u)
{
	s << u.GetDescription();
	return s;
}
