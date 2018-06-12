// Purpose.  Triple dispatch (within a single hierarchy)
// 
// Discussion.  It would be nice if C++ supported creating a function like:
// "processCombine( virtual Binary& first, virtual Binary& second, virtual
// Binary& third )".  While not directly supported, we can simulate this kind
// of capability by: calling combine() on the first object to resolve its
// type, then calling combine() on the second object to resolve its type,
// then calling combine() on the third object to resolve its type.  We
// "remember" the type information we have "discriminated" at each stage by
// juggling the three objects through 2 increasingly type-specific parameter
// slots.

#include "CommonInclude.h"

class Zero;
class One;

class Binary {
public:
   // First dispatch
   virtual void combine( Binary& second, Binary& third ) = 0;

   // Second dispatch
   virtual void combine( Binary& third, Zero& first ) = 0;
   virtual void combine( Binary& third, One&  first ) = 0;

   // Third dispatch
   virtual void combine( Zero& first, Zero& second ) = 0;
   virtual void combine( Zero& first, One&  second ) = 0;
   virtual void combine( One& first,  Zero& second ) = 0;
   virtual void combine( One& first,  One&  second ) = 0;
};

class Zero : public Binary {
public:
   void combine( Binary& second, Binary& third ) {
      second.combine( third, *this ); }

   void combine( Binary& third, Zero& first ) {
      third.combine( first, *this ); }
   void combine( Binary& third, One& first ) {
      third.combine( first, *this ); }

   void combine( Zero& first, Zero& second );
   void combine( Zero& first, One&  second );
   void combine( One&  first, Zero& second );
   void combine( One&  first, One&  second );

   void doZero() { cout << "0  "; }
};

class One : public Binary {
public:
   void combine( Binary& second, Binary& third ) {
      second.combine( third, *this ); }

   void combine( Binary& third, Zero& first ) {
      third.combine( first, *this ); }
   void combine( Binary& third, One& first ) {
      third.combine( first, *this ); }

   void combine( Zero& first, Zero& second );
   void combine( Zero& first, One&  second );
   void combine( One&  first, Zero& second );
   void combine( One&  first, One&  second );

   void doOne() { cout << "1  "; }
};

void Zero::combine( Zero& first, Zero& second ) {
   first.doZero();  second.doZero();  doZero();  cout << endl; }
void Zero::combine( Zero& first, One&  second ) {
   first.doZero();  second.doOne();   doZero();  cout << endl; }
void Zero::combine( One&  first, Zero& second ) {
   first.doOne();   second.doZero();  doZero();  cout << endl; }
void Zero::combine( One&  first, One&  second ) {
   first.doOne();   second.doOne();   doZero();  cout << endl; }

void One::combine( Zero& first, Zero& second ) {
   first.doZero();  second.doZero();  doOne();  cout << endl; }
void One::combine( Zero& first, One&  second ) {
   first.doZero();  second.doOne();   doOne();  cout << endl; }
void One::combine( One&  first, Zero& second ) {
   first.doOne();   second.doZero();  doOne();  cout << endl; }
void One::combine( One&  first, One&  second ) {
   first.doOne();   second.doOne();   doOne();  cout << endl; }

void processCombine( Binary& first, Binary& second, Binary& third ) {
   first.combine( second, third );
}

int main_visitor_12( void ) 
{
    cout<<">>>>>>>> main_visitor_12 <<<<<<<<"<<endl; 
   Zero myZero;
   One myOne; 
   Binary*  list[2] = { &myZero, &myOne }; // message: taking the address of a temporary object of type 'A' [-Waddress-of-temporary]

   // Run through permutations
   for (int i=0; i < 2; i++)
      for (int j=0; j < 2; j++)
         for (int k=0; k < 2; k++)
            processCombine( *list[i], *list[j], *list[k] );
 return 0;
}

// 0  0  0  
// 0  0  1  
// 0  1  0  
// 0  1  1  
// 1  0  0  
// 1  0  1  
// 1  1  0  
// 1  1  1  