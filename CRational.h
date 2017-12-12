//------------------------------------------------------------------------
// File: CRational.h
// Class: CRational
//------------------------------------------------------------------------
#ifndef CRATIONAL_H
#define CRATIONAL_H
#define FLIP_SIGN -1
#define BUFFER 256
#define TENTH 10

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace Rational
{
//------------------------------------------------------------------------
// Title: Rational Number Class
// Description: this file contains the class prototypes and inline
//				functions for CRational class
// Programmer:	Tabitha Roemish
// Date:	2/24/2017
// Version: v1
// Environment: PC
//				Software: Windows 10
//				Compiles under Microsoft Visual Studio 2015
//
// Class CRational:
//	Properties:
//		m_numerator - numerator of Rational Number
//		m_denominator - denominator of Rational Number
//
//	Methods:
//		inline:
//			CRational(long n = 0, long d = 1) 
//			Constructor
//			initializes m_numerator and m_denominator
//			Parameters:
//				long m_numerator
//				long m_denominator
//		
//			CRational(int n)
//			constructor for one int to long conversion
//			initializes RationalNumber, m_numerator
//			Parameters:
//				int n - numerator 
//
//			long getNumerator() const 
//			Returns: m_numerator
//
//			long getDenominator() const 
//			Returns: m_denominator
//
//			long getLCD(const CRational & rationalNumber)
//			Returns: lowest common denominator as long
//			Parameters: CRational& - second rational number to compare
//
//			CRational::operator bool() const
//			Returns: true if not 0/1
//			
//			operator string() const
//			returns rational as string
//
//			operator double() const 
//			returns rational number as double
//
//			CRational operator*=(const CRational & rationalNumber)
//			Parameters:
//					const CRational & rationalNumber
//					const reference to the multiplier	
//				Returns: a CRational with the value of *this
//					after multiplication
//
//			CRational operator/=(const CRational & rationalNumber)
//				Parameters:
//					const CRational & rationalNumber
//					a const reference to the divisor
//				Returns: a CRational with the value of *this
//					after division
//
//			CRational operator+=(const CRational & rationalNumber)
//				Parameters:
//					const CRational & rationalNumber
//					a const reference to the addend	
//				Returns: a CRational with the value of *this
//					 after addition
//			CRational operator-=(const CRational & rationalNumber)
//				Parameters:
//					const CRational & rationalNumber
//					a const reference to the subtrahend	
//				Returns: a CRational with the value of *this
//					after subtraction
//
//		non-inline:
/*			CRational(double x);
			CRational(const CRational & rationalNumber);
			static long GCF(long, long);

			void print() const;
			void print(ostream& sout) const;

			CRational invert();
			CRational toThePower(long);
			long compareTo(const CRational & rationalNumber) const;

			CRational operator= (const CRational & rationalNumber);

			CRational operator* (const CRational & rationalNumber);
			CRational operator/ (const CRational & rationalNumber);
			CRational operator+ (const CRational & rationalNumber);
			CRational operator- (const CRational & rationalNumber);
			CRational operator-();

			
			CRational operator++();
			CRational operator--();

			bool operator==(const CRational & rationalNumber);
			bool operator!=(const CRational & rationalNumber);
			bool operator<(const CRational & rationalNumber);
			bool operator<=(const CRational & rationalNumber);
			bool operator>(const CRational & rationalNumber);
			bool operator>=(const CRational & rationalNumber);
	
			bool operator!();
			CRational operator~();

			operator double() const;
			operator string() const;
// History Log:
//		2/24/2017 TR completed v1
*///--------------------------------------------------------------------

	class CRational
	{
	public:
		CRational(long n = 0, long d = 1) : m_numerator(n), m_denominator(d) 
			{ setProperForm(); };
		CRational(const CRational & rationalNumber);
		CRational(int n) { m_numerator = n; m_denominator = 1; };
		CRational(double x);

		long getNumerator() const {return m_numerator;};
		long getDenominator() const {return m_denominator;};
		long getLCD(const CRational & rationalNumber) 
			{ return LCD(rationalNumber); };
		static long GCF(long, long);
		

		void print() const;
		void print(ostream& sout) const;

		CRational invert();
		CRational toThePower(long);
		long compareTo(const CRational & rationalNumber) const;

		CRational operator= (const CRational & rationalNumber);

		CRational operator* (const CRational & rationalNumber);
		CRational operator/ (const CRational & rationalNumber);
		CRational operator+ (const CRational & rationalNumber);
		CRational operator- (const CRational & rationalNumber);
		CRational operator-();

		CRational operator*=(const CRational & rationalNumber)
			{return *this = *this * rationalNumber;};
		CRational operator/=(const CRational & rationalNumber)
			{return *this = *this / rationalNumber;};
		CRational operator+=(const CRational & rationalNumber)
			{return *this = *this + rationalNumber;};
		CRational operator-=(const CRational & rationalNumber)
			{return *this = *this - rationalNumber;};
		
		CRational operator++();
		CRational operator--();
		CRational operator++(int);
		CRational operator--(int);

		bool operator==(const CRational & rationalNumber);
		bool operator!=(const CRational & rationalNumber);
		bool operator<(const CRational & rationalNumber);
		bool operator<=(const CRational & rationalNumber);
		bool operator>(const CRational & rationalNumber);
		bool operator>=(const CRational & rationalNumber);

		bool operator!();
		CRational operator~() const;

		operator bool() const { return m_numerator != 0; };
		operator double() const { return static_cast<double>(m_numerator) / 
			static_cast<double>(m_denominator); };
		operator string() const {ostringstream os; print(os); return os.str(); };

	private:
		long m_numerator;
		long m_denominator;
		void setProperForm();
		long LCD(const CRational & rationalNumber);
	};

	ostream& operator<< (ostream& sout, const CRational & rationalNumber);
	istream& operator>> (istream& sin, CRational & rationalNumber);

	
}
#endif