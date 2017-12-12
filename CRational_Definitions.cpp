// File: CRational_Definitions.cpp
// Functions:
/*	void CRational::setProperForm()
	CRational::CRational(const CRational & rationalNumber)
	CRational(double x);
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

	non-class related function:
	void safeRead(istream& sin, T& number,
	const char* reprompt = "Invalid input--Enter a number: ");
*/

#include "CRational.h"
#include <cmath>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;



namespace Rational
{
	
	/*---------------------------------------------------------------
		Class: CRational
		Title: CRational Class Definitions
		Description: Defintions for CRational Class Methods and
			related functions
		Programmer: Tabitha Roemish
		Date: 2/24/2017
		Version: v1
		Environment: PC
					Software: Windows 10
					Compiles under Microsoft visual Studio 2015
		Class: CRational
		History Log:
			2/24/2017 TR completed v1
	*///-------------------------------------------------------------
	/*---------------------------------------------------------------
	Class:         CRational
	method:        void CRational::setProperForm()
	description:   throws error for zero denominator, adjusts signs
					for denminator and numerator and reduces fraction
	Input:         None
	Output:        none
	Calls:         GCF()
	Called By:     CRational(long,long) constructor
	Parameters:    none
	Returns:       n/a 
	History Log:
               2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	void CRational::setProperForm()
	{
		if (m_denominator == 0)
			throw invalid_argument("Zero Denominator");
		else
		{
			if (m_denominator < 0)
			{
				m_denominator = abs(m_denominator);
				m_numerator = FLIP_SIGN * m_numerator;
			}

			long common = 0;

			common = GCF(m_numerator, m_denominator);
			m_denominator = m_denominator / common;
			m_numerator = m_numerator / common;
		}
	}
	/*---------------------------------------------------------------
	Class:         CRational
	method:        CRational::CRational(const CRational & rationalNumber)
	description:   copy constructor
	Input:         none
	Output:        none
	Calls:         none
	Called By:     assignment implicitly
	Parameters:    CRational&
	Returns:       n/a
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational::CRational(const CRational & rationalNumber)
	{
		m_numerator = rationalNumber.m_numerator;
		m_denominator = rationalNumber.m_denominator;
	}
	/*---------------------------------------------------------------
	Class:         CRational
	method:        long CRational::LCD(const CRational & rationalNumber)
	description:   finds lowest common denominator
	Input:         none
	Output:        none
	Calls:         none
	Called By:     operator+
	Parameters:    CRational&
	Returns:       long
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	long CRational::LCD(const CRational & rationalNumber)
	{
		long cd = 0;

		if (m_denominator == 0 || rationalNumber.m_denominator == 0)
			return cd;
		else
			return ((m_denominator / GCF(m_denominator, 
				rationalNumber.m_denominator)) 
				* rationalNumber.m_denominator);
	}
	/*---------------------------------------------------------------
	Class:         CRational
	method:        CRational::CRational(double x)
	description:   constructs ratonal number from double
	Input:         none
	Output:        none
	Calls:         setProperForm()
	Called By:     n/a
	Parameters:    double x - double to be converted to rational
	Returns:       n/a
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational::CRational(double x)
	{
		long intPart = static_cast<long>(x);
		double decPart = intPart - x;
		long decPartConverted = 0;
		int count = 0;
		long powerOfTen = 0;

		string str = "";
		stringstream convertDec;

		convertDec << decPart;
		str = convertDec.str();
		str.erase(str.begin(), str.begin() + 3);
		count = str.length();
		powerOfTen = pow(TENTH, count);

		istringstream convertStr(str);
		convertStr >> decPartConverted;
		
		m_numerator = powerOfTen * intPart + decPartConverted;
		m_denominator = powerOfTen;
		
		setProperForm();
		
	}

	/*---------------------------------------------------------------
	Class:         CRational
	method:        long CRational::GCF(long n1, long n2)
	description:   finds the greates common factor for two rationals
	Input:			none 
	Output:        none
	Calls:         GCF() - (recursive)
	Called By:     setProperForm()
					operator*
					LCD()
	Parameters:    2 longs - numbers to be compared
	Returns:       long - greatest common factor of two numbers
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	long CRational::GCF(long n1, long n2)
	{
		long remainder;
		remainder = abs(n1) % abs(n2);
		if (remainder != 0)
			GCF(n2, remainder); 
		else
			return n2;
	}

	/*---------------------------------------------------------------
	Class:			CRational
	method:			void CRational::print() const
	description:	calls print of CRational with cout
	Input:			none
	Output:			none
	Calls:			print()
	Called By:		main()
	Parameters:		none
	Returns:		none
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	void CRational::print() const
	{
		print(cout);
	}

	/*---------------------------------------------------------------
	Class:			CRational
	method:			void CRational::print(ostream& sout) const
	description:	prints CRational
	Input:			none
	Output:			outputs to requested ostream
	Calls:			none
	Called By:		print()
					operator<<
	Parameters:		ostream
	Returns:		void
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	void CRational::print(ostream& sout) const
	{
		if (m_denominator == 1)
			sout << m_numerator << endl;
		else
			sout << m_numerator << "/" << m_denominator << endl;
	}

	/*---------------------------------------------------------------
	Class:			CRational
	method:			CRational CRational::invert()
	description:	flips the rational so that numerator becomes
					the denominator and the denominator is the numerator
	Input:			none	
	Output:			none
	Calls:			none
	Called By:		operator/
					main()
	Parameters:		none
	Returns:		CRational
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational CRational::invert()
	{
		long temp;
		temp = m_numerator;
		
		if (temp == 0)
			throw invalid_argument("zero denominator");
		else
		{
			m_numerator = m_denominator;
			m_denominator = temp;
		}
		return *this;
	}

	/*---------------------------------------------------------------
	Class:			CRational
	method:			CRational CRational::toThePower(long power)
	description:	raises rational number to power
	Input:			none
	Output:			none
	Calls:			Constructor
	Called By:		main()
	Parameters:		power, long - exponent
	Returns:		CRational
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational CRational::toThePower(long power)
	{
		long numerator = 1;
		long denominator = 1;

		if (m_numerator == 0)
			throw invalid_argument("Zero to the zero power");
		else
		{
			while (power > 0)
			{
				numerator *= m_numerator;
				denominator *= m_denominator;
				power--;
			}
		}
		return CRational(numerator, denominator);
	}
	/*---------------------------------------------------------------
	Class:         CRational
	method:	long CRational::compareTo(const CRational & rationalNumber) const
	description: compares two rationals, returns less than 0
			if the first < the second, a 0 if the two are equal, and
			greater than 0 if first > second
	Input:	none
	Output:	none
	Calls:	none	
	Called By: main()
	Parameters: CRational&
	Returns: long
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	long CRational::compareTo(const CRational & rationalNumber) const
	{
		return ((m_numerator * rationalNumber.m_denominator) - 
					(rationalNumber.m_numerator * m_denominator));
	}

	/*---------------------------------------------------------------
	Class:  CRational
	method:	CRational CRational::operator= (const CRational & rationalNumber)
	description: assigns one rational to another
	Input:	none
	Output:	none
	Calls:	none
	Called By:	main()
				operator/
	Parameters: CRational &
	Returns: CRational
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational CRational::operator= (const CRational & rationalNumber)
	{
		if (this != &rationalNumber)
		{
			m_numerator = rationalNumber.m_numerator;
			m_denominator = rationalNumber.m_denominator;
		}
		return *this;
	}

	/*---------------------------------------------------------------
	Class:  CRational
	method:	CRational CRational::operator* (const CRational & rationalNumber)
	description: multiplies one rational number by another and returns new
				rational number
	Input:	none
	Output:	none
	Calls:	GCF()
	Called By: main()
				operator/
	Parameters:	CRational&
	Returns:	CRational
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational CRational::operator* (const CRational & rationalNumber) 
	{
		long common1 = GCF(m_numerator,rationalNumber.m_denominator);
		long common2 = GCF(rationalNumber.m_numerator, m_denominator);
		return CRational((m_numerator / common1)*
			(rationalNumber.m_numerator / common2), (m_denominator / common2)
			*(rationalNumber.m_denominator / common1));
	}

	/*---------------------------------------------------------------
	Class:  CRational
	method:	CRational CRational::operator/ (const CRational & rationalNumber)
	description:	divides one rational number by another and returns 
					a new rational
	Input:	none
	Output:	none
	Calls:	operator*
	Called By:	main()
	Parameters: CRational&
	Returns:	CRational
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational CRational::operator/ (const CRational & rationalNumber)
	{
		CRational temp = rationalNumber;
		if (rationalNumber.m_numerator == 0)
			throw invalid_argument("Zero denominator");
		else
			temp = *this * temp.invert();
		return temp;
	}

	/*---------------------------------------------------------------
	Class:  CRational
	method:	CRational CRational::operator+ (const CRational & rationalNumber)
	description: adds one rational number to another and returns a new
				rational number
	Input:	none
	Output:	none
	Calls:	LCD()
	Called By: main()
	Parameters:	CRational&
	Returns:	CRational
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational CRational::operator+ (const CRational & rationalNumber)
	{
		long lcd = LCD(rationalNumber);
		return CRational(((lcd / m_denominator) * m_numerator) + 
			((lcd / rationalNumber.m_denominator) * 
				rationalNumber.m_numerator),lcd);
	}

	/*---------------------------------------------------------------
	Class:  CRational
	method:	CRational CRational::operator- (const CRational & rationalNumber)
	description:	subtracts one rational number from another returning a 
					new rational number
	Input:	none
	Output:	none
	Calls:	LCD
	Called By:	main()
	Parameters:	CRational&
	Returns:	CRational
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational CRational::operator- (const CRational & rationalNumber)
	{
		long lcd = LCD(rationalNumber);
		return CRational(((lcd / m_denominator) * m_numerator) -
			((lcd / rationalNumber.m_denominator)
				* rationalNumber.m_numerator), lcd);
	}

	/*---------------------------------------------------------------
	Class:  CRational
	method:	ostream& operator << (ostream& sout, const CRational & rationalNumber)
	description: outputs rational number in fraction form a/b
	Input:	none
	Output:	rational number to ostream
	Calls:	print()
	Called By: main()
	Parameters: ostream& and CRational&
	Returns:	ostream
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	ostream& operator << (ostream& sout, const CRational & rationalNumber)
	{
		rationalNumber.print(sout);
		return sout;
	}

	/*---------------------------------------------------------------
	Class: CRational
	method:istream& operator>> 
			(istream& sin, const CRational & rationalNumber)
	description: inputs rational number
	Input:	number in this format a/b
	Output: none
	Calls:
	Called By:
	Parameters: istream&, CRational&
	Returns:
	History Log:
	2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	istream& operator>> (istream& sin, CRational & rationalNumber)
	{
		long long1input = 0;
		long long2input = 0;
		char charInput = ' ';
		char charCheck = ' ';
		double doubleinput;
		double remainingDouble;
		string remaining = "";
		bool isDouble = false;
		
		
		if (!(sin >> long1input))
			return sin;

		while ((isspace(charInput = sin.peek()) && charInput != '\n') || charInput == '/')
			sin.get();
	
		if (!(cin >> long2input))
		{
			if (charInput == '.')
				isDouble = true;
			cin.clear();
			cin.ignore();
		}
		else
			rationalNumber = CRational(long1input, long2input);
		
		if(isDouble)
		{ 
			while ((charInput =sin.get()) != '\n')
			{
				remaining += charInput;
			}
			remaining =  "0." + remaining;
			istringstream stringToDouble(remaining);
			stringToDouble >> remainingDouble;
			doubleinput = long1input + remainingDouble;
			rationalNumber = CRational(doubleinput);
		}
		else
			if(long2input = 0)
				rationalNumber = CRational(static_cast<int>(long1input));
			
		return sin;
	}
	/*---------------------------------------------------------------
	Class:      CRational
	method:		CRational CRational::operator-()
	description: changes the sign of the rational number
	Input:		none
	Output:		none
	Calls:		none
	Called By:	main()
	Parameters:	none
	Returns:	CRational
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational CRational::operator-()
	{
		m_numerator *= FLIP_SIGN;
		return *this;
	}

	/*---------------------------------------------------------------
	Class:      CRational
	method:		CRational CRational::operator++()
	description: Pre increments CRational
	Input:		none
	Output:		none
	Calls:		constructor, operator+=
	Called By:	main()
	Parameters: none
	Returns:	CRational: after incementing
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational CRational::operator++()
	{
		return *this+= CRational(1, 1);
	}

	/*---------------------------------------------------------------
	Class:      CRational
	method:		CRational  CRational::operator--()
	description: pre decrements a CRational
	Input:		none
	Output:		none
	Calls:		constructor, operator-=
	Called By:	main()
	Parameters:	none
	Returns:	CRational: after decrementing
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational  CRational::operator--()
	{
		return *this -= CRational(1, 1);
	}

	/*---------------------------------------------------------------
	Class:      CRational
	method:		CRational CRational::operator++(int)
	description: post increments CRational
	Input:		none
	Output:		none
	Calls:		constructor, operator+=
	Called By:	main()
	Parameters:	an unused integer
	Returns:	CRational: as it is before incrementing
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational CRational::operator++(int)
	{
		CRational temp = *this;
		*this += CRational(1, 1);
		return temp;
	}

	/*---------------------------------------------------------------
	Class:		CRational
	method:		CRational CRational::operator--(int)
	description: post decrements CRational
	Input:		none
	Output:		none
	Calls:		constructor, operator-=
	Called By:	main()
	Parameters:	an unused integer
	Returns:	CRational: as it is before decrementing
	History Log:
	2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational CRational::operator--(int)
	{
		CRational temp = *this;
		*this -= CRational(1, 1);
		return temp;
	}

	/*---------------------------------------------------------------
	Class:  CRational
	method:	bool CRational::operator==(const CRational & rationalNumber)
	description: returns true if two CRationals are equal
	Input:	none
	Output:	none
	Calls:	compareTo()
	Called By:	main()
	Parameters:	CRational
	Returns: bool: true for equal
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	bool CRational::operator==(const CRational & rationalNumber)
	{
		if (compareTo(rationalNumber) == 0)
			return true;
		else
			return false;
	}
	/*---------------------------------------------------------------
	Class:  CRational
	method:	bool CRational::operator!=(const CRational & rationalNumber)
	description: returns true if CRationals are not equal
	Input:	none
	Output:	none	
	Calls:	compareTo()
	Called By: main()
	Parameters:	CRational&
	Returns:	bool: true if not equal
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	bool CRational::operator!=(const CRational & rationalNumber)
	{
		if (compareTo(rationalNumber) !=0)
			return true;
		else
			return false;
	}
	/*---------------------------------------------------------------
	Class:      CRational
	method:		bool CRational::operator<(const CRational & rationalNumber)
	description:	returns true if CRational is less than rationalNumber
	Input:		none
	Output:		none
	Calls:		compareTo()
	Called By:	main()
	Parameters: CRational&: fraction being compared to *this
	Returns:	bool: True if *this is less than rationalNumber
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	bool CRational::operator<(const CRational & rationalNumber)
	{
		if (compareTo(rationalNumber) < 0)
			return true;
		else
			return false;
	}
	/*---------------------------------------------------------------
	Class:  CRational
	method:	bool CRational::operator<=(const CRational & rationalNumber)
	description: compares two rationals, returns true if *this is less than
				or equal to rationalNumber
	Input:	none
	Output:	none
	Calls:	compareTo()
	Called By: main()
	Parameters: CRational&- comparison rational
	Returns:	bool: true if *this is less than or equal to rationalNumber
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	bool CRational::operator<=(const CRational & rationalNumber)
	{
		if (compareTo(rationalNumber) <= 0)
			return true;
		else
			return false;
	}
	/*---------------------------------------------------------------
	Class:  CRational
	method:	bool CRational::operator>(const CRational & rationalNumber)
	description: compares two CRationals and returns true 
					if CRational > rationalNumber
	Input:	none
	Output:	none
	Calls:	compareTo()
	Called By: main()
	Parameters:	CRational&: Rational being compared
	Returns:	bool: true if *this > rationalNumber
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	bool CRational::operator>(const CRational & rationalNumber)
	{
		if (compareTo(rationalNumber) > 0)
			return true;
		else
			return false;
	}
	/*---------------------------------------------------------------
	Class:  CRational
	method:	bool CRational::operator>=(const CRational & rationalNumber)
	description:	compares two rational numbers and returns true if 
					*this is >= rationalNumber
	Input:	none	
	Output:	none	
	Calls:	compareTo()
	Called By:	main()
	Parameters:	CRational& - rational being compared
	Returns: bool: true if *this is >= rationalNumber
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	bool CRational::operator>=(const CRational & rationalNumber)
	{
		if (compareTo(rationalNumber) >= 0)
			return true;
		else
			return false;
	}
	/*---------------------------------------------------------------
	Class:			CRational
	method:			bool CRational::operator!()
	description:	returns true if numerator is 0
	Input:			none
	Output:			none
	Calls:			none
	Called By:		main()
	Parameters:		none
	Returns:		bool, true if numerator is 0
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	bool CRational::operator!()
	{
		if (m_numerator == 0)
			return true;
		else
			return false;
	}
	/*---------------------------------------------------------------
	Class:      CRational
	method:		CRational CRational::operator~() const
	description: returns the inverse of a rational number
	Input:		none
	Output:		none
	Calls:		invert()
	Called By:	main()
	Parameters:	none
	Returns:	CRational
	History Log:
		2/24/2017 TR completed v1
	//---------------------------------------------------------------*/
	CRational CRational::operator~() const
	{
		CRational temp = *this;
		temp.invert();
		return temp;
	}
	
}


