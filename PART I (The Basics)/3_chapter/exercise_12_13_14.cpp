/*
[12]
Create a program to find all the prime numbers between 1 and 100. One way to do this is to
write a function that will check if a number is prime (i.e., see if the number can be divided by
a prime number smaller than itself) using a vector of primes in order (so that if the vector is
called primes, primes[0]==2, primes[1]==3, primes[2]==5, etc.). Then write a loop that goes
from 1 to 100, checks each number to see if it is a prime, and stores each prime found in a
vector. Write another loop that lists the primes you found. You might check your result by
comparing your vector of prime numbers with primes. Consider 2 the first prime.
[13]
Create a program to find all the prime numbers between 1 and 100. There is a classic method
for doing this, called the ‘‘Sieve of Eratosthenes.’’ If you don’t know that method, get on the
Web and look it up. Write your program using this method.
[14] 
Write a program that takes an input value n and then finds the first n primes.
*/

import PPP;
using namespace std;

/*
* //not needed
bool check_fractional_part(double d)
{
	if (d - int(d))
		return true; //there is a fractional part
		else
		return false; //an integer
}
*/


bool check_if_prime(unsigned int d) // Sieve of Eratosthenes is unnecessary complicated so i didn't use it.
{
	if (d < 2)return false;
	for (unsigned int num{2}; d != num; ++num)
	{
		if((d%num)==0)return false;
	}
	return true;
}


int main()
try {
	cout << "Type an integer number followed by enter: ";
	unsigned int bar{};
	cin >> bar;
	cout << "Here are " << bar<<" primes" << ":\n";
	unsigned int potentially_prime{ 2 }; // start with the prime 2 
	for (unsigned int quantity{ 1 }; quantity <= bar;) // 1 because we enter loop with prime 2 
	{
		if (check_if_prime(potentially_prime))
		{
			cout << potentially_prime << "\n";
			++quantity;
		}
		++potentially_prime;
	}
	system("pause");
	return 0;
}
catch (const string& surprise)
{
	cerr << surprise << '.' << endl;
	system("pause");
}
catch (...) {
	cerr << "Caught an unknown exception." << endl;
	system("pause");
}