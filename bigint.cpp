#include"bigint.h"
#include<string>
#include<algorithm>
#include<iostream>
#include<assert.h>
#include<stack>
bigint::bigint(string temp){
	for ( int i = temp.length() - 1; i>-1; i--)
		data.push_back(temp[i] - '0');
}
bigint::bigint(){
	for (unsigned int i = 0; i < data.size(); i++){
		data.push_back(0);
	}
}



bigint bigint::add(bigint a, bigint b){
	bigint result;
	int carry = 0;
	int difflength = abs((int)(a.data.size() - b.data.size()));
	int digit = 0;
	vector<int>::iterator it;
	it = (a.data.size() < b.data.size()) ? a.data.end() : b.data.end();
	if (a.data.size() > b.data.size())
		b.data.insert(it, difflength, 0);
	else if(a.data.size() < b.data.size())
		a.data.insert(it, difflength, 0);
	
	for (unsigned int i = 0; i < a.data.size(); i++)
	{     
		digit = carry + a.data[i] + b.data[i];
		if (digit>9)
		{
			result.data.push_back(digit % 10);
			carry = 1;
		}
		else
		{
			result.data.push_back(digit);
			carry = 0;
		}
	}
	if (digit > 9)
		result.data.push_back(1);

	return result;
}

bigint bigint::multiply(bigint a, bigint b){
	bigint result("0");
	if (a.data.size() > b.data.size())
		a.data.swap(b.data);
	vector<int>::iterator it;
	for (unsigned int i = 0; i < a.data.size(); i++)
	{
		bigint temp;
		int current = a.data[i];
		int carry = 0;//
		int digit = 0;// unsigned long
		for (unsigned int j = 0; j < b.data.size(); j++)
		{
			digit = (b.data[j] * current) + carry;
			if (digit >9)//99999999
			{
				temp.data.push_back(digit % 10);
				carry = digit / 10;//1000000000
			}
			else
			{
				temp.data.push_back(digit);
				carry = 0;
			}
		}
		if (carry > 0)
			temp.data.push_back(carry);
		it = temp.data.begin();
		temp.data.insert(it, i, 0);
		result = add(result, temp);
	}
	while (result.data[result.data.size() - 1] == 0 && result.data.size() != 1)
		result.data.erase(result.data.end()-1);
	return result;
}

bigint bigint::multiplybytwo(bigint a){
	return add(a, a);
}
bigint bigint::subtract(bigint a, bigint b){
//only a must be > or equal b
	//assert( larger(a,b));
	
	int carry = 0;
	bigint result;
	if (larger(b, a) && !equal(a, b)){
		a.data.swap(b.data);
		result.data.push_back('-');
	}

	b.data.resize(a.data.size(), 0);
	for (unsigned int i = 0; i < a.data.size(); i++)
	{
		int temp = a.data[i] - b.data[i] - carry; 
		if (temp<0){
			temp += 10;
			carry = 1;
		}
		else{
			carry = 0;
		}
		result.data.push_back(temp);
	}
	while (result.data[result.data.size() - 1] == 0 && result.data.size() != 1)
		result.data.erase(result.data.end() - 1);
	return result;
}
bool bigint::equal(bigint &a, bigint &b){
	if (a.data.size() != b.data.size())
		return false;
	string s1, s2;
	for (int i = a.data.size() - 1; i > -1; i--){
		s1 += a.data[i] + '0';
		s2 += b.data[i] + '0';
	}
	if (s1 == s2)
		return true;
	//bigint zero;
	//bigint result;
	//result = subtract(a, b);
	//zero.data.resize(result.data.size(), 0);
	//if (zero.data == subtract(a, b).data) return true;
	return false;
}
bool bigint::larger(bigint &a, bigint &b){
	if ( a.data.size() > b.data.size())
		return true;
	else if (a.data.size() == b.data.size())
	{
		string s1, s2;
		for (int i = a.data.size() - 1; i > -1; i--){
			s1 += a.data[i] +'0';
			s2 += b.data[i]+'0';
		}
		if (s1>=s2)
		return true;
	}
	return false;
}

