#include <iostream>
#include "..\stack\stacklib\TStack.h"
using namespace std;

void f(MaxStack<double>& a) {
	cout << a.size();
}

int main() {

	MaxStack<double> temp;
	temp.push(1.1);
	temp.push(2.2);
	temp.push(3.3);
	/*cout << temp.size();
	while (!temp.empty()) {
		cout << temp.top() << endl;
		temp.pop();
	}*/
	cout << endl;
	temp.pop();
	f(temp);
}
