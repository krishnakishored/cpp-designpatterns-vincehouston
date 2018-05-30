// Purpose.  Direct coupling, lots of start-up and shut-down overhead

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Image1 {
   int        id;
   static int next;
public:
   Image1() { id = next++;  cout << "   $$ ctor: "<< id << '\n'; }
   ~Image1()              { cout << "   dtor: " << id << '\n'; }
   void draw()           { cout << "   drawing image " << id << '\n'; }
};
int Image1::next = 1;

int main_proxy_1( void ) {
   Image1 images[5];
   int   i;

   cout << "Exit[0], Image[1-5]: ";
   cin >> i;
   while (i) {
      images[i-1].draw();
      cout << "Exit[0], Image[1-5]: ";
      cin >> i;
   }     
return 0;
}

//    $$ ctor: 1
//    $$ ctor: 2
//    $$ ctor: 3
//    $$ ctor: 4
//    $$ ctor: 5
// Exit[0], Image[1-5]: 2
//    drawing image 2
// Exit[0], Image[1-5]: 4
//    drawing image 4
// Exit[0], Image[1-5]: 2
//    drawing image 2
// Exit[0], Image[1-5]: 0
//    dtor: 5
//    dtor: 4
//    dtor: 3
//    dtor: 2
//    dtor: 1




// Purpose.  Proxy design pattern

// 1. Design an "extra level of indirection" wrapper class
// 2. The wrapper class holds a pointer to the real class
// 3. The pointer is initialized to null
// 4. When a request comes in, the real object is created "on first use" (aka lazy intialization)
// 5. The request is always delegated

class RealImage {
   int  id;
public:
   RealImage( int i ) { id = i;  cout << "   $$ ctor: "<< id << '\n'; }
   ~RealImage()                { cout << "   dtor: " << id << '\n'; }
   void draw()                 { cout << "   drawing image " << id << '\n'; }
};

// 1. Design an "extra level of indirection" wrapper class
class Image {
   // 2. The wrapper class holds a pointer to the real class
   RealImage* theRealThing;
   int        id;
   static int next;
public:
   Image()  { id = next++;  theRealThing = 0; }  // 3. Initialized to null
   ~Image() { delete theRealThing; }
   void draw() {
      // 4. When a request comes in, the real object is created "on first use"
      if ( ! theRealThing) theRealThing = new RealImage( id );
      // 5. The request is always delegated
      theRealThing->draw();
}  };

int Image::next = 1;

int main_proxy_2( void ) {
   Image images[5];
   int   i;

   cout << "Exit[0], Image[1-5]: ";
   cin >> i;
   while (i) {
      images[i-1].draw();
      cout << "Exit[0], Image[1-5]: ";
      cin >> i;
}  
return 0;
}

// Exit[0], Image[1-5]: 2
//    $$ ctor: 2
//    drawing image 2
// Exit[0], Image[1-5]: 4
//    $$ ctor: 4
//    drawing image 4
// Exit[0], Image[1-5]: 2
//    drawing image 2
// Exit[0], Image[1-5]: 4
//    drawing image 4
// Exit[0], Image[1-5]: 0
//    dtor: 4
//    dtor: 2
