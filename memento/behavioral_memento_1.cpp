// Purpose.  Memento design pattern

// 1. Assign the roles of "caretaker" and "originator"
// 2. Create a "memento" class and declare the originator a friend
// 3. Caretaker knows when to "check point" the originator
// 4. Originator creates a memento and copies its state to the memento
// 5. Caretaker holds on to (but cannot peek in to) the memento
// 6. Caretaker knows when to "roll back" the originator
// 7. Originator reinstates itself using the saved state in the memento

#include "CommonInclude.h"

using std::ostream; 

class Memento {                   // 2. Create a "memento" class and
   friend class Stack;            //    declare the originator a friend
   int *items, num;
   Memento( int* arr, int n ) {
      items = new int[num = n];
      for (int i=0; i < num; i++) items[i] = arr[i]; }
public:
   ~Memento() { delete items; }
};

class Stack {                     // 1. Stack is the "originator"
   int  items[10], sp;
public:
   Stack()                 { sp = -1; }
   void     push( int in ) { items[++sp] = in; }
   int      pop()          { return items[sp--]; }
   bool     isEmpty()      { return sp == -1; }
   // 4. Originator creates a memento and copies its state to the memento
   Memento* checkPoint() {
      return new Memento( items, sp+1 );
   }
   // 7. Originator reinstates itself using the saved state in the memento
   void rollBack( Memento* m ) {
      sp = m->num-1;
      for (int i=0; i < m->num; i++) items[i] = m->items[i];
   }
   friend ostream& operator<< ( ostream& os,  const Stack& s ) {
      string buf( "[ " );
      for (int i=0; i < s.sp+1; i++) { buf += s.items[i]+48;  buf += ' '; }
      buf += ']';
      return os << buf;                   
}  };                                     
                                    
// 1. main() is the "caretaker"     

int main_memento_1( void ) 
{                       
   cout<<">>>>>>>> main_memento_1 <<<<<<<<"<<endl;   
   Stack s;                               
   for (int i=0; i < 5; i++) s.push( i ); 
   cout << "stack is " << s << endl;      
   Memento* first = s.checkPoint();       // 3. Caretaker knows when to save
   for (int i=5; i < 10; i++) s.push( i );    // 5. Caretaker holds on to memento
   cout << "stack is " << s << endl;      
   Memento* second = s.checkPoint();      // 3. Caretaker knows when to save
   cout << "popping stack: ";             // 5. Caretaker holds on to memento
   while ( ! s.isEmpty()) cout << s.pop() << ' ';  cout << endl;
   cout << "stack is " << s << endl;
   s.rollBack( second );                  // 6. Caretaker knows when to undo
   cout << "second is " << s << endl;
   s.rollBack( first );                   // 6. Caretaker knows when to undo
   cout << "first is " << s << endl;
   cout << "popping stack: ";
   while ( ! s.isEmpty()) cout << s.pop() << ' ';  cout << endl;
   delete first;  delete second;
   return 0;
}

// stack is [ 0 1 2 3 4 ]
// stack is [ 0 1 2 3 4 5 6 7 8 9 ]
// popping stack: 9 8 7 6 5 4 3 2 1 0
// stack is [ ]
// second is [ 0 1 2 3 4 5 6 7 8 9 ]
// first is [ 0 1 2 3 4 ]
// popping stack: 4 3 2 1 0

