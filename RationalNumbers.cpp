//--------------------------------------------
// File: RationalNumbers.cpp
// Function: main()
//--------------------------------------------
#include <iostream>
#include "CRational.h"
using namespace std;
template <class T>
void safeRead(istream& sin, T& number,
	const char* reprompt = "Invalid input--Enter a number: ");
//-----------------------------------------------------------------------------
//
//	Function:	main()
//
//	Title:		Using Rational Numbers
//
//	Description:	This file contains function main()
//						which tests rational numbers
//
//	Programmer:	Tabitha Roemish
//   
//	Date:		2/24/2017
// 
//	Version:	1.0
//  
//	Environment:	PC 
//				Software:   MS Windows 10
//				Compiles under Microsoft Visual Studion 2015
// 
//	Input:		a rational number from the console
// 
//	Output:		Screen display of rational numbers
// 
//	Calls:		CRational class and related functions
// 
//	Called By:	n/a
// 
//	Parameters:	None
// 
//	Returns:	EXIT_SUCCESS  = successful 
//
//	History Log:
//			2/24/2017  TR  completed version 1.0
//-----------------------------------------------------------------------------
int main()
{
	using namespace Rational;
	char again = 'Y';
	try
	{
		while (again != 'Q' && again != 'q')
		{
			//ask for two fractions
			CRational a;
			CRational b;
			cout << "Please enter two rational numbers";
			cout << "<please note that after entering a double, ";
			cout << "you will need to press <enter> twice>" << endl;
			cout << "First Number: " << endl;
			safeRead(cin, a);
			cout << "Second Number: " << endl;
			safeRead(cin, b);
			
			cout << "These are your rational numbers:";
			cout << "a: " << a;
			cout << "b: " << b;

			//print out basic arithmetic methods
			cout << "Greatest common factor for : " << a.getDenominator()
				<< " and " << b.getDenominator() << ": " <<
				CRational::GCF(a.getDenominator(), b.getDenominator()) << endl;
			cout << "Lowest common denominator: " << a.getLCD(b) << endl;
			cout << "a + b: " << a + b;
			cout << "a - b: " << a - b;
			cout << "a * b: " << a * b;
			cout << "a / b: " << a / b;
			cout << "a ^ 3: " << a.toThePower(3);
			
			//print out combination arithemtic methods
			CRational answer = a;
			cout << "-a: " << -answer;
			answer += b;
			cout << "a += b: " << answer;
			answer = a;
			answer -= b;
			cout << "a -= b: " << answer;
			answer = a;
			answer *= b;
			cout << "a *= b: " << answer;
			answer = a;
			answer /= b;
			cout << "a /= b: " << answer;
			
			//print out iterators
			cout << "a++: " << a++;
			cout << "++a: " << ++a;
			cout << "a--: " << a--;
			cout << "--a: " << --a;
			cout << "~a: " << ~a;
			
			//print out boolean comparisons
			string boolanswer = (!a != 0) ? "TRUE" : "FALSE";
			cout << "!a (will print true if numerator = 0): " 
				<< boolanswer << endl;
			boolanswer = (a == b) ? "TRUE" : "FALSE";
			cout << "a == b? " << boolanswer << endl;
			boolanswer = (a != b) ? "TRUE" : "FALSE";
			cout << "a != b? " << boolanswer << endl;
			boolanswer = (a < b) ? "TRUE" : "FALSE";
			cout << "a < b? " << boolanswer << endl;
			boolanswer = (a >= b) ? "TRUE" : "FALSE";
			cout << "a >= b? " << boolanswer << endl;
			boolanswer = (a <= b) ? "TRUE" : "FALSE";
			cout << "a <= b? " << boolanswer << endl;
			
			//print out static cast overloads
			cout << "static_cast<bool>(a): " << static_cast<bool>(a) << endl;
			cout << "static_cast<double>(a): " << static_cast<double>(a) 
				<< endl;
			cout << "static_cast<string>(a): " << static_cast<string>(a) 
				<< endl;

			//print out other contructors
			cout << endl << "Here are some constructors in action:" << endl;
			CRational sample;
			cout << "Default CRational: " << sample;
			CRational sample2(5L);
			cout << "CRational with one long (5L): " << sample2;
			CRational sample3(3);
			cout << "CRational with one int (3): " << sample3;
			CRational sample4(382, 52356);
			cout << "CRational with two longs (382/52356): " 
				<< sample4 << endl;

			//ask user to enter again.
			cout << "Would you like to enter two new fractions?" 
				<< "press <enter> to contine, or ""Q"" to quit" << endl;
			again = cin.get();
		}
	}
	catch (exception ex)
	{
		cerr << endl << "exception: " << ex.what() << endl;
		cout << endl << "Press \"Enter\" to continue..." << endl;
		cin.get();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
//	Function:	safeRead()
//
//	Title:		safely reads in number data
// 
//	Description:	template funtion to safely read in a number from sin.
//				Re-prompts and re-enters if input is invalid
//
//	Programmer:	Paul Bladek
//
//	Date:		2/8/12
//
//	Version:	1.02
//
//	Environment:	PC 
//				Software:   MS Windows 7
//				Compiles under Microsoft Visual C++.Net 2012
//
//	Input:		a number from the console 
//	Output:		reprompt to console on invalid input
//	Calls:		n/a
//	Called By:	main()
//	Parameters:	char* reprompt -- the prompt upon invalid input
//				defaults to "Invalid input--Enter a number: "
//	Returns:	void 
//	History Log:
//			6/10/06  PB  completed version 1.01
//			2/8/12   PB  completed version 1.02
//-----------------------------------------------------------------------------
template <class T>
void safeRead(istream& sin, T& number, const char* reprompt)
{
	while (!(sin >> number))
	{
		sin.clear();
		sin.ignore(FILENAME_MAX, '\n');
		cout << reprompt;
	}
	sin.ignore(FILENAME_MAX, '\n');
}

