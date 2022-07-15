/* table.h */
/*******************************************************************
**  Kendra Wainscott           CS202                 spring 2022  **
**                             Prog#3                             **
*******************************************************************/
/* This file contains the definitions of Red Black tree (Rbtree)
** and the Node class that goes along with it. Since there is no 
** hierarchy, all of the data members are declared private.
** The RBtree is the major data structure used in this program and
** through the Concept's use of dynamic binding it is capable of 
** holding any of the three derived types of concepts. 
*******************************************************************/
#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <array>
#include <vector>
#include "concepts.h"
/*******************************************************************
****************************  NODE  ********************************
*******************************************************************/
/* Node for Red-Black Tree        
** PURPOSE: container for any of the 3 derived Concept classes. 
** Nodes have a pointer to the ABC Concept to allow for upcasting 
** This allows the RBTree to access the correct fuction for 
** any of the 3 drived types. */
class Node
{
    public:
	typedef std::string string;

        Node(); //default constructor

		/* Job: constructor for any derived concept
		** Arg: about, website map, methods for Std & pyLib
		** good/bad for ModProg, char to note derived type
		** throws exception if invalid type */ 
		Node(const std::array<string,SIZE>& about, 
             const std::multimap<string,bool>& web, 
			 const std::vector <Method>& method_list,
             const std::string& goodBad, const char type);

		 //cc since has raw ptrs
        Node(const Node*& src, const char type);

        ~Node(); //release dynamic memory, set fault vals

		/* Job: set next ptr to passed in node */
		void set_left(Node* new_left);
		void set_right(Node* new_right);
	

		/* Job: get/check for ptr to next node
		** Returns: next node, else nullptr */ 
        bool check_left();
		bool check_right();

		/* Job: get/check for ptr to next node
		** Returns: next node, else nullptr */ 
        Node*& go_left();
		Node*& go_right();

        // NOT!!! Confident in these Args & return types 
        void rotateLeft(Node* & node);
        void rotateRight(Node* & node);

		/* Job: display all data in node,
		** Ret: success else excpeption  */
        bool display() const; 

		/* Node to Node Overloaded Relational Operators 
		** Job: allow for class tb use with templates
        ** and readability in the RBtree class
		** Arg: node object to be compared
		** Ret: true/false  */
        bool operator == (const Node* source);
        bool operator < (const Node* source);
        bool operator > (const Node* source);
//        bool operator <= (const Node & source);
 //       bool operator >= (const Node & source);

//bool operator > (const Node* op1, const Node* op2); 
		/* Node to Concept Overloaded Relational Ops
		** Job: allow for Concept objects to be 
		** compared within a node
		** Arg: concept object to be compared
		** Ret: true/false  */
		//bool operator < (const Concept & src);
		//bool operator > (const Concept & src);


    private:
        //two color flags to avoid look ahead 
        //Red (0) == Inside, Black (1) == Child
        int Lcol, Rcol; 
        Node* left;
		Node* right; 
        Concept* concept;
	
        //Do I need a parent pointer???
};
/*******************************************************************
*************************  RBTREE  *********************************
*******************************************************************/
/* Red-Black Tree Balanced Tree
** Balanced Search Tree (simulates 2-3-4 tree)
** PURPOSE: holds a collection of the 3 different types 
** (Stl, ModProg, PyLib) of derived Concept class objects. 
** An instance of a RBtree can hold any of the concept types in 
** the same tree object */
class RBtree
{
    public:
		typedef std::string string;

        RBtree(); //default
        ~RBtree(); //destructor 

        /* Job: wrapper, insert new node into tree
        ** Arg: new data
        ** Ret: none - throw exception on failure */
        void F_insert(const std::array<string,SIZE>& about, 
                    const std::multimap<string,bool>& web, 
			        const std::vector <Method>& method_list,
                    const std::string& goodBad, const char type);

        /* Job: insert new node into tree
        ** Arg: new node with concept data
        ** Ret: none - throw exception on failure */
		void F_insert(Node* & root, Node* & node);

        //void insert(const Node* node, const char type);

        /* Job: wrapper to print tree
        ** Ret: num of nodes displayed */
        int display() const;

        /* Job: wrapper to delete entire tree
        ** Ret: num of nodes deleted */ 
        int remove_all();

        //need in order to do anything with exsisting Concepts
        /* Job: locate/access desired item 
        ** Arg: key, possibly need 2?? */
        bool search(string & key);   

    private:
		Node* root;

        /* Job: recursively insert new node into tree
        ** Arg: root of tree, node with concept ptr
        ** Ret: none - throw exception on failure */
//        void insert(Node* & root, const Node* node, const char type);

        /* Job: rebalance tree after insert
        ** Arg:
        ** Ret: none - throw exception on failure */
        void balance(/* args */);

        /* Job: traver tree inorder and print 
        ** Arg: root of tree
        ** Ret: num of nodes displayed  */
        int display_inorder(Node* root) const;

        /* Job: delete entire list
        ** Arg: root of tree
        ** Ret: num of nodes deleted  */
        int remove_all(Node* & root);

};
/*******************************************************************
*******************************    ********************************
*******************************************************************/

#endif
