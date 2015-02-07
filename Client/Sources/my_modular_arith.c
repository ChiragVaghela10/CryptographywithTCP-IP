#include "../headers/my_modular_arith.h"

long int mul_inv(long int a,long int b)
{
	long int b0 = b, t, q;
	long int x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

long long int modular_expo(long int b,long int e,long int m)
{
    long long int r=1,base=b;
    base %= m;
    while(e)
        {
            if( e%2 ==1 )
                r = (r*base) % m;
            e = e >> 1;
            base = (base * base) % m;
        }
    return r;
}
