/* main.cpp */
/*******************************************************************
**  Kendra Wainscott           CS202                 spring 2022  **
**                             Prog#3                             **
*******************************************************************/
/* The purpose of this program is to read in, store, add too and 
** output data on Modern Programming Languages. An inheritance 
** higherarchy and dynamic binding is used for the derived classes
** STL Syntax (Stl), Modern Programming Concepts (ModProg), and 
** Python Libraries (PyLib) can be stored in the same datastructure
** which is a Red Black tree (RBtree). 
** The program supports user input, modification, and output (both 
** printing to screen or an external file) of the derived Concept
** classes data  */
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <memory>
#include <list>
#include <algorithm>
#include "helpers.h"
#include "concepts.h"
#include "table.h"
using namespace std;

#define SIZE 2 //std array size for concept 'about' input
#define FIELDS 5 //num of fields in method object
#define MIN_SIZE 10
int main(int argc, char** argv)
{
    // prog not run with input file
    if(argc != 2){ 
		FILE_ERROR e; 
		throw e;
	}// instream variable 
    char* datafile = argv[1];
    ifstream inDatafile(datafile);
    if(!inDatafile){ 
		FILE_ERROR e; 
		throw e;
	}// create outstream & file to output to 
    ofstream outFile;
    outFile.open("prog_output.txt");
    if(!outFile){ 
		FILE_ERROR e; 
		throw e;
	}

	RBtree tree; //red-black tree for concept ptrs
	list<Concept*> basePtrs;	

	string str1;                       //input string for datafile
	array<string,SIZE> about;          //name & description
	multimap<string, bool> websites;   //websites & ratings
	vector<string> methodData(FIELDS); //fields for 1 method obj
	vector<Method> m_list;             //list of method objects

	while(inDatafile)//start add concept loop
	{
	char type = inDatafile.peek();
	getline(inDatafile,str1);//ignore * line 

	getline(inDatafile,about.at(0)); //name
	getline(inDatafile,about.at(1)); //description 	
	getline(inDatafile,str1);        //website
	websites.insert({str1,true});
	if(type == 'S' || type == 'P')
	{// stl & py methods + push
		while(inDatafile.peek() != '*')
		{//start method List read in 
			for(int i=0; i<FIELDS; ++i) //read fields for 1 method
			getline(inDatafile, methodData.at(i));
		getline(inDatafile,str1);  //ignore format line
		Method method(methodData); //create 1 method
		m_list.push_back(method);  //insert into method list
		}//end of 1 method loop, read till new concept type  

		getline(inDatafile,str1);           //ignore * line 
		sort(m_list.begin(), m_list.end()); //alpha order methods
		//add Stl of PyLib	
		if(type == 'S')
		basePtrs.push_back(new Stl(about, websites, m_list));
		else
		basePtrs.push_back(new PyLib(about, websites, m_list));
		//rb tree insert
		tree.F_insert(about, websites, m_list, str1, type);
	}
	else{// ModProg add
		getline(inDatafile,str1);
		if(type == 'M')
		{
		basePtrs.push_back(new ModProg(about, websites, str1));
		tree.F_insert(about, websites, m_list, str1, type);
		}
	}
	websites.clear();
	m_list.clear();
	}//end of add concept loop 

	inDatafile.close(); //close input file
	Helper h; // helper to get and error check user input

	/**** USER INTERFACE *******/
	int done{false}, choice{0};
	print_banner();

	while (!done) //start user interface 
    {
	main_menu();
	choice = h.get_answer(0,8,0);

	if(choice == 0){ 
		done = true;	
	}
	else if(choice == 1)//STL Syntax
	{
		cout << "\nSTL" <<endl;
		sub_menu();
		choice = h.get_answer(0,4,0);

		if(choice == 1) {
		for( auto base : basePtrs ){ //write to file
			Stl* stl = dynamic_cast<Stl*>(base);
			if(stl != nullptr)
				stl->write_file(outFile);
		}
		}
		if(choice == 2)	{ //add stl item 
		string type {"STL"};
		h.stl_py_input(type, about, websites, m_list);
		basePtrs.push_back(new Stl(about, websites, m_list));
		}
		if(choice == 3) {
		for( auto base : basePtrs ){ //display all
			Stl* stl = dynamic_cast<Stl*>(base);
			if(stl != nullptr)
				base->display_all(); 
		}
		}
	}
	else if(choice == 2)//Modern Prog
	{
		cout << "\nMod Prog" <<endl;
		sub_menu();
		choice = h.get_answer(0,4,0);

		if(choice == 1) { //write to file
		for( auto base : basePtrs ){
			ModProg* mod = dynamic_cast<ModProg*>(base);
			if(mod != nullptr)
				mod->write_file(outFile);
		}
		}
		if(choice == 2) { //add new Mod Prog
		h.modProg_input("ModProg", about, websites, str1);
		basePtrs.push_back(new ModProg(about, websites, str1));
		}
		if(choice == 3) {
		for( auto base : basePtrs ){ //display all
			ModProg* mod = dynamic_cast<ModProg*>(base);
			if(mod != nullptr)
				base->display_all(); 
		}
		}
		if(choice == 4) { //add website
		}
	}
	else if(choice == 3)//Python Lib
	{
		cout << "\nPyLib" <<endl;
		sub_menu();
		sub_menu();
		choice = h.get_answer(0,4,0);
		if(choice == 1) {
		for( auto base : basePtrs ){ //write to file
			PyLib* pyPtr = dynamic_cast<PyLib*>(base);
			if(pyPtr != nullptr)
				pyPtr->write_file(outFile);
		}
		}
		if(choice == 2) { //add pyLib item 
		string type {"Python Lib"};
		h.stl_py_input(type, about, websites, m_list);
		basePtrs.push_back(new PyLib(about, websites, m_list));
		}
		if(choice == 3) {
		for( auto base : basePtrs ){ //display all
			PyLib* pyPtr = dynamic_cast<PyLib*>(base);
			if(pyPtr != nullptr)
				base->display_all(); 
		}
		}
	}
	else if(choice == 4)//Display all
	{
		for( auto base : basePtrs )
			base->display_all(); 
	}
	else if(choice == 5) //search for an item
	{
		string key;
		cout <<"\nenter Key to search for" 
			 <<"\n(example 'ARRAY', 'EXCEPTIONS')\nKey: ";
		cin  >> key;	
		for( auto base : basePtrs ) {	
			if( base->find(key))
				base->display_all();
		}
	}
	else if(choice == 6)//Delete all
	{
		cout << "Clear All" <<endl;
		basePtrs.clear();
	}
	//else invalid menu option, default quit
	}//end while !done

    outFile.close();//close output file
	return 0;
}

