#include <cassert>
#include <string>
#include "Fraction.h"

using namespace std;

Fraction::Fraction(long n, long d) : num(n), den(d)
{
	assert(d != 0); // denominator = 0 is not allowed
	normalize();
	reduce();
}

// Accessors and mutators
long Fraction::getNum() const
{
	return num;
}

long Fraction::getDen() const
{
	return den;
}

void Fraction::setNum(long n)
{
	num = n;
	reduce();
}

void Fraction::setDen(long d)
{
	assert(d != 0);
	den = d;
	normalize();
	reduce();
}

// Member operator overloads
Fraction& Fraction::operator=(const int& val) // f = i
{
	num = val;
	den = 1;
	return *this;
}

Fraction& Fraction::operator+=(const int& val) // f += i
{
	*this = Fraction{ num + den * val , den };
	return *this;
}

Fraction& Fraction::operator-=(const int& val) // f -= i
{
	*this = Fraction{ num - den * val , den };
	return *this;
}

Fraction& Fraction::operator*=(const int& val) // f *= i
{
	*this = Fraction{ num * val , den };
	return *this;
}

Fraction& Fraction::operator/=(const int& val) // f /= i
{
	*this = Fraction{ num, den * val };
	return *this;
}

Fraction& Fraction::operator=(const Fraction& rhs) // f = f
{
	if (this == &rhs)
		return *this;
	num = rhs.num;
	den = rhs.den;
	return *this;
}

Fraction& Fraction::operator+=(const Fraction& rhs) // f += f
{
	*this = Fraction{ num * rhs.den + den * rhs.num, den * rhs.den };
	return *this;
}

Fraction& Fraction::operator-=(const Fraction& rhs) // f -= f
{
	*this = Fraction{ num * rhs.den - den * rhs.num, den * rhs.den };
	return *this;
}

Fraction& Fraction::operator*=(const Fraction& rhs) // f *= f
{
	*this = Fraction{ num * rhs.num, den * rhs.den };
	return *this;
}

Fraction& Fraction::operator/=(const Fraction& rhs) // f /= f
{
	*this = Fraction{ num * rhs.den, den * rhs.num };
	return *this;
}


Fraction& Fraction::operator++() // ++f
{
	return *this += 1;
}

Fraction& Fraction::operator--() // --f
{
	return *this -= 1;
}

string Fraction::operator()() const // returns the string version of this fraction
{ 
	string temp{ "(" };

	if (den != 1) // if not an integer
	{
		temp += to_string(num) + "/" + to_string(den);
		
		// improper fraction shows equivalent int + fraction
		if (abs(num) > abs(den)) 
			temp += " = " + to_string(num / den) + " + " +
			to_string(num % den) + "/" + to_string(den);
	}
	else // integer
		temp += to_string(num);
	return temp + ")";
}

Fraction& Fraction::operator*() // make Fraction objects behave like pointers: returns *this
{
	return *this;
}

// [s] returns the numerator if s = "top"; otherwise, returns denominator
long& Fraction::operator[](const string &s)
{
	if (s == "top")
		return num;
	else
		return den;
}

const long& Fraction::operator[](const string &s) const
{
	if (s == "top")
		return num;
	else
		return den;
}

// The following operators are usually overloaded as members
Fraction Fraction::operator+() const // +f
{
	return *this;
}

Fraction Fraction::operator-() const // -f
{
	return *this * (-1);
}

Fraction Fraction::operator++(int) // f++
{
	Fraction temp{ *this };
	*this += 1;
	return temp;
}

Fraction Fraction::operator--(int) // f--
{
	Fraction temp{ *this };
	*this -= 1;
	return temp;
}

void Fraction::normalize()
{
	if (den < 0) {
		num *= -1;
		den *= -1;
	}
}

void Fraction::reduce()
{
	if (den != 1) // skip integers
	{
		long gcd = findGCD(abs(num), den);
		num /= gcd;
		den /= gcd;
	}
}

long Fraction::findGCD(long a, long b)
{
	// recursive version of Euclid's algorithm
	return b == 0 ? a : findGCD(b, a % b);
}

// Non-member operator overloads
Fraction operator+(const Fraction& lhs, const Fraction& rhs) // f + f
{
	return Fraction{ lhs.getNum() * rhs.getDen() + lhs.getDen() * rhs.getNum(),
		lhs.getDen() * rhs.getDen() };
}

Fraction operator+(const Fraction& lhs, const int& val) // f + i
{
	return Fraction{ lhs.getNum() + lhs.getDen() * val, lhs.getDen() };
}

Fraction operator+(const int& val, const Fraction& rhs) // i + f
{
	return Fraction{ val * rhs.getDen() + rhs.getNum(), rhs.getDen() };
}

