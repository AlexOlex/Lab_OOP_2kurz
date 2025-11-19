// Mathfuncslib.cpp 
// compile with: cl /c /Ehsc Mathfuncslib.cpp 
// post-build command: lib Mathfuncslib.obj 
#include "Mathfuncslib.h" 
#include <stdexcept> 
using namespace std;
namespace Mathfuncs
{
	double Mymathfuncs::Add(double a, double b)
	{
		return a + b;
	}
	double Mymathfuncs::Subtract(double a, double b)
	{
		return a - b;
	}
	double Mymathfuncs::Multiply(double a, double b)
	{
		return a * b;
	}
	double Mymathfuncs::Divide(double a, double b)
	{
		return a / b;
	}
}