#pragma once
#include <iostream>
#include <list>
#include <vector>
using namespace std;

ostream& operator<<(ostream& os, vector<bool> v) {
	for (auto e : v) {
		os << e <<" ";
	}
	return os;
}


bool check_sum(const list<int>& L1, const list<int>& L2) {
	bool puede = true, puede_este = false;
	int suma = 0, i=0;
	list<int>::const_iterator ultima_pos = L1.begin();
	vector<bool> se_puede(L2.size(),false); //inicializados a false

	for (auto it = L2.begin(); it != L2.end(); ++it) {
		puede_este = false;
		suma = 0;
		for (auto jt = ultima_pos; jt != L1.end() && !puede_este; ++jt) {
			suma += *jt;
			if (suma == *it) {
				puede_este = true;
				ultima_pos = jt;
				++ultima_pos;
			}
		}
		se_puede[i++] = puede_este;
	}
	for (auto it = se_puede.begin(); it != se_puede.end(); ++it) {
		if (!*it)
			puede = false;
	}
	return puede;
}