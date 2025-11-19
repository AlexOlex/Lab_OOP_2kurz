// Myexecrefslib.cpp 
// compile with: cl /Ehsc Myexecrefslib.cpp /link Mathfuncslib.lib 
#include <iostream> 
#include "Mathfuncslib.h" 
using namespace std;
int main()
{
	double a = 7.4;
	int b = 99;
	cout << "a + b = " <<
		Mathfuncs::Mymathfuncs::Add(a, b) << endl;
	cout << "a - b = " <<
		Mathfuncs::Mymathfuncs::Subtract(a, b) << endl;
	cout << "a * b = " <<
		Mathfuncs::Mymathfuncs::Multiply(a, b) << endl;
	cout << "a / b = " <<
		Mathfuncs::Mymathfuncs::Divide(a, b) << endl;
	return 0;
}