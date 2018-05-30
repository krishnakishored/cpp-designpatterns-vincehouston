
// Purpose.  Composite and Prototype - lightweight persistence

// #pragma warning( disable : 4786 )
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
using namespace std;

class Component { 
    public:
        virtual ~Component() { }
        virtual void       traverse() = 0;
        virtual Component* clone() = 0;
        virtual void       initialize( ifstream& ) = 0;
};

namespace Factory {
   map<string,Component*> hash;
   void add( string s, Component* c ) { hash[s] = c; }
   Component* makeComponent( string name ) { return hash[name]->clone(); }
}

class Leaf : public Component {
   string value;
public:
   ~Leaf()                           { cout << 'd' << value << ' '; }
   /*virtual*/ void       traverse() { cout << value << ' '; }
   /*virtual*/ Component* clone()    { return new Leaf(); }
   /*virtual*/ void       initialize( ifstream& is ) { is >> value; }
};

class Composite : public Component {
   vector<Component*> children;
   string             value;
public:
   ~Composite() {
      cout << 'd' << value << ' ';
      for (int i=0; i < children.size(); i++)
          delete children[i];
   }
   void add( Component* c ) { children.push_back( c ); }
   /*virtual*/ void traverse() {
      cout << value << ' ';
      for (int i=0; i < children.size(); i++)
          children[i]->traverse();
   }
   /*virtual*/ Component* clone() { return new Composite(); }
   /*virtual*/ void       initialize( ifstream& is ) {
      is >> value;
      string str, delim( "/"+value );
      is >> str;
      while (str != delim) {
         add( Factory::makeComponent( str ) );
         children[children.size()-1]->initialize( is );
         is >> str;
}  }  };

//segmentation fault ToDo: fix
int main_combo_structural( void ) {
   Factory::add( "comp", new Composite() );
   Factory::add( "leaf", new Leaf() );
   ifstream is( "compositeCreate.txt" );
   string str;
   is >> str;
   Component* root = Factory::makeComponent( str );
   root->initialize( is );
   root->traverse();  cout << '\n';
   delete root;       cout << '\n';
   return 0;
}

/***
comp a leaf 1 comp b comp d leaf 8 leaf 9 /d leaf 4 comp e leaf 10
leaf 11 leaf 12 /e leaf 2 comp c leaf 5 leaf 6 leaf 7 /c /b leaf 3 /a
***/

// a 1 b d 8 9 4 e 10 11 12 2 c 5 6 7 3
// da d1 db dd d8 d9 d4 de d10 d11 d12 d2 dc d5 d6 d7 d3