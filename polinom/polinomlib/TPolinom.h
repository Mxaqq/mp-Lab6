
#include "../listlib/TList.h"
#include "TMonom.h"
#include <string>


const int nonDisplayedZeros = 4; // Êîëè÷åñòâî íåîòîáðàæàåìûõ íóëåé ïðè âûâîäå êîýôôèöèåíòà ïîëèíîìà


string RemoveSpace(string s);
class TPolinom
{
public:
	List<TMonom> list;
	TPolinom(TPolinom& other);
	TPolinom() {};
	TPolinom(string str);
	TPolinom& operator=(TPolinom& other); // ïðèñâàèâàíèå
	TPolinom& operator+(TPolinom& q); // ñëîæåíèå ïîëèíîìîâ
	void setPolinom(string s);
	// äîïîëíèòåëüíî ìîæíî ðåàëèçîâàòü:
	void operator+(TMonom newMonom); // äîáàâëåíèå ìîíîìà
	TPolinom operator*(TMonom monom); // óìíîæåíèå ìîíîìîâ 
	TPolinom operator*(double coef); // óìíîæåíèå ïîëèíîìà íà ÷èñëî 
	TPolinom operator* (TPolinom& other); // óìíîæåíèå ïîëèíîìîâ
	bool operator==(TPolinom& other); // ñðàâíåíèå ïîëèíîìîâ íà ðàâåíñòâî
	string ToString(); // ïåðåâîä â ñòðîêó
};
void TPolinom::setPolinom(string s) {
	list.clear();
	s = RemoveSpace(s);
	string temp;
	int i = 0;
	while (i < s.size()) {
		if (s[i] == '+') {
			this->operator+(TMonom(temp));
			temp.clear();
		}
		else if (s[i] == '-') {
			if (!temp.empty())
				this->operator+(TMonom(temp));
			temp.clear();
			temp.push_back('-');
		}
		else {
			temp += s[i];
		}
		i++;
	}
	if (!temp.empty()) {
		this->operator+(TMonom(temp));
	}
}
TPolinom::TPolinom(TPolinom& other)
{
	this->list = other.list;
}
TPolinom::TPolinom(string str)
{
	setPolinom(str);
}
TPolinom& TPolinom::operator=(TPolinom& other)
{
	this->list = other.list;
	return *this;
}
void TPolinom::operator+(TMonom m)
{
	List<TMonom>::iterator it;
	it = list.begin();
	bool flag = true;
	while (it != list.end()) {
		if (m > *it)
			break;
		if (*it == m) {
			(*it).coef += m.coef;
			flag = false;
			break;
		}
		it++;
	}
	if (flag && m.coef != 0)
		list.insert(m, it);
}
TPolinom& TPolinom::operator+(TPolinom& other)
{
	List<TMonom>::iterator it;
	it = other.list.begin();
	while (it != other.list.end()) {
		this->operator+(*it);
		it++;
	}


	return *this;
}
TPolinom TPolinom::operator*(TMonom monom)
{
	TPolinom temp = *this;
	List<TMonom>::iterator it;
	it = temp.list.begin();
	while (it != temp.list.end()) {
		(*it) = (*it).operator*(monom);
		it++;
	}


	return temp;
}
TPolinom TPolinom::operator*(double coef)
{
	List<TMonom>::iterator it;
	it = list.begin();
	while (it != list.end()) {
		(*it).coef *= coef;
		it++;
	}
	return *this;
}
TPolinom TPolinom::operator*(TPolinom& other)
{
	TPolinom temp;
	List<TMonom>::iterator it;
	it = other.list.begin();
	while (it != other.list.end()) {
		TPolinom t = this->operator*(*it);
		temp = temp + t;
		it++;
	}
	*this = temp;
	return *this;
}
bool TPolinom::operator==(TPolinom& other) 
{
	if (list == other.list) {
		return true;
	}
	return false;
}

string TPolinom::ToString()
{
	string result;
	List<TMonom>::iterator it;
	it = list.begin();
	while (it != list.end()) {
		if (abs((*it).coef) != 1) {
			result += std::to_string(abs((int)(*it).coef));
		}
		if ((*it).index / 100 != 0) {
			result += "x";
			if ((*it).index / 100 != 1)
				result += "^" + std::to_string((*it).index / 100);
		}
		if ((*it).index % 100 / 10 != 0) {
			result += "y";
			if ((*it).index % 100 / 10 != 1)
				result += "^" + std::to_string((*it).index % 100 / 10);
		}
		if ((*it).index % 10 != 0) {
			result += "z";
			if ((*it).index % 10 != 1)
				result += "^" + std::to_string((*it).index % 10);
		}
		it++;
		if (it != list.end()) {
			if ((*it).coef < 0)
				result += " - ";
			else
				result += " + ";
		}
	}
	return result;
}
string RemoveSpace(string s)
{
	int i = 0;
	while (i < s.size()) {
		if (s[i] == ' ')
			s.erase(i, 1);
		else
			i++;
	}
	return s;
}
