#ifndef BIGINT_H_
#define BIGINT_H_
#include<vector>
#include<stdint.h>
using namespace std;
class bigint
{
public:
	bigint();
	bigint(string temp);
	bigint add(bigint a, bigint b);
	bigint subtract(bigint a, bigint b);
	bigint multiply(bigint a, bigint b);
	bigint multiplybytwo(bigint a);
	bigint divide(bigint dividend, bigint divisor);
	bigint divideby2(bigint dividend);
	bigint mod2(bigint dividend);
	bigint exp(bigint &a, bigint &b);
	bigint mod(bigint dividend, bigint divisor);
	bool equal(bigint &a, bigint &b);
	bool larger(bigint &a, bigint &b);
	bigint random(bigint number);
	bigint square(bigint number);
	bigint power(bigint a, bigint q, bigint n);
	bool miller(bigint q, bigint n);
    bool isPrime(bigint n, int accuracy);
	bigint inverse(bigint number, bigint phi);
	//bigint half(bigint a);
	void print(bigint p);
private:
	vector<int> data;
	//vector<uint64_t> data;
};



#endif 