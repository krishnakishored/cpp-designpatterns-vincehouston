
// Purpose.  No reuse

#include <iostream>
using namespace std;

class One {
   void a() { cout << "a  "; }
   void b() { cout << "b  "; }
   void c() { cout << "c  "; }
   void d() { cout << "d  "; }
   void e() { cout << "e  "; }
public:
   void execute() { a();  b();  c();  d();  e(); }
};

class Two {
   void a()  { cout << "a  "; }
   void _2() { cout << "2  "; }
   void c()  { cout << "c  "; }
   void _4() { cout << "4  "; }
   void e()  { cout << "e  "; }
public:
   void execute() { a();  _2();  c();  _4();  e(); }
};

int main( void ) {
   One first;
   first.execute();
   cout << '\n';
   Two second;
   second.execute();
   cout << '\n';
   return 0;
}

// a  b  c  d  e
// a  2  c  4  e