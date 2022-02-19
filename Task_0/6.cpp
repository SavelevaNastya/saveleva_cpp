#include <iostream>
#include <string>

using namespace std;

class A
{
protected:

	static const int num;
	string code;

public:

	~A()
	{}

	A(string const& c) :
		code(c)
	{}

	virtual string what() const
	{
		return code + to_string(num);
	}
};
const int A::num = 0;

class B : public A
{
protected:

	static const int num;

public:

	 ~B(){}

	B(string const& c) :
		A(c)
	{}

	virtual string what() const override
	{
		return code + to_string(num);
	}
};
const int B::num = A::num + 1;

class C : public B
{
protected:
	static const int num;
public:

	~C() {}

	C(string const& c) :
		B(c)
	{}

	virtual string what() const override
	{
		return code + to_string(num);
	}
};
const int C::num = B::num + 1;

int main()
{
	for (int i = 0; i < 3; i++)
	{
		try
		{
			if (i == 0)
				throw C("1244c");
			else if (i == 1)
				throw B("1233b");
			else
				throw A("1234a");
		}
		catch (A const& except)
		{
			cout << except.what() << endl;
		}
	}

}
