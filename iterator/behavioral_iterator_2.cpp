
// Purpose.  Iterator using operators instead of methods
//
// Discussion.  John Lakos suggests the GOF and STL iterator interfaces are:
// error-prone (possibility of misspelling method names), clumsy, and require
// too much typing.  This design uses nothing but "intuitive" operators.
// Notice also that no createIterator() was specified.  The user creates these
// iterators as local variables, and no clean-up is necessary.
#include "CommonInclude.h"    
class Stack1 {
   int items[10];
   int sp;
public:
   friend class StackIter1;
   Stack1()             { sp = -1; }
   void push( int in ) { items[++sp] = in; }
   int  pop()          { return items[sp--]; }
   bool isEmpty()      { return (sp == -1); }
};

class StackIter1 {
   const Stack1& stk;
   int index;
public:
   StackIter1( const Stack1& s ) : stk( s ) { index = 0; }
   void operator++() { index++; }
   bool operator()() { return index != stk.sp+1; }
   int  operator*()  { return stk.items[index]; }
};

bool operator==( const Stack1& l, const Stack1& r ) {
   StackIter1 itl( l ), itr( r );
   for ( ; itl(); ++itl, ++itr)
      if (*itl != *itr) break;
   return ! itl() && ! itr();
}

int main_iterator_2A( void ) 
{
    cout<<">>>>>>>> main_iterator_2A <<<<<<<<"<<endl;  
   Stack1  s1;   int  i;
   for (i=1; i < 5; i++) s1.push(i);
   Stack1  s2( s1 ), s3( s1 ), s4( s1 ), s5( s1 );
   s3.pop();       s5.pop();
   s4.push( 2 );   s5.push( 9 );
   cout << "1 == 2 is "<< (s1 == s2) << endl;
   cout << "1 == 3 is "<< (s1 == s3) << endl;
   cout << "1 == 4 is "<< (s1 == s4) << endl;
   cout << "1 == 5 is "<< (s1 == s5) << endl;
   return 0;
}

// 1 == 2 is 1
// 1 == 3 is 0
// 1 == 4 is 0
// 1 == 5 is 0




// Purpose.  Iterator using the Java interface
//
// Discussion.  Java's standard collection classes have a much leaner inter-
// face.  Their next() methods combine the next() and currentItem() methods.



class StackIter;
class Stack {
   int items[10];
   int sp;
public:
   friend class StackIter;
   Stack()             { sp = -1; }
   void push( int in ) { items[++sp] = in; }
   int  pop()          { return items[sp--]; }
   bool isEmpty()      { return (sp == -1); }
   StackIter* iterator() const;
};

class StackIter {
   const Stack* stk;
   int index;
public:
   StackIter( const Stack* s ) { stk = s;  index = 0; }
   int  next()                 { return stk->items[index++]; }
   bool hasNext()              { return index != stk->sp+1; }
};

StackIter* Stack::iterator() const { return new StackIter( this ); }

bool operator==( const Stack& l, const Stack& r ) {
   StackIter* itl = l.iterator();
   StackIter* itr = r.iterator();
   while (itl->hasNext())
      if (itl->next() != itr->next()) {
         delete itl;   delete itr;
         return false;
      }
   bool ans = (! itl->hasNext()) && ( ! itr->hasNext());
   delete itl;   delete itr;
   return ans;
}

int main_iterator_2B( void ) 

{
    main_iterator_2A();
    cout<<">>>>>>>> main_iterator_2B <<<<<<<<"<<endl;  
   Stack  s1;   int  i;
   for (i=1; i < 5; i++) s1.push(i);
   Stack  s2( s1 ), s3( s1 ), s4( s1 ), s5( s1 );
   s3.pop();       s5.pop();
   s4.push( 2 );   s5.push( 9 );
   cout << "1 == 2 is "<< (s1 == s2) << endl;
   cout << "1 == 3 is "<< (s1 == s3) << endl;
   cout << "1 == 4 is "<< (s1 == s4) << endl;
   cout << "1 == 5 is "<< (s1 == s5) << endl;
   return 0;
}

// 1 == 2 is 1
// 1 == 3 is 0
// 1 == 4 is 0
// 1 == 5 is 0