bigint bigint::divide(bigint dividend, bigint divisor){
	bigint quotient;
	if (equal(dividend,divisor)){
		quotient.data.push_back(1);
		return quotient;
	}
	if (!larger(dividend,divisor)){
		quotient.data.push_back(0);
		return quotient;
	}
	bigint residue;
	bigint two;
	bigint half;
	bigint half_divide;
	bigint zero;
	bigint temp;

	two.data.push_back(2);
	half.data.push_back(5);
	int cnt = 0;
	 while (larger(dividend,divisor)){
		 residue = divisor;
		 half_divide = multiply(dividend, half);
		 half_divide.data.erase(half_divide.data.begin());
		 cnt = 0;
		while (!equal(dividend,residue) && !larger(residue,half_divide)){
			residue = multiplybytwo(residue);		
			cnt++;
		}

		temp.data.push_back(1);
		for (int i = 0; i < cnt; i++)
		{
			temp = multiplybytwo(temp);
		}
		quotient = add(temp,quotient);
		while (!temp.data.empty())
			temp.data.pop_back();
	    dividend=subtract(dividend, residue);
		if (dividend.data[dividend.data.size() - 1] == 0)dividend.data.erase(dividend.data.end() - 1);
		while (!residue.data.empty())
			residue.data.pop_back();

	}

	 return quotient;
}

bigint bigint::mod(bigint dividend, bigint divisor){
	bigint result;
	if (equal(dividend, divisor)){
		result.data.push_back(0);
		return result;
	}
	if (!larger(dividend, divisor)){
		return dividend;
	}
	bigint residue;
	bigint two;
	bigint half;
	bigint half_divide;
	bigint zero;
	bigint temp;
	two.data.push_back(2);
	half.data.push_back(5);
	int cnt = 0;
	while (larger(dividend, divisor)){
		residue = divisor;
		half_divide = multiply(dividend, half);
		half_divide.data.erase(half_divide.data.begin());
		cnt = 0;
		while (!equal(dividend, residue) && !larger(residue, half_divide)){
			residue = multiplybytwo(residue);
			cnt++;
		}

		temp.data.push_back(1);
		for (int i = 0; i < cnt; i++)
		{
			temp = multiplybytwo(temp);
		}
	
		while (!temp.data.empty())
			temp.data.pop_back();
		dividend = subtract(dividend, residue);
		while(dividend.data[dividend.data.size() - 1] == 0)dividend.data.erase(dividend.data.end()-1);
		while (!residue.data.empty())
			residue.data.pop_back();
		if (dividend.data.size()==0)
			dividend.data.push_back(0);
	}

	return dividend;


}
bigint bigint::divideby2(bigint dividend){
	bigint result;
	bigint five("5");
	result=multiply(dividend,five );
	result.data.erase(result.data.begin());
	return result;
}

bigint bigint::mod2(bigint dividend){
	bigint result;
	bigint five("5");
	if (*multiply(dividend, five).data.begin() == 5)
		result.data.push_back(1);
	else
		result.data.push_back(0);
	return result;
}
bigint bigint::random(bigint number){
	int x = number.data.size();
	for (int i = 0; i < x; i++)
		number.data.pop_back();

	for (int i = 0; i < x; i++)
		number.data.push_back(rand() % 10);
	return number;
}
bigint bigint::square(bigint number){
	bigint temp;
	bigint result("0");
	bigint zero("0");
	bigint one("1");
	temp = number;
	while (larger(temp, zero)&&!equal(temp,zero)){
		result = add(result, number);
		temp = subtract(temp, one);
	}
	return result;

}
bigint	bigint::power(bigint a, bigint q, bigint n){
	bigint result("1");
	bigint one("1");
	bigint zero("0");
	a = mod(a, n);
	while (larger(q,zero))
	{
		if (equal(mod2(q),one))
			result = mod(multiply(result, a), n);
		q = divideby2(q);
		a = mod(multiply(a, a), n);
	}
	return result;
}

