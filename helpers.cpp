/* helpers.h */
/*******************************************************************
**  Kendra Wainscott           CS202                 spring 2022  **
**                             Prog#3                             **
*******************************************************************/
/* This file is the implementation of the Method class as well as
** the Helper class. The Method class is used in the derived 
** concepts. The Helper class is a utility class use to get and
** error check input from the user. There are also a few General
** functions implemented at the end to print menus.
*******************************************************************/
#include "helpers.h"
using namespace std;
/*******************************************************************
*************************  METHOD  *********************************
*******************************************************************/
/* Data Memebers: (strings) selfClass, funcName, job, args, ret */ 

//default constructor 		
Method::Method():selfClass("null"), funcName("null"), job("null"), 
                 args("null"), ret("null") {} 

Method::Method(vector<string> & input) 
	   :selfClass(input.at(0)), funcName(input.at(1)), 
        job(input.at(2)), args(input.at(3)), ret(input.at(4)) {} 

Method::~Method() //no dynamic memory, reset to defaul vals 
{ selfClass = funcName = job = args = ret = "null"; }

bool Method::is_member(string & key)
{//invalid key throw INPUT ERROR struct 
	if(key == "null"){
		INPUT_ERROR e;
		throw e;
	}return selfClass == key;
}

void Method::display_name()
{ 
	if(funcName == "null"){
		INPUT_ERROR e;
		throw e;
	}cout <<"--  "<< funcName <<"  --";
}

void Method::display_all()
{
	if(funcName == "null"){
		INPUT_ERROR e;
		throw e;
	}cout << *this;
}

// cannot be a member function in order to use set 
bool operator < (const Method & op1, const Method & op2)
{ return op1 < op2; }

//over loaded member function op 
bool Method::operator < (const Method & source)
{
	if(selfClass != source.selfClass)
		return selfClass < source.selfClass;
	return funcName < source.funcName; 
}

bool Method::operator > (const Method & source)
{
	if(selfClass != source.selfClass)
		return selfClass > source.selfClass;
	return funcName > source.funcName; 
}

bool Method::operator <= (const Method & source)
{
	if(selfClass != source.selfClass)
		return selfClass <= source.selfClass;
	return funcName <= source.funcName;
}

bool Method::operator >= (const Method & source)
{
	if(selfClass != source.selfClass)
		return selfClass >= source.selfClass;
	return funcName >= source.funcName;
}

bool Method::operator == (const Method & source)
{ 
	if(selfClass != source.selfClass)
		return false;
	return funcName == source.funcName; 
}

ostream &operator <<(ostream& out, Method& op)
{
	if(op.funcName == "null"){
		INPUT_ERROR e;
		throw e;
	}out <<"--  "<< op.funcName <<"  ----------------\nPurpose: "
		  << op.job <<"\nParameters: " << op.args << "\nReturns: " 
          << op.ret <<"\nMethod of: "<< op.selfClass <<"\n";
	return out; 
}
/*******************************************************************
*************************  HELPER  *********************************
*******************************************************************/
// min-max accepted rage, if invaild defaults
int Helper::get_answer(int min, int max, int defaultX) const
{
    int answer {defaultX};
    cout <<"ANSWER: ";
    cin  >> answer;
    cin.ignore(100, '\n'); //ignore extra input
    if(answer > max || answer < min) return defaultX;
    return answer; 
}

string Helper::get_str(const string& mess, const string& dfalt)const
{
	string output {dfalt};
	try{
		cout << mess;
		cin  >> output;
		return output;
	}catch(...){
		return dfalt;
	}
}

void Helper::stl_py_input(string type, array<string,SIZE>& about, 
	                      multimap<string,bool>& web,
				          vector<Method>& methods_list) {
	string defaultStr = "null";
	//get stl data type OR python library name & descript
	string message {"Enter " + type +" name: "};
	about.at(0) = get_str(message, defaultStr);
	message = "Enter a description: "; 
	about.at(1) = get_str(message, defaultStr);
	
	if(about.at(0) == "null" || about.at(1) == "null"){
		INPUT_ERROR e;
		throw e;
	}
	read_web(web);//get resource website 
	//choice to add methods to concept 
	cout <<"Add Methods? yes(1)| no(0)\n";
	if(get_answer(0,1,0))
		read_m_list(methods_list, FIELDS);
}

void Helper::modProg_input(string type, array<string,SIZE>& about, 
	                       multimap<string,bool>& web, string& g_b)
{
	string defaultStr = "null";
	//get stl data type OR python library name & descript
	string message {"Enter " + type +" name: "};
	about.at(0) = get_str(message, defaultStr);
	message = "Enter a description: "; 
	about.at(1) = get_str(message, defaultStr);
	
	if(about.at(0) == "null" || about.at(1) == "null"){
		INPUT_ERROR e;
		throw e;
	}
	read_web(web);//get resource website 
	//enter good/bad
	message = "Enter the benefits and drawbacks of " + type;	 
	g_b = get_str(message, defaultStr);
}

void Helper::read_web(std::multimap <string,bool> & websites)
{
	string str{"Enter website resource: "};
	string defaultStr{"null"};	

	str = get_str(str, defaultStr);
	if(str == "null"){
		INPUT_ERROR e;
		throw e;
	}
	cout << "Is this site helpful? yes(1) | no(0)\n";
	int rate = get_answer(1,0,1); 
	websites.insert({str,rate});
}


void Helper::read_method(vector<Method>& method_list, const int fields)
{
	vector<string> methodData(fields);

	string dfault {"null"};
	methodData.at(0) = get_str("Method Name: ",dfault);
	methodData.at(1) = get_str("Purpose: ",dfault);
	methodData.at(2) = get_str("Argument(s): ",dfault);
	methodData.at(3) = get_str("Return Type: ",dfault);
	for(int i=0; i<fields; ++i)
	{
		if(methodData.at(i) == dfault){
			INPUT_ERROR e;
			throw e; }
	}//create a new method and add to list
	Method method(methodData);
	method_list.push_back(method);
}

void Helper::read_m_list(vector<Method>& mthd_list, const int fields)
{
	int done{0};
	while(!done)
	{
		read_method(mthd_list, fields);
		cout <<"Add another method? yes(1) | no(0)\n";
		done = get_answer(0,1,0);
	}
}
//int Helper::write_file(ostream & out)
/*******************************************************************
*************************  GENERAL  ********************************
*******************************************************************/
bool print_banner()
{
    for(int i=0; i<2; ++i){
    cout<<"***************************************************"
        <<"*******************************"<<endl;}
    cout<<"**************************  MODERN C++ DATABASE "
        <<" ********************************"<<endl;
    for(int i=0; i<2; ++i){
    cout<<"***************************************************"
        <<"*******************************"<<endl;}
    cout<<"Please choose from the following options:"<<endl;
    return true;
}

bool main_menu()
{
    cout <<"\n==========  MAIN MENU OPTIONS  ============\n"
		 <<"1) STL Syntax\n2) Modern Programming Concepts\n"
		 <<"3) Python Libraries\n4) Display All\n5) Search item\n"
		 <<"6) Delete All\n0) Quit\n\n";
    return 1;
}

bool sub_menu()
{
    cout <<"\n========== Supported Functions ============" 
		 <<"\n1) Write catagory to file\n2) Add an Item "
		 <<"\n3) Display ALL \n4) Add a website"
		 <<"\n0) Main Menu \n\n";
    return 1;
}