Fraction operator-(const Fraction& lhs, const Fraction& rhs) // f - f
{
	return Fraction{ lhs.getNum() * rhs.getDen() - lhs.getDen() * rhs.getNum(),
		lhs.getDen() * rhs.getDen() };
}

Fraction operator-(const Fraction& lhs, const int& val) // f - i
{
	return Fraction{ lhs.getNum() - lhs.getDen() * val, lhs.getDen() };
}

Fraction operator-(const int& val, const Fraction& rhs) // i - f
{
	return Fraction{ val * rhs.getDen() - rhs.getNum(), rhs.getDen() };
}

Fraction operator*(const Fraction& lhs, const Fraction& rhs) // f * f
{
	return Fraction{ lhs.getNum() * rhs.getNum(), lhs.getDen() * rhs.getDen() };
}

Fraction operator*(const Fraction& lhs, const int& val) // f * i
{
	return Fraction{ lhs.getNum() * val, lhs.getDen() };
}

Fraction operator*(const int& val, const Fraction& rhs) // i * f
{
	return Fraction{ val * rhs.getNum(), rhs.getDen() };
}

Fraction operator/(const Fraction& lhs, const Fraction& rhs) // f / f
{
	return Fraction{ lhs.getNum() * rhs.getDen(), lhs.getDen() * rhs.getNum() };
}

Fraction operator/(const Fraction& lhs, const int& val) // f / i
{
	return Fraction{ lhs.getNum(), lhs.getDen() * val };
}

Fraction operator/(const int& val, const Fraction& rhs) // i / f
{
	return Fraction{ val * rhs.getDen(), rhs.getNum() };
}

bool operator==(const Fraction& lhs, const Fraction& rhs) // f == f
{
	// a/b = c/d <=> ad = bc
	return lhs.getNum() * rhs.getDen() == lhs.getDen() * rhs.getNum();
}

bool operator==(const Fraction& lhs, const int& val) // f == i
{
	return lhs.getNum() == lhs.getDen() * val;
}

bool operator==(const int& val, const Fraction& rhs) // i == f
{
	return val * rhs.getDen() == rhs.getNum();
}

bool operator!=(const Fraction& lhs, const Fraction& rhs) // f != f
{
	return !(lhs == rhs);
}

bool operator!=(const Fraction& lhs, const int& val) // f != i
{
	return !(lhs == val);
}
bool operator!=(const int& val, const Fraction& rhs) // i != f
{
	return !(val == rhs);
}

bool operator<(const Fraction& lhs, const Fraction& rhs) // f < f
{
	// a/b < c/d <=> ad < bc
	return lhs.getNum() * rhs.getDen() < lhs.getDen() * rhs.getNum();
}
bool operator<(const Fraction& lhs, const int& val) // f < i
{
	return lhs.getNum() < lhs.getDen() * val;
}
bool operator<(const int& val, const Fraction& rhs) // i < f
{
	return val * rhs.getDen() < rhs.getNum();
}

bool operator<=(const Fraction& lhs, const Fraction& rhs) // f <= f
{
	return !(lhs > rhs);
}

bool operator<=(const Fraction& lhs, const int& val) // f <= i
{
	return !(lhs > val);
}

bool operator<=(const int& val, const Fraction& rhs) // i <= f
{
	return !(val > rhs);
}

bool operator>(const Fraction& lhs, const Fraction& rhs) // f < f
{
	// a/b > c/d <=> ad > bc
	return lhs.getNum() * rhs.getDen() > lhs.getDen() * rhs.getNum();
}
bool operator>(const Fraction& lhs, const int& val) // f < i
{
	return lhs.getNum() > lhs.getDen() * val;
}
bool operator>(const int& val, const Fraction& rhs) // i < f
{
	return val * rhs.getDen() > rhs.getNum();
}

bool operator>=(const Fraction& lhs, const Fraction& rhs) // f <= f
{
	return !(lhs < rhs);
}

bool operator>=(const Fraction& lhs, const int& val) // f <= i
{
	return !(lhs < val);
}

bool operator>=(const int& val, const Fraction& rhs) // i <= f
{
	return !(val < rhs);
}

istream& operator >> (istream& istr, Fraction& rhs)
{
	cout << "numerator? ";
	long n;
	istr >> n;
	rhs.setNum(n);
	cout << "\ndenominator? ";
	istr >> n;
	rhs.setDen(n);
	cout << "\n";
	return istr;
}

ostream& operator<<(ostream& ostr, const Fraction& rhs)
{
	ostr << rhs().substr(1, rhs().length() - 2); // removes () from rhs()
	return ostr;
}