/*bigint	bigint::power(bigint a, bigint q, bigint n){
	bigint temp("1");
	bigint temp2;
	bigint result("1");
	bigint zero("0");
	int cnt=0;
	while (!equal(q, zero)){
		while (!larger(temp, q)||equal(temp,q)){
			temp = multiplybytwo(temp);
			cnt++;
		}
		temp2 = mod(a, n);
		for (int i = 0; i < cnt-1; i++)
		{
			temp2 = multiply(temp2,temp2);
			temp2 = mod(temp2, n);
		}
		cnt = 0;
		result = mod(multiply(temp2, result),n);
		temp = divideby2(temp);
		q = subtract(q, temp);
		if (q.data[q.data.size() - 1] == 0)q.data.erase(q.data.end() - 1);
		while (!temp.data.empty())
			temp.data.pop_back();
		temp.data.push_back(1);
		//result = mod(temp, n);
	}
	//if (result.data[result.data.size() - 1] == 0)result.data.erase(result.data.end() - 1);
	return result;
}*/

bool bigint::miller(bigint q, bigint n){
	bigint one("1");
	bigint two("2");
	bigint nminus1;
	nminus1 = subtract(n, one);
	bigint a = mod(add(one, random(n)), subtract(n, two));
	while (!one.data.empty())one.data.pop_back();
	one.data.push_back(1);
	bigint result;
	result = power(a, q, n);
	if (equal(result, one) || equal(result, nminus1)) return true;
	while (!equal(q,nminus1))
	{
		result = mod(multiply(result, result), n);
		q = multiplybytwo(q);
		if (equal(result,one)) return false;
		if (equal(result, nminus1)) return true;
	}

	return false;

}

bool bigint::isPrime(bigint n, int acccuracy){
	bigint zero("0");
	//zero.data.resize(n.data.size(), 0);
	bigint two("2");
	//if zero or 1 not prime 
	if (equal(n, zero) || (n.data[0] == 1 && n.data.size() == 1))
		return false;
	//if two
	if (equal(n, two))
		return true;
	//if even numbers
	if (equal(mod2(n), zero))
		return false;
	//miller rabin
	bigint one("1");
	bigint q = subtract(n, one);
	while (equal(mod2(q), zero))
		q=divideby2(q);
	for (int i = 0; i < acccuracy; i++)
		if (miller(q, n) == false)
			return false;

	return true;
}

bigint bigint::inverse(bigint number, bigint phi){
	bigint quot;
	bigint zero("0");
	bigint one("1");
	bigint a2("0"), b2("1"), a3, b3, t2, t3;
	a3 = phi;
	b3 = number;
	while (larger(a3, one) && !equal(a3, one))
	{
		if (equal(b3, zero)) return a3 ;
		if (equal(b3, one)) return b2;
		quot = divide(a3, b3);
		t2 = subtract(a2, multiply(quot, b2));
		while (*(t2.data.begin()) == '-')
		{
			t2.data.erase(t2.data.begin());
			t2 = subtract(phi, t2);
		}
		
		/*int x = 0; int y = 0;
		if (*(a2.data.begin()) == '-'){
			if (*(b2.data.begin()) == '-'){
				b2.data.erase(b2.data.begin());
				y = 1;
			}
			a2.data.erase(a2.data.begin());
			t2 = add(a2, multiply(quot, b2));
			t2.data.insert(t2.data.begin(), '-');
			if (y == 1)t2.data.insert(t2.data.begin(), '-');
		}
		else if (*(b2.data.begin()) == '-'){
			if (*(a2.data.begin()) == '-'){
				a2.data.erase(a2.data.begin());
				 x = 1;
			}
			b2.data.erase(b2.data.begin());
			t2=add(a2, multiply(quot, b2));
			b2.data.insert(b2.data.begin(), '-');
			if (x == 1)t2.data.insert(t2.data.begin(), '-');
		}
		else*/
		t3 = mod(a3, b3);
		a2 = b2;
		a3 = b3;
		b2 = t2;
		b3 = t3;
	}
}


void bigint::print(bigint p){
	for (int i = p.data.size()-1; i > -1; --i)
		cout << p.data[i];
	cout << endl;
}