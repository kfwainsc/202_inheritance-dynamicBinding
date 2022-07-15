/* concepts.cpp */
/*******************************************************************
**  Kendra Wainscott           CS202                 spring 2022  **
**                             Prog#3                             **
*******************************************************************/
/* This file is the implementation of the ABD Concept class and all
** the classes derived from it: Stl, ModProg, Pylib. The Concept
** class is declared vitual to allow for upcasting in which a 
** Concept pointer can point to any of the derived class objects 
** and allow the appropriate function to be called at runtime.
*******************************************************************/
#include "concepts.h"
using namespace std;
/*******************************************************************
*************************  CONCEPT  ********************************
*******************************************************************/
/* Data members: string name 
				 string description 
			     multimap <string, bool> websites */

Concept::Concept() :name("null"), description("null") {}

Concept::Concept(const array<string,SIZE>& about, 
                 const multimap<string,bool>& web)
       :name(about.at(0)), description(about.at(1)), websites(web){}

Concept::~Concept()
{//set to default vals if no dynamic memory
	websites.clear();
	name = description = "null";
}

void Concept::in_web() //reading in a website 
{
	Helper h; //helper throws exceptions for bad input
	h.read_web(websites);	
}

/**** VIRTUAL FUNCTIONS ONLY IMPLEMENTED IN DERIVED ***/
void Concept::select()			   {} 
bool Concept::add_info()           {return false;}
bool Concept::update_description() {return false;}
void Concept::display_all() const  {}
/*****************************************************/

ostream& Concept::write_file(ostream& out) const
{return out;}

bool Concept::find(const string & key) const
{ return name == key; }

/************  OVERLOADED OPERATORS  ****************/
bool Concept::operator == (const Concept & source)
{ return name == source.name; }

bool Concept::operator < (const Concept & source)
{ return name < source.name; }

bool Concept::operator > (const Concept & source)
{ return name > source.name; }

bool Concept::operator <= (const Concept & source)
{ return name <= source.name; }

bool Concept::operator >= (const Concept & source)
{ return name >= source.name; }

//ostream &operator<<(std::ostream& out, Concept& op)
//{ return out; }

/*******************************************************************
*************************  STL  ************************************
*******************************************************************/
/* Data Members: vector <Method> methods{} //contaier of methods */

Stl::Stl() :Concept(){}

Stl::Stl(const array<string,SIZE>& about, 
         const multimap<string,bool>& web,
         const vector<Method>& mthd) 
    :Concept(about, web), methods(mthd){}

Stl::~Stl() //set to default vals   
{ methods.clear(); }

void Stl::select(){} //selecting a website 

bool Stl::add_info()
{return 0;} 

bool Stl::update_description()
{return 0;}

void Stl::display_all() const
{//oveloaded << throws exceptions on bad input
	cout << *this; 
}

// must be DOWNCAST not a function in ABC
int Stl::display_methods() const
{
	int count {0};
	for(Method m : methods){
		cout << m << endl;
		++ count;
	}return count;
 } 

ostream& Stl::write_file(ostream& out) const
{
	out << *this; 
	return out;
}

/*// May not be needed
ostream& write_file(ostream& out, const Stl& stlObj)
{ out << stlObj;
	return out; } */

ostream & operator<<(ostream & out, const Stl & stl)
{
	if(stl.name == "null"){
		OPERATOR_ERROR e;
		throw e;
	}
	out << stl.self <<"\n****************\n" << stl.name 
		 <<"\n****************\n"<< stl.description
		 <<"\nRESOURCES:\n";
	for(auto it=stl.websites.begin(); it!=stl.websites.end(); ++it)
	out << it->first <<"\n";
	out <<"\n***  METHODS  ***\n";
	for(Method m : stl.methods)
		out << m <<"\n";
	return out;
}
/*******************************************************************
*************************  MODPROG  ********************************
*******************************************************************/
/* Data members: websites with a rating/useful indicator 
				 multimap <string, bool> websites 
				 description of benefits & drawbacks for concept
				 string good_bad */

ModProg::ModProg(){}

ModProg::ModProg(const array<string,SIZE>& about, const
                 multimap<string,bool>& web, const string& goodBad) 
		:Concept(about, web), good_bad(goodBad) 
{
	for(auto it = websites.begin(); it!= websites.end(); ++it)
		cout << it->first <<"\n";
}

ModProg::~ModProg(){} //set to default vals if no dynamic memory 

/*
void ModProg::in_web()  //reading in a website
{
	string str{"Enter website address to add: "};
	string defaultStr{"none"};	

	Helper h;
	str = h.get_str(str, defaultStr);
	cout << "Is this site helpful? yes(1) | no(0)\n";
	int rate = h.get_answer(1,0,0); 

	websites.insert({str,rate});	
}*/

void ModProg::select(){} //selecting a website 
bool ModProg::add_info(){return 0;} 
bool ModProg::update_description(){return 0;}

void ModProg::display_all() const
{//oveloaded << throws exceptions on bad input
	cout << *this; 
}

ostream& ModProg::write_file(ostream& out) const
{//oveloaded << throws exceptions on bad input
	out << *this; 
	return out;
}

ostream& operator<<(ostream& out, const ModProg& mod)
{
	if(mod.name == "null"){
		OPERATOR_ERROR e;
		throw e;
	}
	out <<"\n<<<<<<  Modern Programing Concepts  <<<<<<<<<<\n"
		<< mod.name <<"\n"<< mod.description <<"\n"
        << mod.good_bad <<"\nResources:\n";
	for(auto it = mod.websites.begin(); it!= mod.websites.end(); ++it)
		out << it->first <<"\n";
	return out;
}
/*******************************************************************
*************************  PYLIB  **********************************
*******************************************************************/
/* Data members: vector <Method> methods */

PyLib::PyLib(){}

PyLib::PyLib(const array<string,SIZE>& about, 
             const multimap<string,bool>& web,
             const vector <Method> & mthd) 
			:Concept(about, web), methods(mthd){}

PyLib::~PyLib()//set to default vals, no dynamic memory 
{ methods.clear(); }

void PyLib::select()
{
	//select a website, out to external
}

bool PyLib::add_info(){return 0;} 
bool PyLib::update_description(){return 0;}

void PyLib::display_all() const
{//oveloaded << throws exceptions on bad input
	cout << *this; 
}

// must be DOWNCAST not a function in ABC
int PyLib::display_methods() const
{
	int count {0};
	for(Method m : methods){
		cout << m << endl;
		++ count;
	}return count;
} 

ostream& PyLib::write_file(ostream& out) const
{
	out << *this; 
	return out;
}

ostream& operator<<(ostream& out, const PyLib& py)
{
	if(py.name == "null"){
		OPERATOR_ERROR e;
		throw e;
	}
	out <<"\n" << py.self <<"\n#############################\n"
		<< py.name <<"\n#############################\n"
		<< py.description <<"\nRESOURCES:\n";
	for(auto it = py.websites.begin(); it!= py.websites.end(); ++it)
	out << it->first <<"\n";
	out <<"\n###  METHODS  ###\n";
	for(Method m : py.methods)
		out << m <<"\n";
	return out;
}

