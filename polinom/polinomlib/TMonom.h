#pragma once
#include <string>
#include <stack>
using namespace std;

bool CheckNumber(char c)
{
	return (c >= '0' && c <= '9' || c == '.');
}

bool CheckChar(char c) {
	return (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_');
}

bool CheckRes(char c) {
	return c == '-';
}

double ToDouble(string s, int& i);

string ToStringVar(string s, int& i);

struct TMonom
{
	double coef; 
	int index; 
	TMonom();
	TMonom(string s);
	TMonom(double coef, int degX = 0, int degY = 0, int degZ = 0);
	void SetCoef(int cval) { coef = cval; }
	int GetCoef(void) { return coef; }
	void SetIndex(int ival) { index = ival; }
	int GetIndex(void) { return index; }
	bool operator==(const TMonom& other) { return  this->index == other.index; }
	bool operator>(const TMonom& other);
	bool operator<(const TMonom& other) { return  !(this->operator>(other) && this->operator==(other)); }
	TMonom& operator*(const TMonom& other);
	TMonom derivative(char c);
	TMonom Integral(char c);
	TMonom operator/(TMonom& other);

};



TMonom::TMonom()
{
	this->coef = 1;
	this->index = 0;
}

TMonom::TMonom(string s) :TMonom()
{
	stack<string> st;
	int i = 0;
	while (i < s.size()) {
		if (CheckRes(s[i])) {
			st.push("-");
		}
		else if (CheckNumber(s[i])) {
			double temp = ToDouble(s, i);
			if (st.empty())
				coef = temp;
			else if (st.top() == "-") {
				coef = -temp;
				st.pop();
			}
			else if (st.top() == "^") {
				st.pop();
				if (st.top() == "x" || st.top() == "X")
					index += 100 * temp;
				if (st.top() == "y" || st.top() == "Y")
					index += 10 * temp;
				if (st.top() == "z" || st.top() == "Z")
					index += temp;
				st.pop();
			}

		}
		else if (CheckChar(s[i])) {
			string var; var += s[i];
			if (st.empty())
				st.push(var);
			else if (st.top() == "-") {
				coef = -1;
				st.pop();
				st.push(var);
			}
			else {
				if (st.top() == "x" || st.top() == "X")
					index += 100;
				if (st.top() == "y" || st.top() == "Y")
					index += 10;
				if (st.top() == "z" || st.top() == "Z")
					index += 1;
				st.pop();
				st.push(var);
			}
		}
		else if (s[i] == '^') {
			st.push("^");
		}
		i++;
	}
	if (!st.empty()) {
		if (st.top() == "x" || st.top() == "X")
			index += 100;
		if (st.top() == "y" || st.top() == "Y")
			index += 10;
		if (st.top() == "z" || st.top() == "Z")
			index += 1;
		st.pop();
	}
}

inline TMonom::TMonom(double coef, int degX, int degY, int degZ)
{
	if (degX > 9 || degY > 9 || degZ > 9)
		throw exception("deg > 9");
	this->coef = coef;
	this->index = 100 * degX + 10 * degY + degZ;
}

inline bool TMonom::operator>(const TMonom& other)
{
	if (this->index / 100 == other.index / 100) {
		if ((this->index % 100) / 10 == (other.index % 100) / 10) {
			if (this->index % 10 == other.index % 10) {
				return false;
			}
			else
				return this->index % 10 > other.index % 10;
		}
		else
			return (this->index % 100) / 10 > (other.index % 100) / 10;
	}
	else
		return this->index / 100 > other.index / 100;
}

inline TMonom& TMonom::operator*(const TMonom& other)
{
	if (this->index / 100 + other.index / 100 > 9)
		throw exception("of range");
	if ((this->index % 100) / 10 + (other.index % 100) / 10 > 9)
		throw exception("of range");
	if (this->index % 10 + other.index % 10 > 9)
		throw exception("of range");
	TMonom temp;
	temp.index = this->index + other.index;
	temp.coef = this->coef * other.coef;
	return temp;
}

inline TMonom TMonom::derivative(char c)
{
	bool flag = false;
	TMonom temp = *this;
	if ((c == 'X' || c == 'x') && temp.index >= 100) {
		temp.coef *= (index / 100);
		temp.index -= 100;
		flag = true;
	}
	if ((c == 'Y' || c == 'y') && (temp.index % 100) >= 10) {
		temp.coef *= (index % 100 / 10);
		temp.index -= 10;
		flag = true;
	}
	if (c == 'Z' || c == 'z' && (temp.index % 10) >= 1) {
		temp.coef *= (index % 10);
		temp.index -= 1;
		flag = true;
	}
	if (!flag) {
		temp.index = 0;
		temp.coef = 0;
	}
	return temp;
}

inline TMonom TMonom::Integral(char c)
{
	TMonom temp = *this;
	if ((c == 'X' || c == 'x') && temp.index < 900) {
		temp.index += 100;
		temp.coef /= (temp.index / 100);
	}
	if ((c == 'Y' || c == 'y') && (temp.index % 100) < 90) {
		temp.index += 10;
		temp.coef /= ((temp.index % 100) / 10);
	}
	if (c == 'Z' || c == 'z' && (temp.index % 10) < 9) {
		temp.index += 1;
		temp.coef /= (temp.index % 10);
	}
	return temp;
}

inline TMonom TMonom::operator/(TMonom& other)
{
	if (this->index / 100 - other.index / 100 < 0)
		throw exception("of range");
	if ((this->index % 100) / 10 - (other.index % 100) / 10 < 0)
		throw exception("of range");
	if (this->index % 10 - other.index % 10 < 0)
		throw exception("of range");
	TMonom temp;
	temp.index = this->index - other.index;
	temp.coef = this->coef / other.coef;
	return temp;
}


double ToDouble(string s, int& i) {
	double k = 0;
	int kol = 0;
	while (s[i] != '\0' && CheckNumber(s[i])) {
		if (s[i] != '.')
			k = k * 10 + (s[i] - 48);
		if (s[i] == '.' || kol != 0)
			kol++;
		i++;
	}
	i--;
	return k / pow(10, ((kol == 0) ? 0 : kol - 1));
}

string ToStringVar(string s, int& i) {
	string temp;
	char c = s[i];
	while (c != '\0' && CheckChar(c)) {
		temp += s[i];
		i++;
		c = s[i];
	}
	i--;
	return temp;
}