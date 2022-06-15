#include <iostream>
#include <iomanip>
#include <time.h>
#include <math.h>
using namespace std;
class Polynomial; //forward declaration
//first
//second
class Term
{
	friend Polynomial;

private:
	float coef; //coefficient
	int exp;	//exponent
};
class Polynomial
{
public:
	Polynomial(int c = 0);
	void GetTerm(float &coef, int &exp, int location);
	friend istream &operator>>(istream &is, Polynomial &p);
	friend ostream &operator<<(ostream &os, Polynomial &p);
	void NewTerm(float coef, int exp);
	Polynomial Add(Polynomial b);
	Polynomial Mult(Polynomial b);
	float eval(float x);
	~Polynomial();
	//omit
private:
	Term *termArray;
	int capacity; //size of termArray
	int terms;	  //number of nonzero terms
};
Polynomial::Polynomial(int c)
{
	capacity = c;
	terms = 0;
	termArray = new Term[c];
}
void Polynomial::GetTerm(float &coef, int &exp, int location)
{
	coef = termArray[location].coef;
	exp = termArray[location].exp;
}
void Polynomial::NewTerm(float coef, int exp)
{
	if (capacity == terms)
	{
		if (capacity == 0)
			capacity++;
		else
			capacity *= 2;
		Term *TermTmp = new Term[capacity];
		for (int i = 0; i < terms; ++i)
		{
			TermTmp[i] = termArray[i];
		}
		delete[] termArray;
		termArray = TermTmp;
		//p.termArray = new Term[p.capacity];
	}
	termArray[terms].coef = coef;
	termArray[terms].exp = exp;
	terms++;
}
Polynomial Polynomial::Add(Polynomial b)
{
	int apos = 0, bpos = 0;
	Polynomial c;
	while (apos < terms && bpos < b.terms)
	{
		if (termArray[apos].exp < b.termArray[bpos].exp)
		{
			c.NewTerm(termArray[apos].coef, termArray[apos].exp);
			apos++;
		}
		else if (termArray[apos].exp == b.termArray[bpos].exp)
		{
			float tmp = termArray[apos].coef + b.termArray[bpos].coef;
			if (tmp)
				c.NewTerm(tmp, termArray[apos].exp);
			apos++;
			bpos++;
		}
		else
		{
			c.NewTerm(b.termArray[bpos].coef, b.termArray[bpos].exp);
			bpos++;
		}
	}
	while (apos < terms)
	{
		c.NewTerm(termArray[apos].coef, termArray[apos].exp);
		apos++;
	}
	while (bpos < b.terms)
	{
		c.NewTerm(b.termArray[bpos].coef, b.termArray[bpos].exp);
		bpos++;
	}
	return c;
}
Polynomial Polynomial::Mult(Polynomial b)
{
	clock_t start, end;
  	double time_used;
	start = clock();
	//
	Polynomial c;
	for (int i = 0; i < terms; ++i)
	{
		Polynomial *tmp = new Polynomial(b.terms);
		for (int j = 0; j < b.terms; ++j)
		{
			tmp->termArray[j].coef = termArray[i].coef * b.termArray[j].coef;
			tmp->termArray[j].exp = termArray[i].exp + b.termArray[j].exp;
			tmp->terms++;
		}
		if (i == 0)
			c = *tmp;
		else
			c = c.Add(*tmp);
		delete tmp;
	}
	end = clock();
	time_used = ((double) (end - start))/ CLOCKS_PER_SEC ;
	cout<<"time_used(sec): "<<time_used<<endl;
	return c;
}
float Polynomial::eval(float x)
{

	clock_t start, end;
  	double time_used;
	start = clock();

	float result = 0;
	for (int i = 0; i < terms; ++i)
	{
		result += termArray[i].coef * pow(x, termArray[i].exp);
	}
	end = clock();
	time_used = ((double) (end - start))/ CLOCKS_PER_SEC ;
	cout<<"time_used(sec): "<<time_used<<endl;
	return result;
}
Polynomial ::~Polynomial()
{
	
}
ostream &operator<<(ostream &os, Polynomial &p)
{
	float coef;
	int exp;
	for (int i = p.terms - 1; i >= 0; --i)
	{
		p.GetTerm(coef, exp, i);
		if (coef > 0)
			os << coef;
		else if(coef < 0)
			os <<'('<<coef<<')';
		if (exp != 0)
		{
			os << "x^";
			os << exp;
		}
		if (i > 0)
				os << "+";
	}
	return os;
}
istream &operator>>(istream &is, Polynomial &p)
{
	
	float coef;
	int exp;
	char c;
	cout << "輸入polynomial(由低次項到高次項)" << endl;
	while (c != '\n')
	{
		is >> coef >> exp;
		c = cin.peek();
		while (c == ' ')
		{
			cin.ignore(1);
			c = cin.peek();
		}
		p.NewTerm(coef, exp);
	}
	cin.ignore();
	return is;
}
int main()
{
	Polynomial p, q;
	cin >> p;
	cout <<"Polynomial1: " << p << endl;
	//cin >> q;
	//cout <<"Polynomial2: " << q << endl;
	//Polynomial r;
	//r = p.Mult(q);
	float t,ans;
	cin>>t;
	ans = p.eval(t);
	cout<<ans<<endl;
}
