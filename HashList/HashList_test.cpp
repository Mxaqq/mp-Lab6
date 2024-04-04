#include <gtest.h>
#include "HashList.h"




//Ïðîâåðêà ïîèñêà ñóøåñòâóþùåãî çíà÷åíèÿ
TEST(HashList, Find_exists_value)
{
	HashList<string, int> table;
	table.Insert("1", 1);
	table.Insert("2", 2);
	table.Insert("3", 3);
	EXPECT_EQ(*table.Find("2"), 2);
}


//Ïðîâåðêà ïîèñêà íå ñóøåñòâóþùåãî çíà÷åíèÿ
TEST(HashList, Find_not_exists_value)
{
	HashList<string, int> table;
	table.Insert("1", 1);
	table.Insert("2", 2);
	table.Insert("3", 3);
	EXPECT_EQ(table.Find("4"), nullptr);
}

//Ïðîâåðêà äîáàâëåíèÿ â òàáëèöó íîâîãî ýëåìåíòà
TEST(HashList, insert_new_value)
{
	HashList<string, int> table;
	table.Insert("1", 1);
	table.Insert("2", 2);
	table.Insert("3", 3);
	EXPECT_EQ(*table.Find("2"), 2);
}

//Ïðîâåðêà äîáàâëåíèÿ â òàáëèöó íîâîãî ýëåìåíòà ñ ñóùèñòâóþùèì êëþ÷îì
TEST(LinerOnList, insert_new_value_repit_key)
{
	HashList<string, int> table;
	table.Insert("1", 1);
	table.Insert("2", 2);
	table.Insert("3", 3);
	bool temp = table.Insert("3", 12);
	EXPECT_EQ(temp, false);
}

//Óäàëåíèå ýëåìåíòà èç òàáëèöû
TEST(HashList, delete_line)
{
	HashList<string, int> table;
	table.Insert("1", 1);
	table.Insert("2", 2);
	table.Insert("3", 3);
	table.Delete("2");
	EXPECT_EQ(table.Find("2"), nullptr);
}

//Óäàëåíèå ýëåìåíòà èç òàáëèöû ñ íåñóùèñòâóþøèì êëþ÷îì
TEST(HashList, delete_line_not_key)
{
	HashList<string, int> table;
	table.Insert("1", 1);
	table.Insert("2", 2);
	table.Insert("3", 3);
	bool temp = table.Delete("4");
	EXPECT_EQ(temp, false);
}

//Óäàëåíèå ýëåìåíòà èç ïóñòîé òàáëèöû
TEST(HashList, delete_line_empty_table)
{
	HashList<string, int> table;
	bool temp = table.Delete("4");
	EXPECT_EQ(temp, false);
}

//Îáõîä òàáëèöû ïî ýëåìåíòíî
TEST(HashList, go_table)
{
	HashList<string, int> table;
	table.Insert("1", 1);
	table.Insert("2", 2);
	table.Insert("3", 3);
	int k = 0;
	for (table.Reset(); !table.IsTabEnded(); table.GoNext()) {
		k += table.GetValuePtr();
	}
	EXPECT_EQ(k, 6);
}

//Îáõîä ïîëó÷åíèå ýëåìåíòà
TEST(HashList, get_value)
{
	HashList<string, int> table;
	table.Insert("1", 1);
	table.Insert("2", 2);
	table.Insert("3", 3);
	int k = 0;
	for (table.Reset(); !table.IsTabEnded(); table.GoNext()) {
		k += table.GetValuePtr();
	}
	EXPECT_EQ(k, 6);
}


//Îáõîä ïîëó÷åíèå êëþ÷åé
TEST(HashList, get_key)
{
	HashList<string, int> table;
	table.Insert("1", 1);
	table.Insert("2", 2);
	table.Insert("3", 3);
	string s;
	for (table.Reset(); !table.IsTabEnded(); table.GoNext()) {
		s += table.GetKey();
	}
	EXPECT_EQ(s, "123");
}
