
#include "../listlib/TList.h"
#include "TMonom.h"
#include <string>


const int nonDisplayedZeros = 4; 
string RemoveSpace(string s);

class TPolinom
{
public:
	List<TMonom> list; 

	TPolinom(TPolinom& other);
	TPolinom() {};
	TPolinom(string str);
	TPolinom& operator=(TPolinom& other);
	TPolinom operator+(TPolinom& q);
	TPolinom operator-(TPolinom& q);
	void setPolinom(string s);
	void operator+(TMonom newMonom);
	TPolinom operator*(TMonom monom);
	TPolinom operator*(double coef);
	TPolinom operator* (TPolinom& other);
	bool operator==(TPolinom& other);
	string ToString(); 
	friend ostream& operator<<(ostream& os, TPolinom& polinom)
	{
		cout << polinom.ToString() << endl;
		return os;
	}
	TPolinom derivative(char c);
	TPolinom Integral(char c);
	TPolinom operator/(TMonom monom);
	TPolinom operator/(double coef);
	TPolinom operator/(TPolinom& other);

	string ToPostfix();


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
	if (!flag && (*it).coef == 0)
		list.erase(it);
	if (flag && m.coef != 0)
		list.insert(m, it);
}


TPolinom TPolinom::operator+(TPolinom& other)
{
	TPolinom temp = *this;
	List<TMonom>::iterator it;
	it = other.list.begin();
	while (it != other.list.end()) {
		temp.operator+(*it);
		it++;
	}

	return temp;
}

inline TPolinom TPolinom::operator-(TPolinom& q)
{
	TPolinom temp = q * (-1);
	return (*this) + temp;
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
	return this->list == other.list;
}


string TPolinom::ToString()
{
	string result;
	List<TMonom>::iterator it;
	it = list.begin();
	while (it != list.end()) {
		if ((*it).coef == 0) {
			it++;
			continue;
		}

		if ((*it).index == 0 && (int)(*it).coef == 1) {
			result += to_string(abs((int)(*it).coef));
		}
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
	if (result[result.size() - 2] == '+') {
		result.pop_back();
		result.pop_back();
	}
	return result;
}

inline TPolinom TPolinom::derivative(char c)
{
	TPolinom temp = *this;
	List<TMonom>::iterator it;
	it = temp.list.begin();
	while (it != temp.list.end()) {
		(*it) = (*it).derivative(c);
		it++;
	}

	return temp;
}

inline TPolinom TPolinom::Integral(char c)
{
	TPolinom temp = *this;
	List<TMonom>::iterator it;
	it = temp.list.begin();
	while (it != temp.list.end()) {
		(*it) = (*it).Integral(c);
		it++;
	}

	return temp;
}

inline TPolinom TPolinom::operator/(TMonom monom)
{
	List<TMonom>::iterator it;
	it = list.begin();
	while (it != list.end()) {
		(*it) = (*it) / monom;
		it++;
	}
	return *this;
}

inline TPolinom TPolinom::operator/(double coef)
{
	List<TMonom>::iterator it;
	it = list.begin();
	while (it != list.end()) {
		(*it).coef /= coef;
		it++;
	}
	return *this;
}

inline TPolinom TPolinom::operator/(TPolinom& other)
{
	if (other.list.Size() > 1)
		throw exception("eror");

	*this = *this / other.list[0];
	return *this;
}

inline string TPolinom::ToPostfix()
{
	string result;
	List<TMonom>::iterator it;
	it = list.begin();
	while (it != list.end()) {
		if ((*it).coef == 0) {
			it++;
			continue;
		}
		if ((*it).index == 0 && (int)(*it).coef == 1) {
			result += to_string(abs((int)(*it).coef));
		}
		if (abs((*it).coef) != 1) {
			result += std::to_string(abs((int)(*it).coef)) + "*";
		}
		if ((*it).index / 100 != 0) {
			result += "x";
			if ((*it).index / 100 != 1)
				result += "^" + std::to_string((*it).index / 100);
			result += "*";
		}
		if ((*it).index % 100 / 10 != 0) {
			result += "y";
			if ((*it).index % 100 / 10 != 1)
				result += "^" + std::to_string((*it).index % 100 / 10);
			result += "*";
		}
		if ((*it).index % 10 != 0) {
			result += "z";
			if ((*it).index % 10 != 1)
				result += "^" + std::to_string((*it).index % 10);
		}
		if (result[result.size() - 1] == '*')
			result.pop_back();
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