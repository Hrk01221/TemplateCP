// To find GCD of a and b
int gcd(int a, int b);
 
int power(int x,  int y,  int m);
 
int modInverse(int a, int m)
{
    int g = gcd(a, m);
    return power(a, m-2, m);
    
}
// To compute x^y under modulo m
int power(int x, int y,  int m)
{
    if (y == 0)
        return 1;
    int p = power(x, y/2, m) % m;
    p = (p * p) % m;
 
    return (y%2 == 0)? p : (x%m * p%m) % m;
}
// Function to return gcd of a and b
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b%a, a);
}