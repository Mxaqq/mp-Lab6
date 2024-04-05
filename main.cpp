#include <iostream>
#include "table.h"
#include "maneg.h"
#include "postfix.h"
#include <conio.h>
#include <string>
#include <Windows.h>
using namespace std;

int vibor(int kol);
int nowvibor(int kol);

void NotKey() {
	cout << "Äàííûé êëþ÷ â òàáëèöå íå îáíàðóæåí" << endl;
	system("pause");
	system("cls");
}

TPolinom* GetPolinom(maneger& men, string& k = string("key")) {
	TPolinom* temp;
	do {
		cout << "Ââåäèòå êëþ÷:" << endl;
		getline(cin, k);
		while (k == "")
			getline(cin, k);
		temp = men.Find(k);
		if (temp == nullptr) NotKey();
	} while (temp == nullptr);
	return temp;
}

int main() {

	maneger men;


	setlocale(LC_ALL, "ru");
	int wibor;
	int nowwibor;
	do {
		system("cls");
		cout << "\tÌåíþ:\n1)Îïåðàöèè íàä îòäåëüíûìè ïîëèíîìàìè\n2)Îïåðàöèè â âûðàæåíèÿõ èç ïîëèíîìîâ\n3)Îïåðàöèè íàä òàáëèöàìè\n4)Âûáîð òàáëèö\n";
		wibor = vibor(5);
		system("cls");
		if (wibor == 1) {

			system("cls");
			cout << "\tÌåíþ:\n1)Âû÷èñëåíèå â òî÷êå\n2)Óìíîæåíèå íà êîíñòàíòó\n3)Ïðîèçâîäíàÿ\n4)Èíòåãðàë\n";
			nowwibor = nowvibor(5);
			system("cls");
			if (nowwibor == 1) {
				TPolinom* temp = GetPolinom(men);
				postfix::calculator a((*temp).ToPostfix());
				auto var = a.GetVar();
				for (auto& a : var) {
					cout << a.first << " = ";
					cin >> a.second;
				}
				a.SetVar(var);
				system("cls");
				cout << a.Ansver() << endl;
				system("pause");
				nowwibor = 5;
			}
			if (nowwibor == 2) {
				int n;
				string k;
				TPolinom polinom = *GetPolinom(men, k);
				cout << "Ââåäèòå êîíñòàíòó:" << endl;
				cin >> n;
				polinom = polinom.operator*(n);
				men.Insert(k + "*" + to_string(n), polinom);
				nowwibor = 5;
			}
			if (nowwibor == 3) {
				char n; string k;
				TPolinom polin = *GetPolinom(men, k);
				cout << "Ââåäèòå ïî êàêîé ïåðåìåííîé õîòèòå íàéòè ïðîèçâîäíóþ:" << endl;
				cin >> n;
				men.Insert(k + "_der", polin.derivative(n));
				nowwibor = 5;
			}
			if (nowwibor == 4) {
				char n; string k;
				TPolinom polin = *GetPolinom(men, k);
				cout << "Ââåäèòå ïî êàêîé ïåðåìåííîé õîòèòå âû÷èñëèòü èíòåãðàë:" << endl;
				cin >> n;
				men.Insert(k + "_ins", polin.Integral(n));
				nowwibor = 5;
			}
			while (nowwibor != 5);
		}




		if (wibor == 2)
		{

			system("cls");
			cout << "\tÌåíþ:\n1)Ñëîæåíèå\n2)Âû÷èòàíèå\n3)Óìíîæåíèå íà êîíñòàíòó\n4)Óìíîæåíèå ïîëèíîìîâ\n5)Äåëåíèå ïîëèíîìîâ\n";
			nowwibor = nowvibor(6);
			system("cls");
			if (nowwibor == 1) {
				string k; string g;
				men.Insert(k + "+" + g, *GetPolinom(men, k) + *GetPolinom(men, g));
				cout << *men.Find(k + "+" + g);
				system("pause");
				nowwibor = 6;
			}
			if (nowwibor == 2) {
				string k; string g;
				men.Insert(k + "-" + g, *GetPolinom(men, k) - *GetPolinom(men, g));
				cout << *men.Find(k + "-" + g);
				system("pause");
				nowwibor = 6;
			}
			if (nowwibor == 3) {
				double n; string k;
				TPolinom polinom = *GetPolinom(men, k);
				cout << "Ââåäèòå êîíñòàíòó:" << endl;
				cin >> n;
				polinom = polinom * n;
				men.Insert(k + "*" + to_string(n), polinom);
				cout << *men.Find(k + "*" + to_string(n));
				system("pause");
				nowwibor = 6;
			}
			if (nowwibor == 4) {
				string k; string g;
				men.Insert(k + "*" + g, *GetPolinom(men, k) * *GetPolinom(men, g));
				cout << *men.Find(k + "*" + g);
				system("pause");
				nowwibor = 6;
			}
			if (nowwibor == 5) {
				string k; string g;
				men.Insert(k + "/" + g, *GetPolinom(men, k) / *GetPolinom(men, g));
				cout << *men.Find(k + "/" + g);
				system("pause");
				nowwibor = 6;
			}
			while (nowwibor != 6);
		}


		if (wibor == 3) {

			system("cls");
			cout << "\tÌåíþ:\n1)Äîáàâëåíèå ïîëèíîìà\n2)Óäàëåíèå ïîëèíîìà\n3)Ïîèñê\n4)Âûâîä àêòèâíîé òàáëèöû íà ýêðàí\n";
			nowwibor = nowvibor(5);
			system("cls");
			if (nowwibor == 1) {
				cout << "Ââåäèòå êëþ÷:" << endl;
				string k; getline(cin, k);
				while (k == "")
					getline(cin, k);
				cout << "Ââåäèòå ïîëèíîì:" << endl;
				string s; getline(cin, s);
				while (s == "")
					getline(cin, s);
				TPolinom polinom(s);
				men.Insert(k, polinom);
				nowwibor = 5;
			}
			if (nowwibor == 2) {
				string k;
				GetPolinom(men, k);
				men.Delete(k);
				nowwibor = 5;
			}
			if (nowwibor == 3) {
				cout << *GetPolinom(men);
				system("pause");
				nowwibor = 5;
			}
			if (nowwibor == 4) {
				cout << men;
				system("pause");
				nowwibor = 5;
			}
			while (nowwibor != 5);
		}

		if (wibor == 4) {

			system("cls");
			cout << "\tÌåíþ:\n1)Ëèíåéíàÿ òàáëèöà íà ìàññèâå\n2)Ëèíåéíàÿ òàáëèöà íà ñïèñêå\n3)Óïîðÿäî÷åííàÿ òàáëèöà íà ìàññèâå\n4)Äåðåâî\n5)Ïåðâàÿ õýø-òàáëèöà\n6)Âòîðàÿ õýø-òàáëèöà\n";
			nowwibor = nowvibor(7);
			system("cls");
			if (nowwibor == 1) {
				men.ChooseTable("LinerOnArray");
				nowwibor = 7;
			}
			if (nowwibor == 2) {
				men.ChooseTable("LinearOnList");
				nowwibor = 7;
			}
			if (nowwibor == 3) {
				men.ChooseTable("OrderedOnArray");
				nowwibor = 7;
			}
			if (nowwibor == 4) {
				men.ChooseTable("Tree");
				nowwibor = 7;
			}
			if (nowwibor == 5) {
				men.ChooseTable("HashList");
