// Purpose.  Direct coupling, lots of start-up and shut-down overhead
#include "CommonInclude.h" 

// Purpose.  "->" and "." operators give different results

class Subject 
{
public: 
      virtual void execute() = 0; 
      virtual ~Subject(){}
};

class RealSubject : public Subject {
   string str;
public:
   RealSubject( string s ) { str = s; }
   /*virtual*/ void execute() { cout << str << '\n'; }
};

class ProxySubject : public Subject {
   string       first, second, third;
   RealSubject* ptr;
public:
   ProxySubject( string s ) {
      int num = s.find_first_of( ' ' );
      first = s.substr( 0, num );   s = s.substr( num+1 );
      num = s.find_first_of( ' ' );
      second = s.substr( 0, num );  s = s.substr( num+1 );
      num = s.find_first_of( ' ' );
      third = s.substr( 0, num );   s = s.substr( num+1 );
      ptr = new RealSubject( s );
   }
   ~ProxySubject() { delete ptr; }
   RealSubject* operator->() {
      cout << first << ' ' << second << ' ';
      return ptr;
   }
   /*virtual*/ void execute() {
      cout << first << ' ' << third << ' ';
      ptr->execute();
   }
};

int main_proxy_2A( void ) 
{
      cout<<">>>>>>>> main_proxy_2A <<<<<<<<"<<endl;  
   ProxySubject obj( string( "the quick brown fox jumped over the dog" ) );
   obj->execute();
   obj.execute();

   return 0;
}

// the quick fox jumped over the dog
// the brown fox jumped over the dog

// Purpose.  "A protection proxy controls access to the original object."

class Person {
   string nameString;
   static string list[];
   static int next;
public:
   Person() { nameString = list[next++]; }
   string name() { return nameString; }
};
string Person::list[] = { "Tom", "Dick", "Harry", "Bubba" };
int    Person::next = 0;

class PettyCashProtected {
   int balance;
public:
   PettyCashProtected() { balance = 500; }
   bool withdraw( int amount ) {
      if (amount > balance) return false;
      balance -= amount;
      return true;
   }
   int getBalance() { return balance; }
};

class PettyCash {
   PettyCashProtected realThing;
public:
   bool withdraw( Person& p, int amount ) {
      if (p.name() == "Tom" || p.name() == "Harry" || p.name() == "Bubba")
         return realThing.withdraw( amount );
      else return false;
   }
   int getBalance() { return realThing.getBalance(); }
};

int main_proxy_2B( void ) 
{
      cout<<">>>>>>>> main_proxy_2B <<<<<<<<"<<endl;  
   PettyCash  pc;
   Person     workers[4];
   for (int i=0, amount=100; i < 4; i++, amount += 100)
      if ( ! pc.withdraw( workers[i], amount ))
         cout << "No money for " << workers[i].name() << '\n';
      else
         cout << amount << " dollars for " << workers[i].name() << '\n';
   cout << "Remaining balance is " << pc.getBalance() << '\n';
   return 0;
}

// 100 dollars for Tom
// No money for Dick
// 300 dollars for Harry
// No money for Bubba
// Remaining balance is 100




// Purpose.  Simulate a Persistent Object Pointer

template <typename TBD>
class POP {          // Persistent Object Pointer
   string oid;
   TBD*   ptr;
public:
   POP( string id )  { oid = id;  ptr = 0; }
   ~POP()            { delete ptr; }
   TBD* operator->() {
      if ( ! ptr)
         // simulate the persistence mechanism
         ptr = new TBD( oid );
      return ptr;
}  };

class Person2 {
   string name;
   int    age;
public:
   Person2( string n) { name = n;}
   string getName()   { return name; }
   int    getAge()    { return age; }//32 ??
};

int main_proxy_2C( void ) 
{ 
   main_proxy_2A();
   main_proxy_2B(); 
   cout<<">>>>>>>> main_proxy_2C <<<<<<<<"<<endl;  
   POP<Person2> ph( "Tom");
   cout << "policy holder is " << ph->getName() << ", age is " << ph->getAge() << '\n';
   return 0;
}

// policy holder is Tom, age is 32