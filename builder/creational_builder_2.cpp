#include"CommonHeader.h"     
#include<deque>
using std::deque;

class Array { public:                   
   virtual void traverse() = 0;         
};                     

                                        
class OneEnded : public Array {         
public:                                 
   friend class BuilderOne;             
   void traverse() {                    
      for (i=0; i < lst.size(); i++)    
         cout << lst[i] << ' ';
      cout << endl; }                   
private:                                
   vector<char> lst;   //message: implicit instantiation of undefined template 'std::__1::vector<char, std::__1::allocator<char> >'
   int i;           
};                                      
class TwoEnded : public Array {         
public:                                 
   friend class BuilderTwo;             
   void traverse() {                    
      for (i=0; i < lst.size(); i++)    
         cout << lst[i] << ' ';         
      cout << endl; }
private:                                
   deque<char> lst;   int i;            
};

class Builder { public:
   virtual void addFront( char ) = 0;
   virtual void addBack( char ) = 0;
   virtual Array& getResult()  = 0;
};
class BuilderOne : public Builder {
public:
   void addFront( char ch ) {
      one.lst.push_back( ch ); }
   void addBack( char ch ) {
      one.lst.push_back( ch ); }
   Array& getResult() {
      return one; }
private:
   OneEnded one;
};
class BuilderTwo : public Builder {
public:
   void addFront( char ch ) {
      two.lst.push_front( ch ); }
   void addBack( char ch ) {
      two.lst.push_back( ch ); }
   Array& getResult() {
      return two; }
 private:
   TwoEnded two;
};
string in[] = { "fa", "bb", "fc",
   "bd", "fe", "bf", "fg", "bh" };
class Director { //message: candidate constructor (the implicit move constructor) not viable: no known conversion from 'BuilderOne *' to 'Director' for 1st argument
public:
   Director( Builder* b ) {
      setBuilder( b ); }
   void setBuilder( Builder* b ) {
      bldr = b; }
   void construct() {
      for (int i=0; i < 8; i++)
         if (in[i][0] == 'f')
            bldr->addFront(in[i][1]);
         else if (in[i][0] == 'b')
            bldr->addBack(in[i][1]);
   }
private:
   Builder* bldr;
};
int main_builder_2( void ) 
{
  cout<<">>>>>>>> main_builder_2 <<<<<<<<"<<endl;       
   BuilderOne one;
   BuilderTwo two;
   Director dir( &one );
   dir.construct();
   one.getResult().traverse();
   dir.setBuilder( &two );
   dir.construct();
   two.getResult().traverse();
   return 0;
}
// a b c d e f g h
// g e c a b d f h