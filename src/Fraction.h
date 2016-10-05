#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>

class Fraction {
public:	
	Fraction(long n = 0, long d = 1);  // takes 0, 1 and 2 args
	Fraction(const Fraction &) = default;
	~Fraction() = default;

	long getNum() const;
	long getDen() const;
	void setNum(long n);
	void setDen(long d);

	void normalize();	// sets a positive denominator to fraction
	void reduce();		// reduces fraction to lowest terms

	// Member operator overloads
	Fraction& operator=(const int& val); // f = i
	Fraction& operator+=(const int& val); // f += i
	Fraction& operator-=(const int& val); // f -= i
	Fraction& operator*=(const int& val); // f *= i
	Fraction& operator/=(const int& val); // f /= i

	Fraction& operator=(const Fraction& rhs); // f = f
	Fraction& operator+=(const Fraction& rhs); // f += f
	Fraction& operator-=(const Fraction& rhs); // f -= f
	Fraction& operator*=(const Fraction& rhs); // f *= f
	Fraction& operator/=(const Fraction& rhs); // f /= f

	Fraction& operator++(); // ++f
	Fraction& operator--(); // --f

	std::string operator()() const; // returns the string version of this fraction
	Fraction& operator*(); // make Fraction objects behave like pointers: returns *this

	// [s] returns the numerator if s = "top"; otherwise, returns denominator
	// Caution! allows access and modification of private members w/o normalization,
	//reduction and zero denominator assertion
	long& operator[](const std::string &s);

	// [s] returns the numerator if s = "top"; otherwise, returns denominator
	const long& operator[](const std::string &s) const;

	// The following operators are usually overloaded as members
	Fraction operator+() const; // + f
	Fraction operator-() const; // - f

	/*returns copy of this Fraction before increment*/
	Fraction operator++(int); // f++
	/*returns copy of this Fraction before decrement*/
	Fraction operator--(int); // f--

private:
	long num;	// numerator
	long den;	// denominator

	long findGCD(long a, long b);		// finds GCD between 2 numbers

}; // end of class

// Non-member operator overloads
Fraction operator+(const Fraction& lhs, const Fraction& rhs); // f + f
Fraction operator+(const Fraction& lhs, const int& val); // f + i
Fraction operator+(const int& val, const Fraction& rhs); // i + f

Fraction operator-(const Fraction& lhs, const Fraction& rhs); // f - f
Fraction operator-(const Fraction& lhs, const int& val); // f - i
Fraction operator-(const int& val, const Fraction& rhs); // i - f

Fraction operator*(const Fraction& lhs, const Fraction& rhs); // f * f
Fraction operator*(const Fraction& lhs, const int& val); // f * i
Fraction operator*(const int& val, const Fraction& rhs); // i * f

Fraction operator/(const Fraction& lhs, const Fraction& rhs); // f / f
Fraction operator/(const Fraction& lhs, const int& val); // f / i
Fraction operator/(const int& val, const Fraction& rhs); // i / f

bool operator==(const Fraction& lhs, const Fraction& rhs); // f == f
bool operator==(const Fraction& lhs, const int& val); // f == i
bool operator==(const int& val, const Fraction& rhs); // i == f

bool operator!=(const Fraction& lhs, const Fraction& rhs); // f != f
bool operator!=(const Fraction& lhs, const int& val); // f != i
bool operator!=(const int& val, const Fraction& rhs); // i != f

bool operator<(const Fraction& lhs, const Fraction& rhs); // f < f
bool operator<(const Fraction& lhs, const int& val); // f < i
bool operator<(const int& val, const Fraction& rhs); // i < f

bool operator<=(const Fraction& lhs, const Fraction& rhs); // f <= f
bool operator<=(const Fraction& lhs, const int& val); // f <= i
bool operator<=(const int& val, const Fraction& rhs); // i <= f

bool operator>(const Fraction& lhs, const Fraction& rhs); // f < f
bool operator>(const Fraction& lhs, const int& val); // f < i
bool operator>(const int& val, const Fraction& rhs); // i < f

bool operator>=(const Fraction& lhs, const Fraction& rhs); // f <= f
bool operator>=(const Fraction& lhs, const int& val); // f <= i
bool operator>=(const int& val, const Fraction& rhs); // i <= f

std::istream& operator>>(std::istream& istr, Fraction& rhs);
std::ostream& operator<<(std::ostream& ostr, const Fraction& rhs);

#endif