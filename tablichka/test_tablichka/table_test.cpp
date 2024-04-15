#include <..\..\gtest\gtest.h>
#include "..\..\..\postfix\postfixlib\postfix.h"
using namespace postfix;
//Проверка удаления пробелов
TEST(Calculator, Remove_Space)
{
	EXPECT_EQ("(a+b)",RemoveSpace("(a   +   b)"));
}
//Проверка преобразование в целое число
TEST(Calculator, To_Double_Int)
{
	int i = 0;
	EXPECT_EQ(12, (int)ToDouble("12adfa",i));
}
//Проверка преобразование в дробное число
TEST(Calculator, To_Double_Float)
{
	int i = 0;
	EXPECT_EQ(12.25, ToDouble("12.25adfa", i));
}
//Проверка взятия многострочной переменной
TEST(Calculator, To_String_Var)
{
	int i = 0;
	EXPECT_EQ(string("adfa"), ToStringVar("adfa + adfd", i));
}
//Проверка верной скобочной последовательности
TEST(Calculator, The_correct_bracket_sequence)
{
	bool flag = true;
	flag = flag && CheckFormula("(a + b)");
	flag = flag && CheckFormula("(a + b + (c + g))");
	flag = flag && CheckFormula("(a + (b + (c + d)))");
	flag = flag && CheckFormula("(((a + 1) + 2) + 3)");
	flag = flag && CheckFormula("(a + (c + d) + b)");
	flag = flag && CheckFormula("(a + b - c + d)");
	EXPECT_EQ(true, flag);
}
//Проверка неверной скобочной последовательности
TEST(Calculator, Incorrect_bracket_sequence)
{
	bool flag = false;
	flag = flag || CheckFormula("((a + b)");
	flag = flag || CheckFormula("(a + b))");
	flag = flag || CheckFormula(") a + b (");
	flag = flag || CheckFormula("() a + b");
	flag = flag || CheckFormula("(a + ) b + c ( + d )");
	EXPECT_EQ(false,flag);
}
//Проверка пустых скобок
TEST(Calculator, Empty_brackets)
{
	bool flag = CheckFormula("( )");
	EXPECT_EQ(false, flag);
}
//Проверка введенных операций
TEST(Calculator, Operations_are_correct)
{
	bool flag = true;
	flag = flag && CheckFormula("(a + b)");
	flag = flag && CheckFormula("(a + b - c * d / k)");
	flag = flag && CheckFormula("(a + (b + (c + d)))");
	flag = flag && CheckFormula("(a % b)");
	EXPECT_EQ(true, flag);
}
//Проверка неверно введенной операции
TEST(Calculator, Operations_are_not_correct)
{
	bool flag = false;
	flag = flag || CheckFormula("(a + - b)");
	flag = flag || CheckFormula("(a -+ b");
	EXPECT_EQ(false, flag);
}
//Проверкак многосимвольных переменных
TEST(Calculator, Multi_character_variables)
{
	bool flag = CheckFormula("(abc + bca)");
	EXPECT_EQ(true , flag);
}
//Проверка многосимвольных чисел
TEST(Calculator, Multi_character_numbers)
{
	bool flag = CheckFormula("(123 + 234)");
	EXPECT_EQ(true, flag);
}
//Проверка дробных чисел
TEST(Calculator, Fractional_numbers)
{
	bool flag = CheckFormula("(1.23 + 2.34)");
	EXPECT_EQ(true, flag);
}
//Проверка ввода формулы без ошибки
TEST(Calculator, Creating_a_calculator_not_throw)
{
	ASSERT_NO_THROW(calculator a("(a + b)"));
}
//Проверка ввода формулы с ошибкой
TEST(Calculator, Creating_a_calculator_throw)
{
	ASSERT_ANY_THROW(calculator a("((a + b)"));
}
//Верная постфиксная запись
//TEST(Calculator, Correct_postfix_entry)
//{
//	calculator c("((12 + ab) * 4 + c) / 3 + 9 * k - 1");
//	bool flag = "12 ab + 4 * c + 3 / 9 k * + 1 - " == c.GetPostfix();
//	c.SetFormula("(a + b)");
//	flag = flag && "a b + " == c.GetPostfix();
//	c.SetFormula("(a + b - 1.23 + rar * (1 - 34 + 12))");
//	flag = flag && "a b + 1.23 - rar 1 34 - 12 + * + " == c.GetPostfix();
//	EXPECT_EQ(true, flag);
//}
//Верный подсчет
TEST(Calculator, Ansver_Goot)
{
	calculator c("((12 + 4) * 4 + 2) / 3 + 9 * 16 - 1");
	bool flag = 165 == c.Ansver();
	c.SetFormula("(12 + 4)");
	flag = flag && 16 == c.Ansver();
	c.SetFormula("(10 % 3)");
	flag = flag && 1 == c.Ansver();
	EXPECT_EQ(true, flag);
}
//Получения map переменных
TEST(Calculator, Get_Var)
{
	calculator c("((12 + ab) * 4 + c) / 3 + 9 * k - 1");
	auto k = c.GetVar();
	bool flag = k.find("ab") != k.end() && k.find("c") != k.end() && k.find("k") != k.end();
	EXPECT_EQ(true, flag);
}
//Задать переменные без ошибки
TEST(Calculator, Set_Var)
{
	calculator c("((12 + ab) * 4 + c) / 3 + 9 * k - 1");
	auto k = c.GetVar();
	k.at("ab") = 10;
	k.at("c") = 2;
	k.at("k") = 3;
	c.SetVar(k);
	EXPECT_EQ(56, c.Ansver());
}
//Константы отсутствуют в списке переменных
TEST(Calculator, Const_Not_In_Var)
{
	calculator c("Pi + e");
	auto var = c.GetVar();
	EXPECT_EQ(var.empty(), true);
}
//Добавление или удаление переменной из списка не вызывает ошибки
TEST(Calculator, Deletingand_unnecessary_variables)
{
	calculator c("((12 + ab) * 4 + c) / 3 + 9 * k - 1");
	auto k = c.GetVar();
	k.erase("c");
	k.insert({ "t", 10 });
	ASSERT_NO_THROW(c.SetVar(k));
}
//Проверка функции CheckNumber
TEST(Calculator, Check_Number)
{
	bool ans = true;
	ans = ans && CheckNumber('0') && CheckNumber('9') && CheckNumber('5') && CheckNumber('.');
	ans = ans && !CheckNumber('a') && !CheckNumber('-') && !CheckNumber(':') && !CheckNumber('+');
	EXPECT_EQ(true, ans);
}
//Проверка функции CheckChar
TEST(Calculator, Check_Char)
{
	bool ans = true;
	ans = ans && CheckChar('a') && CheckChar('A') && CheckChar('z') && CheckChar('Z') && CheckChar('o') && CheckChar('O');
	ans = ans && !CheckChar('1') && !CheckChar('-') && !CheckChar(':') && !CheckChar(' ');
	EXPECT_EQ(true, ans);
}
//Проверка функции CheckOperator
TEST(Calculator, Check_Operator)
{
	bool ans = true;
	ans = ans && CheckOperator('+') && CheckOperator('-') && CheckOperator('*') && CheckOperator('/') && CheckOperator('%');
	ans = ans && !CheckOperator('a') && !CheckOperator('1') && !CheckOperator('_') && !CheckOperator('A');
	ans = ans && CheckOperator("+") && CheckOperator("-") && CheckOperator("*") && CheckOperator("/");
	ans = ans && !CheckOperator("a") && !CheckOperator("1") && !CheckOperator("_") && !CheckOperator("A");
	EXPECT_EQ(true, ans);
}
//Проверка функции CheckFormula на !
TEST(Calculator, Check_Formul_Factorial)
{
	bool flag = true;
	flag = flag && CheckFormula("(a! + b)");
	flag = flag && CheckFormula("(12! + b)");
	flag = flag && CheckFormula("(a + b + (c + g)!)");
	flag = flag && !CheckFormula("(a +! b)");
	flag = flag && !CheckFormula("(!a + b)");
	flag = flag && !CheckFormula("(-!a + b)");
	flag = flag && !CheckFormula("(a + !(b - c) + d)");
	flag = flag && !CheckFormula("(a + !12 + d)");
	flag = flag && !CheckFormula("(a + !a + d)");
	EXPECT_EQ(true, flag);
}
//Проверка верного подсчета факториала
TEST(Calculator, AnsverFactorial)
{
	calculator c("(5!)");
	bool flag = 120 == c.Ansver();
	c.SetFormula("(1 + (1 + 2)!)");
	flag = flag && 7 == c.Ansver();
	EXPECT_EQ(true, flag);
}
//Проверка правильности ввода функций
TEST(Calculator, Check_Func)
{
	bool ans = true;
	ans = ans && CheckFormula("(ln(a))") && CheckFormula("(ln(a + b))") && CheckFormula("(ln(sin(3)))");
	ans = ans && CheckFormula("(pow(1,2))") && CheckFormula("(pow(a + b,2 + 4))");
	ans = ans && CheckFormula("(ln(pow(1,2)))");
	ans = ans && CheckFormula("(pow(1,ln(e)))") && CheckFormula("(pow(ln(e),ln(e)))") && CheckFormula("(pow(pow(e,1),pow(1,e)))");
	ans = ans && CheckFormula("(a + pow(ln(e),3) - sin(pi)! + pow(2,pow(2,3)))");

	ans = ans && !CheckFormula("(ln(a,2))") && !CheckFormula("(ln(a + b)") && !CheckFormula("(ln(sin3)))");
	ans = ans && !CheckFormula("(pow(1))") && !CheckFormula("(pow(a + b,2 + 4)") && !CheckFormula("(pow1))");
	EXPECT_EQ(true, ans);
}
//Проверка правильности Польской записи с функциями
TEST(Calculator, Convert_Func)
{
	bool ans = true;
	calculator c("ln(a)");
	ans = ans && c.GetPostfix() == "a ln ";
	c.SetFormula("ln(a + b)");
	ans = ans && c.GetPostfix() == "a b + ln ";
	c.SetFormula("ln(sin(3))");
	ans = ans && c.GetPostfix() == "3 sin ln ";
	c.SetFormula("pow(1,2)");
	ans = ans && c.GetPostfix() == "1 2 pow ";
	c.SetFormula("pow(a + b,2 + 4)");
	ans = ans && c.GetPostfix() == "a b + 2 4 + pow ";
	c.SetFormula("ln(pow(1,2))");
	ans = ans && c.GetPostfix() == "1 2 pow ln ";
	c.SetFormula("pow(1,ln(e))");
	ans = ans && c.GetPostfix() == "1 e ln pow ";
	c.SetFormula("pow(ln(e),ln(e))");
	ans = ans && c.GetPostfix() == "e ln e ln pow ";
	c.SetFormula("pow(pow(e,1),pow(1,e))");
	ans = ans && c.GetPostfix() == "e 1 pow 1 e pow pow ";
	c.SetFormula("a + pow(ln(e),3) - sin(pi)! + pow(2,pow(2,3))");
	ans = ans && c.GetPostfix() == "a e ln 3 pow + pi sin ! - 2 2 3 pow pow + ";
	EXPECT_EQ(true, ans);
}
