/* concepts.h */
/*******************************************************************
**  Kendra Wainscott           CS202                 spring 2022  **
**                             Prog#3                             **
********************************************************************
** This file contains the definitions of the ABD Concept class and   
** all the classes derived from it: Stl, ModProg, Pylib.
** The data memebers of the Concept class are declared protected 
** to allow for the derived access through public inheritance. 
*******************************************************************/
#ifndef CONCEPTS_H
#define CONCEPTS_H
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "helpers.h"
#define SIZE 2 //std array size for input
/*******************************************************************
*************************  CONCEPT  ********************************
*******************************************************************/
/* Purpose: Concept is an ABC (Abstract Base Class) for 
** derived STL Syntax, Modern Programming, Python Libraries 
** (Stl, ModProg, PyLib) */ 
class Concept
{
    public:
	typedef std::string string;
	typedef std::ostream ostream; 

        Concept(); //default constructor 

		Concept(const std::array <string,SIZE> & about, 
				const std::multimap <string,bool> & websites);

        //Concept(const Concept & src); 
        virtual ~Concept(); //set to default vals if no dynamic memory

		/* Job: read in a website to add to existing concept
		** same for all derived classes so only implemented here. 
		** throws exception on bad input */
        void in_web(); //reading in a website 


		/***** VIRTUAL FUNCTIONS ONLY IMPLEMENTED IN DERIVED *****/
		/* Job: "selects" a website and outputs it to a external
		** data file of "selected / saved" websites */
        virtual void select(); 

		/* Job: add info to exisiting derived concept classes */
        virtual bool add_info();

		/* Job: update description of exisitng derived obj */
        virtual bool update_description();

		/* Setting = 0 makes the Concept an ABC */
        virtual void display_all() const = 0;

		/* Job: write contents of derived obj to out stream */
		virtual ostream& write_file(ostream& out) const ;
		/*****************************************************/

		/* Job: match a user searched key with concept */
		bool find(const string & key) const;

		/***********  OVERLOADED RELATIONAL OPERATORS ***********/ 
		/** Job: allow for RBtree readability & template use 
		** Arg: concept object to be compared, Ret: true/false */
        bool operator < (const Concept & source);
        bool operator > (const Concept & source);
        bool operator <= (const Concept & source);
        bool operator >= (const Concept & source);
		bool operator == (const Concept & source);

		/* Job: allow for use with cout and other output streams
		** it has to be a friend instead of memeber function 
		** Arg: out stream and concept object
		** Ret: out stream to allow for chaining  */
        //friend ostream &operator<<(std::ostream& out, Concept& op);

    protected:
        string name;         //name of concept/library/class etc 
        string description;  //what is it 
        //holds websites with a rating/useful indicator 
        std::multimap <string, bool> websites;
};
/*******************************************************************
*************************  STL  ************************************
*******************************************************************/
/* STL Syntax concepts class        Derived from Concept ABC
** PURPOSE: each Stl object represents a different class type 
** available in the standard template library, distinguished by 
** its actual class name each of the structures 'has a' container 
** of class Method objects each of the methods 'has a' description 
** of its job, args, & return type. */ 
class Stl :public Concept
{
    public:

        Stl(); //default constructor 
	
		/* Job: constructor, must pass args to ABC, 
        ** concept cannot exist on own
		** Arg: about (name & description), websites,
		** set of methods */
        Stl(const std::array <string,SIZE> & about, 
			const std::multimap <string,bool> & websites,
			const std::vector <Method> & methods);

        ~Stl(); //set to default vals since no dynamic memory     

		/* Job: "selects" a website and outputs it to a external
		** data file of "selected / saved" websites */
		void select(); 

		/* Job: add info to exisiting derived concept classes */
		/* Ret: true if updates made, else false */
        bool add_info();

		/* Job: update description of exisitng obj 
		** throw exception on bad data */
        bool update_description();

		/* Job: displays all fields
		** overloaded << throws exception on bad data */
        void display_all() const;

		/* Job: display method list contents
		** must be DOWN CAST, not an ABC function 
		** Ret: num metods printed, else exception  */
		int display_methods() const;

		/* Job: write contents of object to out stream
		** made as a member function for utility 
		** Arg: output stream variable
		** Ret: output stream variable  */
		ostream& write_file(ostream& out) const;

