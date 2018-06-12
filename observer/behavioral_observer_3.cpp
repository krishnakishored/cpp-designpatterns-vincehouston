#include "CommonInclude.h"

// Purpose.  Observer and Mediator demo
// 
// Observer - 1. Sender is coupled to a Receiver interface
//            2. Receivers register with Sender
//            3. Sender broadcasts (in the blind) to all Receivers
// 
// Mediator - 4. Sender(s) has handle to Mediator
//            5. Mediator has handle to Receiver(s)
//            6. Sender(s) sends to Mediator
//            7. Mediator sends to Receiver(s)

// void gotoxy( int, int );
void gotoxy( int x, int y ){ //TODO:
      // cout<<"\nGOTO x: "<<x<<",y: "<<y<<endl;
    for(int i = x;i<0;i--) cout<<" "<<endl;
    for(int i = y;i<0;i--) cout<<" "<<endl;
    
}

class Observer { public: virtual void update( int ) = 0; };

class Mediator 
{
   vector<Observer*> groups[3];         // 1. Sender is coupled to an interface
public:
   enum Message { ODD, EVEN, THREE };   // 1. Sender is coupled to an interface
   void attach( Observer* o, Message type ) { groups[type].push_back( o ); }
   void disseminate( int num )
    {
         if (num % 2 == 1)  // odd      // 3,7. Sender/Mediator broadcasts
            for (int i=0; i < groups[0].size(); i++) groups[0][i]->update(num);
         else               // even
            for (int i=0; i < groups[1].size(); i++) groups[1][i]->update(num);
         if (num % 3 == 0)  // /3
            for (int i=0; i < groups[2].size(); i++) groups[2][i]->update(num);
    }  
};

class OddObserver : public Observer 
{
   int col, row;
public:
   OddObserver( Mediator& med, int c ) 
   {
      col = c;           
      row = 3;
      gotoxy( col, 1 );  
      cout << "Odd";
      gotoxy( col, 2 );  
      cout << "---";
      med.attach( this, Mediator::ODD );  // 2,5. Receivers register with Sender
   }
   void update( int num ) 
   {
     gotoxy( col, row++ );
     cout << num; 
   }
};

class EvenObserver : public Observer 
{
   int col, row;
public:
   EvenObserver( Mediator& med, int c ) 
   {
      col = c;           
      row = 3;
      gotoxy( col, 1 );  
      cout << "/2";
      gotoxy( col, 2 );  
      cout << "--";
      med.attach( this, Mediator::EVEN );
   }
   void update( int num ) 
   {
      gotoxy( col, row++ );  
      cout << num; 
   }
};

class ThreeObserver : public Observer {
   int col, row;
public:
   ThreeObserver( Mediator& med, int c ) 
   {
      col = c;           
      row = 3;
      gotoxy( col, 1 );  cout << "/3";
      gotoxy( col, 2 );  cout << "--";
      med.attach( this, Mediator::THREE );
   }
   void update( int num ) 
   {
      gotoxy( col, row++ );  
      cout << num; 
   }
};

class Publisher 
{ 
public:            // 6. Sender sends to Mediator
   Publisher( Mediator& med ) { for (int i=1; i < 10; i++) med.disseminate(i); }
};

int main_observer_3( void ) 
{
  cout<<">>>>>>>> main_observer_3 <<<<<<<<"<<endl;
   Mediator   mediator;
   OddObserver(   mediator,  1 );
   EvenObserver(  mediator, 11 );
   ThreeObserver( mediator, 21 );
   Publisher  producer( mediator );  // 4. Sender has handle to Mediator
   return 0;
}

// Odd       /2        /3
// ---       --        --
// 1         2         3
// 3         4         6
// 5         6         9
// 7         8
// 9



