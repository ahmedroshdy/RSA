#include<iostream>
#include<string>
#include<time.h>
#include"bigint.h"

using namespace std;
string add(string number1, string number2)
{
	string add = (number1.length() > number2.length()) ? number1 : number2;
	char carry = '0';
	int differenceInLength = abs((int)(number1.size() - number2.size()));

	if (number1.size() > number2.size())
		number2.insert(0, differenceInLength, '0'); // put zeros from left

	else
		number1.insert(0, differenceInLength, '0');

	for (int i = number1.size() - 1; i >= 0; --i)
	{
		add[i] = ((carry - '0') + (number1[i] - '0') + (number2[i] - '0')) + '0';

		if (i != 0)
		{
			if (add[i] > '9')
			{
				add[i] -= 10;
				carry = '1';
			}
			else
				carry = '0';
		}
	}
	if (add[0] > '9')
	{
		add[0] -= 10;
		add.insert(0, 1, '1');
	}
	return add;
}

string multiply(string n1, string n2)
{
	if (n1.length() > n2.length())
		n1.swap(n2);

	string res = "0";
	for (int i = n1.length() - 1; i >= 0; --i)
	{
		string temp = n2;
		int currentDigit = n1[i] - '0';
		int carry = 0;

		for (int j = temp.length() - 1; j >= 0; --j)
		{
			temp[j] = ((temp[j] - '0') * currentDigit) + carry;

			if (temp[j] > 9)
			{
				carry = (temp[j] / 10);
				temp[j] -= (carry * 10);
			}
			else
				carry = 0;

			temp[j] += '0'; // back to string mood
		}

		if (carry > 0)
			temp.insert(0, 1, (carry + '0'));

		temp.append((n1.length() - i - 1), '0'); // as like mult by 10, 100, 1000, 10000 and so on

		res = add(res, temp); // O(n)
	}

	while (res[0] == '0' && res.length() != 1) // erase leading zeros
		res.erase(0, 1);

	return res;
}



int main(){
	clock_t t;


	string s, q,e, operation;
	cin >> s;
	cin >> q;
	cin >> e;
	s = s.substr(2);
	q = q.substr(2);
	e = e.substr(2);
	bigint p(s), Q(q),E(e);
	bigint result("1");


	t = clock();
//for (int i = 0; i < 1000; i++)
//	{
//		result = p.inverse(p, Q);
//		//result = p.square(p);
//		//result = p.divide(p, p);
//		//operation = multiply("12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871", "2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473");
//	}
t = clock() - t;
	//result = p.add(p, Q);
	//result = p.multiply(p, Q);
	//result = p.square(p);
//	result = p.mod(p, Q);
	bigint one("1");
	//result = p.inverse(p, Q);
	while (true)
	{
		cin >> operation;
		if (operation == "IsPPrime")
		{
			if (result.isPrime(p, 1))
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}
		else if (operation == "IsQPrime")
		{
			if (result.isPrime(Q, 1))
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}
		else if (operation == "PrintN")
		{
			result = p.multiply(p, Q);
			p.print(result);
		}
		else if (operation == "PrintPhi")
		{
			
			result = result.multiply(p.subtract(p, one), Q.subtract(Q, one));
			p.print(result);
		}
		else if (operation == "Quit")
			break;
		else if (operation == "PrintD")
		{
			bigint phi;
			phi = result.multiply(p.subtract(p, one), Q.subtract(Q, one));
			result=p.inverse(E, phi);
			p.print(result);
		}
		else if (operation.substr(0, 13) == "EncryptPublic")
		{
			 bigint msg(operation.substr(15, operation.length() -16));
			 result = result.power(msg, E, p.multiply(p, Q));
			 p.print(result);
		}
		else if (operation.substr(0, 14) == "EncryptPrivate"){
			bigint msg(operation.substr(16, operation.length() - 17));
			bigint phi;
			phi = result.multiply(p.subtract(p, one), Q.subtract(Q, one));
			result = result.power(msg, p.inverse(E, phi), p.multiply(p, Q));
			p.print(result);
		}
	}
	//result = p.multiply(p, Q);
	//result = p.divideby2(p);
//	cout << p.larger(p, Q)<<endl;
/*	for (size_t i = 0; i < 100; i++)
	{
		result = p.mod(p, Q);
	}
 */
	
    
	//cout << operation << endl;
	//p.print(result);
	cout <<"Execution time : "<< (double)t / CLOCKS_PER_SEC<< endl;
	//string p, q , e;
	//vector<int> temp;
	//unsigned long long int x,y;
	//x = 8223372036854775807;
	//y = 1000000000000000000;


	return 0;
}