		/* Job: overloaded << op to allow for direct object output 
		** Arg: outstream and Stl object to output
		** Ret: ostream to allow for chaining */
        friend ostream & operator<<(std::ostream& out, const Stl& op);

		//friend ostream & write_file(ostream& out, const Stl& op);

    private: 
        std::vector <Method> methods; //contaier of methods
 		const string self {"STL Syntax"};
};

/*******************************************************************
*************************  MODPROG  ********************************
*******************************************************************/
/* Modern Programming concepts class    Derived from Concept ABC
** PURPOSE: each ModProg object is a topic in modern C++
** Each topic 'has a' container of websites with an indicator if the
** website is useful or not.  <<< multimap or pair or something 
** Each ModProg object also 'has a' string of its drawback(s) & 
** benefit(s) may also be stored as 2piece whole 
** container<string,string>^^^ */
class ModProg :public Concept
{
    public:

        ModProg(); //default constructor 

		/* Job: constructor, must pass args to ABC, 
        ** concept cannot exist on own
		** Arg: about (name & description), websites,
		** benefits/drawbacks of the Modern Prog concept */
		ModProg(const std::array <string,SIZE> & about, 
			    const std::multimap <string,bool> & websites,
                const string& good_bad);

        ~ModProg(); //set to default vals if no dynamic memory 

   		/* Job: "selects" a website and outputs it to a external
		** data file of "selected / saved" websites */
		void select(); 

		/* Job: add info to exisiting derived concept classes */
        bool add_info();

		/* Job: update description of exisitng obj 
		** throw exception on bad data */
        bool update_description();

		/* Job: displays all fields
		** overloaded << throws exception on bad data */
        void display_all() const;

		/* Job: write contents of object to out stream
		** made as a member function for utility 
		** Arg: output stream variable
		** Ret: output stream variable  */
		ostream& write_file(ostream& out) const;

		/* Job: overloaded << op to allow for direct object output 
		** Arg: outstream and ModProg object to output
		** Ret: ostream to allow for chaining */
		friend ostream& operator<<(ostream& out, const ModProg& m);

    private:
        //holds MORE?? websites with a rating/useful indicator 
        std::multimap <string, bool> websites ;
        //description of benefits & drawbacks for concept
        string good_bad; 
		const string self {"Modern Programming Concepts"};

};
/*******************************************************************
*************************  PYLIB  **********************************
*******************************************************************/
/* Python Libraries concepts class        Derived from Concept ABC
** PURPOSE: each PyLib object is a different Python Library.
** Each py library 'has a' container of class Method objects 
** availible to that library. */ 
class PyLib :public Concept
{
    public:

        PyLib(); //default constructor 

		/* Job: constructor, must pass args to ABC, 
        ** concept cannot exist on own
		** Arg: about (name & description), websites,
		** set of methods */
        PyLib(const std::array <string,SIZE> & about, 
			  const std::multimap <string,bool> & websites,
			  const std::vector <Method> & methods);

        ~PyLib(); //set to default vals if no dynamic memory 

		/* Job: "selects" a website and outputs it to a external
		** data file of "selected / saved" websites */
		void select(); 

		/* Job: add info to exisiting derived concept classes */
		/* Ret: true if updates made, else false */
        bool add_info();

		/* Job: update description of exisitng obj 
		** throw exception on bad data */
        bool update_description();

		/* Job: displays all fields
		** overloaded << throws exception on bad data */
        void display_all() const;

		/* Job: display method list contents
		** must be DOWN CAST, not an ABC function 
		** Ret: num metods printed, else exception  */
		int display_methods() const;

		/* Job: write contents of object to out stream
		** made as a member function for utility 
		** Arg: output stream variable
		** Ret: output stream variable  */
		ostream& write_file(ostream& out) const;

		/* Job: overloaded << op to allow for direct object output 
		** Arg: outstream and PyLib object to output
		** Ret: ostream to allow for chaining */
		friend ostream& operator<<(ostream& out, const PyLib& py);

		//friend ostream & write_file(ostream& out, const Stl& op);

    private: 
        std::vector <Method> methods;
		const string self {"Python Libraries"};
};

#endif
