/*
* ---------------------------------------------------
*  Copyright (c) 2017 josan All rights reserved.
* ---------------------------------------------------
*
*               创建者： Josan
*             创建时间： 2017/9/18 16:57:06
*/
#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <memory>
using namespace std;

class Oper
{
public:
	double getNumberA()
	{
		return x;
	}
	void setNumberA(double xx)
	{
		x = xx;
	}
	double getNumberB()
	{
		return y;
	}
	void setNumberB(double yy)
	{
		y = yy;
	}
	virtual double getResult() = 0;
	virtual ~Oper()
	{

	}
private:
	double x;
	double y;
};

class OperatorAdd :public Oper
{
public:
	double getResult()
	{
		return getNumberA() + getNumberB();
	}
};

class OperatorSub :public Oper
{
public:
	double getResult()
	{
		return getNumberA() - getNumberB();
	}
};

class OperatorMul :public Oper
{
public:
	double getResult()
	{
		return getNumberA() * getNumberB();
	}
};

class OperatorDiv :public Oper
{
public:
	double getResult()
	{
		try
		{
			if(fabs(getNumberB()) < 1e-9)
			{
				throw overflow_error("Divide by zero exception");
			}
		}
		catch(overflow_error& e)
		{
			cout << e.what() << " -> " << getNumberB() << endl;
		}
		return getNumberA() / getNumberB();
	}
};

class OperFactory
{
public:
	static shared_ptr<Oper> createOper(char operChar)
	{
		shared_ptr<Oper> oper;
		switch(operChar)
		{
		case '+':
			oper = make_shared<OperatorAdd>();
			break;
		case '-':
			oper = make_shared<OperatorSub>();
			break;
		case '*':
			oper = make_shared<OperatorMul>();
			break;
		case '/':
			oper = make_shared<OperatorDiv>();
			break;
			//other operation
		default:
			;
		}
		return oper;
	}
};

void testSimpleFactoryMode()
{
	shared_ptr<Oper> oper(OperFactory::createOper('+'));
	oper->setNumberA(1);
	oper->setNumberB(2);
	double res = oper->getResult();
	cout << res << endl;
}


int main()
{
	testSimpleFactoryMode();
	return 0;
}

