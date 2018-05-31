#include<iostream>

using std::cout;
using std::vector;
using std::cin;
using std::endl;

#include <ctime>

// Purpose.  State design pattern - an FSM with two states and two events
// (distributed transition logic - logic in the derived state classes)

// State\Event     Suck up money      Drive through
//
// RedLight          you're a            you're   
//                    victim,             dead,
//                 maybe change       change to RED
//                   to GREEN
//
// GreenLight        you're an         you're free
//                     idiot           but you're
//                                  still a victim,
//                                   change to RED



class FSM1 {
   class State* current;
public:
   FSM1();
   void setCurrent( State* s ) { current = s; }
   void suckUpMoney( int );
   void carDrivesThrough();
};

class State {
   int total;
protected:
   int getTotal() { return total; }
public:
   State() { total = 0; }
   virtual void suckUpMoney( int in, FSM1* fsm ) {
      total += in;
      cout << "total is " << total << '\n';
   }
   virtual void carDrivesThrough( FSM1* fsm ) = 0;
};

class GreenLight : public State {
public:
   GreenLight() { cout << "GREEN light\n"; }
   void suckUpMoney( int in, FSM1* fsm ) {
      cout << "      You're an idiot, ";
      State::suckUpMoney( in, fsm );
   }
   void carDrivesThrough( FSM1* fsm );
};

class RedLight : public State {
public:
   RedLight() { cout << "RED light\n"; }
   void suckUpMoney( int in, FSM1* fsm ) {
      cout << "      ";
      State::suckUpMoney( in, fsm );
      if (getTotal() >= 50) {
         fsm->setCurrent( new GreenLight );
         delete this;
   }  }
   void carDrivesThrough( FSM1* fsm ) {
      cout << "Sirens!!  Heat-seeking missile!!  Confiscate net worth!!\n";
      fsm->setCurrent( new RedLight );
      delete this;
}  };

FSM1::FSM1() {
   current = new RedLight();
}
void FSM1::suckUpMoney( int in ) {
   current->suckUpMoney( in, this );
}
void FSM1::carDrivesThrough() {
   current->carDrivesThrough( this );
}
void GreenLight::carDrivesThrough( FSM1* fsm ) {
   cout << "Good-bye sucker!!\n";
   fsm->setCurrent( new RedLight );
   delete this;
}

int getCoin() {
   static int choices[3] = { 5, 10, 25 };
   return choices[rand() % 3];
}

int  main( void ) {
   srand( time(0) );
   FSM1 fsm;
   int ans;
   while (true) {
      cout << "   Shell out (1), Drive thru (2), Exit (0): ";
      cin >> ans;
      if      (ans == 1) fsm.suckUpMoney( getCoin() );
      else if (ans == 2) fsm.carDrivesThrough();
      else break;
    } 
 return 0;
}




// Purpose.  State demo (centralized transition logic - logic in the FSM)
// 
// Discussion.  Who defines the state transitions?  The State pattern does not
// specify which participant defines the criteria for state transitions.  The
// logic can be implemented entirely in the Context (FSM).  It is generally
// more flexible and appropriate, however, to let the State subclasses them-
// selves specify their successor state and when to make the transition.  This
// requires adding an interface to the Context that lets State objects set the
// Context's current state explicitly.  A disadvantage of decentralization is
// that State subclasses will be coupled to other sibling subclasses. [GOF308]

class FSMstate { public:
   virtual void on()  { cout << "undefined combo" << endl; }
   virtual void off() { cout << "undefined combo" << endl; }
   virtual void ack() { cout << "undefined combo" << endl; } };

class FSM {
public:
   FSM();
   void on()   { states[current]->on();  current = next[current][0]; }
   void off()  { states[current]->off(); current = next[current][1]; }
   void ack()  { states[current]->ack(); current = next[current][2]; }
private:
   FSMstate*  states[3];
   int        current;
   int        next[3][3];
};

class A : public FSMstate { public:
   void on()  { cout << "A, on ==> A" << endl; }
   void off() { cout << "A, off ==> B" << endl; }
   void ack() { cout << "A, ack ==> C" << endl; }
};
class B : public FSMstate { public:
   void off() { cout << "B, off ==> A" << endl; }
   void ack() { cout << "B, ack ==> C" << endl; }
};
class C : public FSMstate { public:
   void ack() { cout << "C, ack ==> B" << endl; }
};

FSM::FSM() {
   states[0] = new A; states[1] = new B; states[2] = new C;
   current = 1;
   next[0][0] = 0; next[0][1] = 1; next[0][2] = 2;
   next[1][0] = 1; next[1][1] = 0; next[1][2] = 2;
   next[2][0] = 2; next[2][1] = 2; next[2][2] = 1; }

enum     Message { On, Off, Ack };
Message  messageArray[10] = { On,Off,Off,Ack,Ack,Ack,Ack,On,Off,Off };

int main_state_4( void ) {
   FSM  fsm;
   for (int i = 0; i < 10; i++) {
      if (messageArray[i] == On)        fsm.on();
      else if (messageArray[i] == Off)  fsm.off();
      else if (messageArray[i] == Ack)  fsm.ack(); 
      }
      return 0;
}

// undefined combo           // B, ack ==> C
// B, off ==> A              // C, ack ==> B
// A, off ==> B              // undefined combo
// B, ack ==> C              // B, off ==> A
// C, ack ==> B              // A, off ==> B