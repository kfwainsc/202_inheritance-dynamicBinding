/* helpers.h */
/*******************************************************************
**  Kendra Wainscott           CS202                 spring 2022  **
**                             Prog#3                             **
*******************************************************************/
/* This file contains the definitions for Method and Helper classes.
** Since there is no hierarchy, all of the data members are declared 
** private.The Helper class is a utility class use to get and error 
** check input from the user, print menus etc. The derived concept 
** classes have a 'has a' relationship with the Method class. 
** There are also headers for a few General functions to print 
** menus as well as the Exception Handling structs.
*******************************************************************/
#ifndef HELPERS_H
#define HELPERS_H
#include <iostream>
#include <vector>
#include <map>
#include <array>
/*******************************************************************
*************************  METHOD  *********************************
*******************************************************************/
/* Method 
** PURPOSE: each Method object represents a particular class 
** function this can be from any language or library. Each method 
** 'has a' job description, list of its arguments and return type */
class Method
{
	typedef std::string string;
	typedef std::ostream ostream;
    public: 
	    //construct & destructors
		Method();
		Method(std::vector<string> & input);
		~Method();

		/* Job: check if method is a memeber of passed in class
		** Arg: name of class to compare with selfClass
		** Ret: true match, else false, exception if invalid key*/
		bool is_member(string & key);

		/* Job: display name of the method and class only
		** throw exception if empty */
		void display_name();

		/* Job: display all info
		** Ret: void - throws exception if empty */
		void display_all();

		/*   Overloaded Relational Operators 
		** Job: allow for class tb use with templates
		** Arg: concept object to be compared
		** Ret: true/false  */
        bool operator < (const Method & source);
        bool operator > (const Method & source);
        bool operator <= (const Method & source);
        bool operator >= (const Method & source);
		bool operator == (const Method & source);

		/* Job: allow for cout and other outstream ops
		** Arg: outstream and Method obj
		** Ret: outstream to allow for chaining */
		friend ostream &operator <<(ostream & out, Method & op);

    private: 
		string selfClass;//class method belongs to
		string funcName;//function/method name  
		string job;   //purpose of method
		string args; //function parameters 
		string ret; //return type of method
};
// must be overloaded as a NONmeber in order to use std set
bool operator < (const Method & op1, const Method & op2);
/*******************************************************************
********************  EXCEPTION HANDELING  *************************
*******************************************************************/
struct ALLOCATION_ERROR // new operation failed 
{}; //alloc_error

struct COPY_ERROR //cc error
{}; //copy_error; 

struct DISPLAY_ERROR //general display or menu error
{}; //display_error;

struct FILE_ERROR //invalid File usage or fstream error
{}; //file_error;

struct INPUT_ERROR 
{}; //input_error; //invaid user input

struct OPERATOR_ERROR //overloaded operator errors 
{}; //operator_error;

/*******************************************************************
*************************  HELPER  *********************************
*******************************************************************/
/* Job: reads in user input and accepted rage, if invaild defaults
** Arg: min and max of accpeted range, default for bad input 
** Ret: user input or defaultX */
class Helper
{
	#define SIZE 2   //std array size for concept 'about' input
	#define FIELDS 5 //num of fields in method object
	typedef std::string string;

    public:
		/* Job: get, error check, return an integer from user
		** Arg: min/max acceptable range, default return if error 
		** Ret: user input or default  */
		int get_answer(int min, int max, int defaultX) const;

		/* Job: get, error check, return a string from user
		** Arg: input message, default return if error 
		** Ret: user input or default  */
		string get_str(const string& mes, const string& dfalt)const;

		/* Job: get & error check input for Stl or PyLib objects
		** Arg: type Stl/PyLib, about array, websites, method list
		** throws exception on bad input*/
		void stl_py_input(string type, std::array<string,SIZE>& 
						  about, std::multimap<string,bool>& web,
				          std::vector<Method>& method);

		/* Job: get & error check input for ModProg objects
		** Arg: type ModProg, about arr, websites, good_bad desript
		** throws exception on bad input*/
		void modProg_input(string type, std::array<string,SIZE>&
						   about, std::multimap<string,bool>& web,
				           string& good_bad);

		/* Job: read in a website from user, exception bad input
		** Arg: multimap of websites and helful/not rating */
		void read_web(std::multimap<string,bool>& web);  

		/* Job: read in all fields for a method from user
		** push new method onto list, bad input throw exception
		** Arg: list of methods, num of fields in a method */
		void read_method(std::vector<Method>& methods_list,
                          const int fields);

		/* Job: read methods from user till done
        ** bad input throws exception
		** Arg: list of methods, num of fields in a method */
		void read_m_list(std::vector<Method>& method_list,
                         const int fields);

};
/*******************************************************************
*************************  GENERAL  ********************************
*******************************************************************/
bool print_banner();
bool main_menu();
bool sub_menu();

#endif
