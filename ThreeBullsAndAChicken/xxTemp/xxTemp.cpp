// xxTemp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include "boost/utility.hpp"
class Mutant : public boost::noncopyable
{
};
class Ml : public Mutant
{

};
class MutantModelHandler : public boost::noncopyable
{
public:
	MutantModelHandler(Mutant* mutant)
	{
		cout << "construcot" << this << endl;
	}
	~MutantModelHandler()
	{
		cout << "destroctor" << this << endl;
	}
	void print()
	{
		cout << "print print " << this << endl;
	}
private:
	MutantModelHandler(const MutantModelHandler& that)
	{

	}
	MutantModelHandler& operator=(const MutantModelHandler& that)
	{

	}

};

class wtf
{
public:
	wtf(Mutant* mutant) :myMutant(mutant)
	{
		cout << "wtconstrucotr" << this << endl;
		cout << "and this is my mutant" << myMutant << endl;
	}
	~wtf()
	{
		cout << "wtdfestrucotr" << this << endl;
		cout << "and this is my mutant" << myMutant << endl;
	}
	void print()
	{
		cout << "i am wtf, see me print:" << this << endl;
		cout << "and this is my mutant" << myMutant << endl;
	}
	Mutant* myMutant;
};
class test
{

};
class ye
{
public: 
	ye() :lol(test())
	{

	}
private:
	test& lol;
};
class megaPointer
{
};
int main()
{
	Mutant* mutant = new Mutant();
	vector<unique_ptr<MutantModelHandler>> mHandlers;
	mHandlers.push_back(unique_ptr<MutantModelHandler>(new MutantModelHandler(mutant)));
	mHandlers[0]->print();
//	vector<Ml> mls;
//	mls.push_back(Ml());   error

	cout << "begining wtftest" << endl;
	std::vector<wtf> vWtf;
	vWtf.push_back( std::move( wtf(mutant) ) );
	vWtf[0].print();

	megaPointer l;
	megaPointer k = std::move(l);
	int* pp = new int(4);
	unique_ptr<int> ppp{ pp };
	cout << *ppp << endl;
	char p;
	cin >> p;
	return 0;
}

