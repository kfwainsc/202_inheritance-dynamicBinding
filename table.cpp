/* table.cpp */
/*******************************************************************
**  Kendra Wainscott           CS202                 spring 2022  **
**                             Prog#3                             **
********************************************************************
********************************************************************
** This file contains the definitions of the Red Black tree (RBtree) 
** and the Node class that works with is. Since there is no 
** hierarchy, all of the data members are declared private. 
*******************************************************************/
#include "table.h"
using namespace std;
/*******************************************************************
****************************  NODE  ********************************
*******************************************************************/
/* Data members: Lcol, Rcol [Red(0)==Inside, Black(1)==Child]
				 Node* left, right    Concept* concept     */

Node::Node() :Lcol(0), Rcol(0), left(nullptr), right(nullptr),
              concept(nullptr){}

//constructor for any derived concept
Node::Node(const array <string,SIZE>& about, 
           const multimap <string, bool>& websites, 
		   const vector <Method>& method_list,
           const string& good_bad, 
		   const char type)
	 :Lcol(0), Rcol(0), left(nullptr), right(nullptr)
{
	if(type == 'S') 
		concept = new Stl(about, websites, method_list);
	else if(type == 'P')
		concept = new PyLib(about, websites, method_list);
	else if(type == 'M')
		concept = new ModProg(about, websites, good_bad);
	else{
		ALLOCATION_ERROR e; 
		throw e;
	}
}

Node::Node(const Node*& src, const char type)
{
	if(!src->concept){
		COPY_ERROR e;
		throw e;
	}
	if(type == 'S') 
		concept = new Stl();
	else if(type == 'P')
		concept = new PyLib();
	else if(type == 'M')
		concept = new ModProg();
	else{
		ALLOCATION_ERROR e; 
		throw e;
	}
	concept = src->concept;
	Lcol = Rcol = 0;
	left = right = nullptr;
}

Node::~Node()
{
	Lcol = Rcol = 0;
	if(concept) delete concept; 
	concept = nullptr;
	left = right = nullptr;
 }

/* Job: set next ptr to passed in node */
void Node::set_left(Node* new_left)
{ left = new_left; }

void Node::set_right(Node* new_right)
{ right = new_right; }

bool Node::check_left()
{ return (left != nullptr); }

bool Node::check_right()
{ return (right != nullptr); }

Node*& Node::go_left()
{ return left; }

Node*& Node::go_right()
{ return right; }

// NOT!!! Confident in these Args & return types 
void Node::rotateLeft(Node* & node){ return ; }
void Node::rotateRight(Node* & node){ return ; }

bool Node::display() const
{ 
	if(concept) concept->display_all();
	return 0;  //over load << ??
}

//bool Node::operator = (const Node & source){ return 0; }

// comparing the concepts in two NODES   
/*
bool Node::operator == (const Node* source)
{ return *concept == *(source->concept); }

bool Node::operator < (const Node* source)
{ return *concept <  source->(*concept); }
*/

//bool operator > (const Node* op1, const Node* op2)
//{ return op1 > op2; }

bool Node::operator > (const Node* source)
{ return *concept >  *(source->concept); }

/*
bool Node::operator <= (const Node & source)
{ return *concept <= source.*concept; }

bool Node::operator >= (const Node* source)
{ return *concept >= source->concept; }
*/

/*
// comparing a concept to a concept in a node   
bool Node::operator < (const Concept & src)
{ return *concept < src; }

bool Node::operator > (const Concept & src)
{ return *concept > src; }
*/

/*******************************************************************
*************************  RBTREE  *********************************
*******************************************************************/
RBtree::RBtree() :root(nullptr) {}

//RBtree::RBtree(const RBtree & src){}

RBtree::~RBtree()
{ 
	remove_all(); 
	root = nullptr;		
}
/*
void RBtree::insert(const Node* node, const char type)
{
	if(!root){ //empty tree
		cout <<"Root"<<endl;
		root = new Node(node, type);
		return;
	}
	//calls to recursive insert 
	else if(root > node)
		return insert(root->go_left(), node, type);
	return insert(root->go_right(), node, type);
}
void RBtree::insert(Node* & root, const Node* node, const char type)
{
	cout <<"recur"<<endl;

	if(!root->go_left() && !root->go_right())//at leaf, insert
	{
		Node* new_node = new Node(node, type);
		if(root > node)
			root->set_left(new_node);	
		else 
			root->set_right(new_node);	

		if(!new_node){
			ALLOCATION_ERROR e;
			throw e;
		}return;
	}
	else if(root > node)
		return insert(root->go_left(), node, type);
	return insert(root->go_right(), node, type);
}
*/

void RBtree::F_insert(const std::array<string,SIZE>& about, 
                      const std::multimap<string,bool>& web, 
			          const std::vector <Method>& m_list,
                      const std::string& gb, const char type)
{
	if(!root){ //empty tree
		root = new Node(about, web, m_list, gb, type);
		return;
	}//at leaf, insert
	else if(!root->check_left() && !root->check_right())
	{
		Node* node = new Node(about, web, m_list, gb, type);
		if(root > node)
			root->set_left(node);	
		else 
			root->set_right(node);	
		return;
	}
	else{//recursive call
		Node* node = new Node(about, web, m_list, gb, type);
		if(root > node)
			return F_insert(root->go_left(), node);
		return F_insert(root->go_right(), node);
	}
}

void RBtree::F_insert(Node* & root, Node* & node)
{
	if(!root) return ;

	if(!root->check_left() && !root->check_right())//at leaf, insert
	{
		if(root > node)
			root->set_left(node);	
		else 
			root->set_right(node);	

		if(!node){
			ALLOCATION_ERROR e;
			throw e;
		}return;
	}
	else if(root > node)
		return F_insert(root->go_left(), node);
	return F_insert(root->go_right(),node);
}

//wrapper to print tree
int RBtree::display() const
{
	if(!root) return 0; //empty tree

	int count {0};
	//in order traversal recur 	
	if(root->check_left()) 
		count = display_inorder(root->go_left());

	root->display();

	if(root->check_right()) 
        count += display_inorder(root->go_right());	
	return count;
}

int RBtree::remove_all()
{
	if(!root) return 0; 
	return remove_all(root);
}

bool RBtree::search(string & key)
{ return 0; }   

void RBtree::balance(/* args */){}

int RBtree::display_inorder(Node* root) const
{
	if(!root) return 0;
	int count{0};

	if(root->check_left()) 
		display_inorder(root->go_left());

	count = root->display() +1;	

	if(root->check_right()) return 0;
		display_inorder(root->go_right());	
	return count;
}

int RBtree::remove_all(Node* & root)
{
	if(!root) return 0;

	int count{0};
	count = remove_all(root->go_left()) + remove_all(root->go_right());

	delete root;
	root = nullptr;
	return count +1;
}

