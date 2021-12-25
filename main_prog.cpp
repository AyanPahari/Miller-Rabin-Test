// calling the entire standard library
#include <bits/stdc++.h>
using namespace std;

__uint128_t higher_power(uint64_t a, uint64_t b) // function that computes a^b and returns it
{
    __uint128_t result = 1; // to store the result as 128 bit, so no overflow happens
    while (b)               // loop until b is not equal to 0
    {
        if (b % 2 == 0) // if b is even
        {
            a = a * a; // increment the value of a
            b /= 2;    // update the value of b
        }
        else // if b is odd
        {
            result = result * a; // update the result
            b--;                 // decrement the value of b
        }
    }
    return result; // return the result computed
}

__uint128_t modular_higher_power(uint64_t a, uint64_t b, uint64_t n) // function that computes a^b % n and returns it
{
    __uint128_t result = 1; // to store the result as 128 bit, so no overflow happens
    a = a % n;              // updating the value of a
    while (b)               // loop until b is not equal to 0
    {
        if (b % 2 != 0) // if b is odd
        {
            result = (__uint128_t)result * a % n; // update the result
            b--;                                  // decrement the value of b
        }
        else
        {
            a = (__uint128_t)a * a % n; // update the value of a
            b /= 2;                     // update the value of b
        }
    }
    return result; // return the result computed
}

uint64_t two_factorize(uint64_t x) // this function computes k in n-1 = 2^k * t
{
    uint64_t k = 0;
    uint64_t t = x;
    while (t % 2 == 0) // loop until the t is even
    {
        k++;    // increment the value of k
        t /= 2; // half t in every iteration
    }
    return k; // return the value of k
}

bool check(int n) // this function is very inefficient in terms of runtime, I will not be using it in the main funcion, but this is way to determine if any number n is of the form a^b
{
    for (int a = 1; a <= sqrt(n) + 1; a++) // a goes till sqrt(n)
    {
        for (int b = 1; b <= log2(n) + 1; b++) // b goes till log(n)
        {
            if (n == higher_power(a, b)) // if n is equal to higher_power(a,b) computed using the function defined above
            {
                return true; // that means the number is of the form a^b
            }
        }
    }
    return false; // number not of the form a^b
}

bool check_if_composite(uint64_t a, uint64_t d, uint64_t s, uint64_t n) // check if the given number is composite or not
{
    uint64_t res = modular_higher_power(a, d, n); // calls the modular higher power function and stores the result in res
    if (res == 1)                                 // if res = 1 return false
    {
        return false;
    }
    if (res == n - 1) // if res = -1 i.e n - 1 return false
    {
        return false;
    }
    for (uint64_t k = 1; k < s; k++) // iterate till s-1 and keep squaring the terms till res == n-1
    {
        res = (__uint128_t)res * res % n; // squaring res and taking mod n
        if (res == n - 1)                 // if res == n-1 return false, that means the number is not composite
        {
            return false;
        }
    }
    return true; // this means the number is composite
}

bool check_for_power(uint64_t n) // this function opimally checks if any number can be denoted as a^b or not
{
    for (uint64_t k = 2; k * k <= n; k++) // iterate for sqrt(n) times
    {
        double res = log(n) / log(k);      // using the property of logs here
        if ((res - (int)res) < 0.00000001) // in double there is a precision gap of 10^-8
            return true;                   // this means the number can be denoted a a^b
    }
    return false; // this means the number cannot be denoted as a^b
}

bool Miller_Rabin_Test(uint64_t n, uint64_t r) // main miller rabin test function
{
    if (n == 2 || n == 3) // if n is equal to 3 that means it is prime or return true
    {
        return true;
    }

    if (check_for_power(n)) // this will check if n can be represented as a^b, if yes then return false as it is composite
    {
        return false;
    }

    uint64_t y = two_factorize(n - 1); // call the two_factorize function

    uint64_t k = 0;
    uint64_t t = n - 1;
    while (t % 2 == 0) // loop till t is even
    {
        k++;    // increment the value of k
        t /= 2; // half the value of t in each iteration
    }

    for (uint64_t p = 1; p <= r; p++) // making r number of iterations
    {
        uint64_t a1 = 1 + rand() % (n - 1);                // picking a number at random from 1 to n-1 and assigning it to a1
        uint64_t res = modular_higher_power(a1, n - 1, n); // calling the modular higher power function that will compute (a^n-1) % n

        if (res != 1) // if it is not equal to 1, that means the number is composite, so return false
        {
            return false;
        }

        uint64_t a = 2 + rand() % (n - 3);  // picking a number at random from 2 to n-2 and assigning it to a
        if (check_if_composite(a, t, k, n)) // checking if the number is composite or not by passing it to the check_if_composite function
        {
            return false; // if check_if_composite returns true that means number is composite, simple return false from here
        }
    }
    return true; // reaching this step means the number is indeed prime
}

int main()
{
    uint64_t n, r; // taking the input numbers as 64 bit ints
    cout << "n = ";
    cin >> n; // reading the value of n as input
    cout << "r = ";
    cin >> r; // reading the value of r as input
    cout << endl;
    if (Miller_Rabin_Test(n, r)) // calling the Miller_rabin main function
    {
        cout << n << " is a Prime number." << endl; // if the function returns then this will be printed
    }
    else
    {
        cout << n << " is a Composite number." << endl; // if the function returns then this will be printed
    }
    return 0;
}