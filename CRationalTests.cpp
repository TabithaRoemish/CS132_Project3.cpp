#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Assignment3\CRational.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Rational;

namespace CRationalUnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(AccessorCheck)
		{
			//checks that the accessors return the correct values
			CRational test(3, 5);
			long expectedNumerator = 3;
			long actualNumerator = test.getNumerator();
			long expectedDenom = 5;
			long actualDenom = test.getDenominator();
			Assert::AreEqual(expectedNumerator, actualNumerator);
			Assert::AreEqual(expectedDenom, actualDenom);
		}

		TEST_METHOD(ConstructorCheck)
		{
			//checks that constructor adjusts negative numbers
			// reduces rational numbers and throws error for zero denom
			CRational actualTwoNegatives(-3, -4);
			CRational actualNegDenom(3, -4);
			CRational actualNonReduced(4, 16);

			CRational expectedTwoNegatives(3, 4);
			CRational expectedNegDenom(-3, 4);
			CRational expectedNonReduced(1, 4);
			bool exceptionThrown = false;
			try
			{
				CRational zeroDenom(1, 0);
			}
			catch(const invalid_argument& e)
			{
				exceptionThrown = true;
			}

			Assert::AreEqual(expectedTwoNegatives.getNumerator(), actualTwoNegatives.getNumerator());
			Assert::AreEqual(expectedTwoNegatives.getDenominator(), 
				actualTwoNegatives.getDenominator()); 
			Assert::AreEqual(expectedNegDenom.getNumerator(), actualNegDenom.getNumerator());
			Assert::AreEqual(expectedNegDenom.getDenominator(), actualNegDenom.getDenominator());
			Assert::AreEqual(expectedNonReduced.getNumerator(), actualNonReduced.getNumerator());
			Assert::AreEqual(expectedNonReduced.getDenominator(), actualNonReduced.getDenominator());
			
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(ConstructorDoubleCheck)
		{ //checks that entring a doule is converted to fraction
			CRational test(5.307);
			CRational expected(5307,1000);
			long actualNumerator = test.getNumerator();
			long actualDenominator = test.getDenominator();

			Assert::AreEqual(expected.getNumerator(), actualNumerator);
			Assert::AreEqual(expected.getDenominator(), actualDenominator);
		}

		TEST_METHOD(invertCheck)
		{
			//checks that invert function switches numerator and nominator
			CRational test(3, 4);
			CRational expected(4, 3);
			CRational actual;
			actual = test.invert();
			Assert::AreEqual(expected.getNumerator(), actual.getNumerator());
			Assert::AreEqual(expected.getDenominator(), actual.getDenominator());
		}

		TEST_METHOD(invertErrorCheck)
		{
			//checks that invert function throws error for rational with 0 denom. 
			CRational test;
			CRational actual;
			bool errorThrown = false;
			try
			{
				actual = test.invert();
			}
			catch (const invalid_argument& e)
			{
				errorThrown = true;
			}
			Assert::IsTrue(errorThrown);
		}

		TEST_METHOD(toThePowerCheck)
		{
			//checks that toThePower raises the rational number to the requested power
			//also checks that raising rational number to zero power throws error. 
			CRational test(3, 4);
			CRational actual;
			CRational errorCheck;
			CRational zeroNumerator;
			long expectedNum = 27;
			long expectedDen = 64;
			bool errorThrown = false;

			actual = test.toThePower(3);
			
			try
			{
				errorCheck = zeroNumerator.toThePower(0);
			}
			catch (const invalid_argument& e)
			{
				errorThrown = true;
			}
			
			Assert::AreEqual(expectedNum, actual.getNumerator());
			Assert::AreEqual(expectedDen, actual.getDenominator());
			Assert::IsTrue(errorThrown);
		}
			 
		TEST_METHOD(AssignmentCheck)
		{
			//checks that assigning one rational number to another
			// results in both rational numbers being equal.
			CRational test(5, 9);
			CRational test2(3, 7);
			test = test2;
			Assert::AreEqual(test.getNumerator(), test2.getNumerator());
			Assert::AreEqual(test.getDenominator(), test2.getDenominator());
		}

		TEST_METHOD(MultiplicationCheck)
		{
			//checks that rational numbers are correctly multiplied
			CRational test(1, 3);
			CRational test2(8, 9);
			CRational actual;
			actual = test * test2;
			long expectedNumerator 
				= test.getNumerator() * test2.getNumerator();
			long expectedDenominator 
				= test.getDenominator() * test2.getDenominator();
			Assert::AreEqual(expectedNumerator, actual.getNumerator());
			Assert::AreEqual(expectedDenominator, actual.getDenominator());
		}
		
		TEST_METHOD(MultiplicationCheck_limits)
		{ 
			//checks that numbers are reduced before constructing
			//otherwise constructor would get 21,474,836,460 which is over
			//long limit of 2,147,483,647
			//additional confirms GCF function works correctly
			CRational test(2147483646, 5);
			CRational test2(10, 9);
			CRational actual;
			actual = test * test2; // 2147483646 * 10 / 5 * 9 = 238609294 * 2 / 1
			long gcf1 = CRational::GCF(test.getNumerator(), test2.getDenominator());
			long gcf2 = CRational::GCF(test.getDenominator(), test2.getNumerator()); 
			// (test.numerator) 2147483646 / (GCF) 9
			long expectedNumerator = 238609294 * 2; 
			// test.denominator) 5 / (GCF) 5
			long expectedDenominator = 1; 
			
			Assert::AreEqual(9L, gcf1);
			Assert::AreEqual(5L, gcf2);
			Assert::AreEqual(expectedNumerator, actual.getNumerator());
			Assert::AreEqual(expectedDenominator, actual.getDenominator());
		}

		TEST_METHOD(DivisionCheck)
		{
			// checks that dividing two fractions
			//returns the correct fraction
			CRational test(1, 3);
			CRational test2(8, 9);
			CRational actual;
			CRational expected(3, 8); // 1/3 / 8/9
			actual = test / test2;
			Assert::AreEqual(expected.getNumerator(), actual.getNumerator());
			Assert::AreEqual(expected.getDenominator(), actual.getDenominator());
		}

		TEST_METHOD(DivisionErrorCheck)
		{
			//checks that error is thrown for zero division
			CRational test(1, 2);
			CRational test2;
			CRational actual;
			bool errorThrown = false;
			try
			{
				actual = test / test2;
			}
			catch(const invalid_argument& e)
			{
				errorThrown = true;
			}
			Assert::IsTrue(errorThrown);
		}

		TEST_METHOD(AdditionCheck)
		{
			//checks that adding two rational numbers returns the correct amount
			CRational test(3, 4);
			CRational test2(1, 2);
			CRational actual;
			CRational expected(5,4); // 3/4 + 1/2
			actual = test + test2;
			Assert::AreEqual(actual.getNumerator(), expected.getNumerator());
			Assert::AreEqual(actual.getDenominator(), expected.getDenominator());
		}

		TEST_METHOD(SubtractionCheck)
		{
			// check that subtracting two rational numbers 
			//returns the correct fraction
			CRational test(5, 8);
			CRational test2(1, 3);
			CRational expected(7, 24);
			CRational actual;

			actual = test - test2;

			Assert::AreEqual(expected.getNumerator(), actual.getNumerator());
			Assert::AreEqual(expected.getDenominator(), actual.getDenominator());

		}

		TEST_METHOD(unaryMinusCheck)
		{
			CRational test(5, 8);
			CRational expected(-5, 8);
			CRational actual;
			actual = -test;
			Assert::AreEqual(expected.getNumerator(), actual.getNumerator());
			Assert::AreEqual(expected.getDenominator(), actual.getDenominator());
		}

		TEST_METHOD(notRationalCheck)
		{
			//checks operator! returns true for zero numerator
			CRational test;
			bool actual = !test;
			Assert::IsTrue(actual);
		}

		TEST_METHOD(compareToCheck)
		{
			// checks compareTo function returns less than zero for 
			// firstRational<secondRational, 0 if they are equal
			// and greater than 0 if firstRational>secondRational
			CRational first(1, 2);
			CRational second(3, 4);
			CRational third(1, 2);

			long actualGreater;
			long actualLess;
			long actualEqual;

			bool greater = false;
			bool less = false;
			bool equal = false;

			actualGreater = second.compareTo(third);
			if (actualGreater > 0)
				greater = true;
			
			actualLess = first.compareTo(second);
			if (actualLess < 0)
				less = true;

			actualEqual = first.compareTo(third);
			if (actualEqual == 0)
				equal = true;

			Assert::IsTrue(greater);
			Assert::IsTrue(less);
			Assert::IsTrue(equal);
			
		}

		TEST_METHOD(PlusEqualsCheck)
		{
			//checks that += operator add new rational to itself 
			//and returns addition
			CRational a(1, 3);
			CRational b(5, 8);
		
			CRational expectedA(23, 24);
			CRational actualA = a;
			actualA += b;

			Assert::AreEqual(expectedA.getNumerator(), actualA.getNumerator());
			Assert::AreEqual(expectedA.getDenominator(), actualA.getDenominator());
		}

		TEST_METHOD(MinusEqualsCheck)
		{
			//checks that -= subtract a CRational from itself and returns the
			//subtraction
			CRational a(1, 3);
			CRational b(5, 8);

			CRational expectedA(-7, 24);
			CRational actualA = a;
			actualA -= b;

			Assert::AreEqual(expectedA.getNumerator(), actualA.getNumerator());
			Assert::AreEqual(expectedA.getDenominator(), actualA.getDenominator());
		}

		TEST_METHOD(timesEqualsCheck)
		{
			//checks that *= multiplies a CRational by itself and another CRational
			//and returns the product. 
			CRational a(1, 3);
			CRational b(5, 8);

			CRational expectedA(5, 24);
			CRational actualA = a;
			actualA *= b;

			Assert::AreEqual(expectedA.getNumerator(), actualA.getNumerator());
			Assert::AreEqual(expectedA.getDenominator(), actualA.getDenominator());
		}

		TEST_METHOD(dividEqualsCheck)
		{
			//checks that /= a Crational divides itself by another crational 
			//and returns the division
			CRational a(1, 3);
			CRational b(5, 8);

			CRational expectedA(8, 15);
			CRational actualA = a;
			actualA /= b;

			Assert::AreEqual(expectedA.getNumerator(), actualA.getNumerator());
			Assert::AreEqual(expectedA.getDenominator(), actualA.getDenominator());
		}

		TEST_METHOD(plusPlusPreCheck)
		{
			//checks that ++CRational returns itself +1.
			CRational a(3, 4);
			CRational expected(7, 4);
			CRational actual;

			actual = ++a;

			Assert::AreEqual(expected.getNumerator(), actual.getNumerator());
			Assert::AreEqual(expected.getDenominator(), actual.getDenominator());
		}

		TEST_METHOD(minusMinusPreCheck)
		{
			//Checks that a --CRational returns itself -1.
			CRational a(3, 4);
			CRational expected(-1, 4);
			CRational actual;

			actual = --a;

			Assert::AreEqual(expected.getNumerator(), actual.getNumerator());
			Assert::AreEqual(expected.getDenominator(), actual.getDenominator());
		}

		TEST_METHOD(plusPlusPostCheck)
		{
			//checks that CRational++ returns original CRational but
			//post increments CRational by +1.
			CRational a(3, 4);
			CRational expected = a;
			CRational expectedA;
			CRational actual;

			actual = a++;
			expectedA = a;
			
			Assert::AreEqual(expected.getNumerator(), actual.getNumerator());
			Assert::AreEqual(expected.getDenominator(), actual.getDenominator());
			Assert::AreEqual(expectedA.getNumerator(), a.getNumerator());
			Assert::AreEqual(expectedA.getDenominator(), a.getDenominator());
		}

		TEST_METHOD(minusMinusPostCheck)
		{
			//checks that a CRational-- returns original CRational but
			//post decrements CRational by -1
			CRational a(3, 4);
			CRational expected = a;
			CRational expectedA;
			CRational actual;

			actual = a--;
			expectedA = a;

			Assert::AreEqual(expected.getNumerator(), actual.getNumerator());
			Assert::AreEqual(expected.getDenominator(), actual.getDenominator());
			Assert::AreEqual(expectedA.getNumerator(), a.getNumerator());
			Assert::AreEqual(expectedA.getDenominator(), a.getDenominator());
		}

		TEST_METHOD(boolIsEqual)
		{
			//checks that == returns true for equal CRationals
			CRational a(3, 4);
			CRational b(3, 4);
			bool actual = false;

			if (a == b)
				actual = true;

			Assert::IsTrue(actual);
		}

		TEST_METHOD(boolIsNotEqual)
		{
			//checks that != returns true for non-equal CRationals
			CRational a(3, 4);
			CRational b(8, 13);
			bool actual = false;

			if (a != b)
				actual = true;

			Assert::IsTrue(actual);
		}

		TEST_METHOD(boolLessThan)
		{
			//checks that *this < rationalNumber, returns true if less
			CRational a(3, 4);
			CRational b(9, 10);
			bool actual = false;

			if (a < b)
				actual = true;

			Assert::IsTrue(actual);
		}


		TEST_METHOD(boolLessThanorEqual)
		{
			//checks that *this <= rationalNumber, returns true if less or equal
			CRational a(3, 4);
			CRational b(3, 4);
			bool actual = false;

			if (a <= b)
				actual = true;

			Assert::IsTrue(actual);
		}

		TEST_METHOD(boolGreaterThan)
		{
			//checks that *this > rationalNumber, returns true if greater
			CRational a(3, 4);
			CRational b(1, 4);
			bool actual = false;

			if (a > b)
				actual = true;

			Assert::IsTrue(actual);
		}

		TEST_METHOD(boolGreaterThanorEqual)
		{
			//checks that *this >= rationalNumber, returns true if greater
			//or equal
			CRational a(3, 4);
			CRational b(1, 4);
			bool actual = false;

			if (a >= b)
				actual = true;

			Assert::IsTrue(actual);
		}

		TEST_METHOD(inverseOperatorCheck)
		{
			//checks that invert function switches numerator and nominator
			CRational test(3, 4);
			CRational expected(4, 3);
			CRational actual;
			actual = ~test;
			Assert::AreEqual(expected.getNumerator(), actual.getNumerator());
			Assert::AreEqual(expected.getDenominator(), actual.getDenominator());
		}
	};
}