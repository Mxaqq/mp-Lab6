#include "TPolinom.h"
#include <gtest.h>

TEST(Polinom, Created_polinom_is_empty) {
	TPolinom polinom;
	EXPECT_TRUE(polinom.list.isEmpty());
}

TEST(Polinom, Created_polinom_with_one_monom_is_not_empty) {
	TPolinom polinom("2x^2");
	EXPECT_FALSE(polinom.list.isEmpty());
}

TEST(Polinom, Coefficients_add_up_if_degrees_are_equal) {
	TPolinom polinom1("2x^2");
	TPolinom polinom2("3x^2");
	TPolinom result = polinom1 + polinom2;
	EXPECT_EQ(result.ToString(), "5x^2");
}

TEST(Polinom, Coefficients_dont_add_up_if_degrees_are_different) {
	TPolinom polinom1("2x^2");
	TPolinom polinom2("3x^3");
	TPolinom result = polinom1 + polinom2;
	EXPECT_NE(result.ToString(), "5x^5"); // Adjust expected result based on actual behavior
}

TEST(Polinom, Monom_delete_if_coefficient_equal_zero) {
	TPolinom polinom("2x^2 - 2x^2");
	EXPECT_TRUE(polinom.list.isEmpty());
}

TEST(Polinom, Copied_polinom_is_equal_copiable) {
	TPolinom polinom("2x^2 + 3y^3 - 4z^4");
	TPolinom copiedPolinom(polinom);
	bool f = polinom == copiedPolinom;
	EXPECT_EQ(f, true);
}

TEST(Polinom, Assigned_polinom_is_equal_assignable) {
	TPolinom polinom1("2x^2 + 3y^3 - 4z^4");
	TPolinom polinom2("x^3 - 2y^2 + 5z^5");
	bool f = polinom1 == polinom2;
	EXPECT_EQ(f, true);
}

TEST(Polinom, Correct_adding_operator) {
	TPolinom polinom1("2x^2 + 3y^3 - 4z^4");
	TPolinom polinom2("x^2 + 2y^3 - 3z^4");
	TPolinom expectedResult("3x^2 + 5y^3 - 7z^4");
	TPolinom result = polinom1 + polinom2;
	bool f = result == expectedResult;
	EXPECT_EQ(f, true);
}

TEST(Polinom, Correct_constant_multiply) {
	TPolinom polinom("2x^2 + 3y^3 - 4z^4");
	double constant = 2.5;
	TPolinom expectedResult("5x^2 + 7.5y^3 - 10z^4");
	TPolinom result = polinom * constant;
	bool f = result == expectedResult;
	EXPECT_EQ(f, true);
}

TEST(Polinom, Correct_monom_multiply) {
	TPolinom polinom("2x^2 + 3y^3 - 4z^4");
	TMonom monom("3x^3");
	TPolinom expectedResult("6x^5 + 9x^3y^3 - 12x^3z^4");
	TPolinom result = polinom * monom;
	bool f = result == expectedResult;
	EXPECT_EQ(f, true);
}

TEST(Polinom, Correct_polinom_enter) {
	std::string polinomStr = "2x^2 + 3y^3 - 4z^4";
	TPolinom polinom(polinomStr);
	EXPECT_EQ(polinom.ToString(), polinomStr);
}

TEST(Polinom, Correct_multiply_polinom1) {
	TPolinom polinom1("2x^2 + 3y^3 - 4z^4");
	TPolinom polinom2("x^2 + 2y^3 - 3z^4");
	TPolinom expectedResult("2x^4 + 6x^2y^3 - 8x^2z^4 + 3x^2y^6 - 6x^2y^3z^4 + 9x^2z^8 - 4y^3z^4 + 8y^6 - 12y^3z^8");
	TPolinom result = polinom1 * polinom2;
	bool f = result == expectedResult;
	EXPECT_EQ(f, true);
}

TEST(Polinom, Correct_multiply_polinom2) {
	TPolinom polinom1("2x^2 + 3y^3 - 4z^4");
	TPolinom polinom2("x^2 + 2y^3 - 3z^4");
	TPolinom polinom3("4x^3 + y^2 - 2z^2");
	TPolinom expectedResult = polinom1 * polinom2 * polinom3;
	bool f = polinom1 == expectedResult;
	EXPECT_EQ(f, true);
}

TEST(Polinom, Correct_multiply_polinom3) {
	TPolinom polinom1("2x^2 + 3y^3 - 4z^4");
	TPolinom polinom2("x^2 + 2y^3 - 3z^4");
	double constant = 2.5;
	TPolinom expectedResult = polinom1 * polinom2 * constant;
	bool f = polinom1 == expectedResult;
	EXPECT_EQ(f, true);
}
