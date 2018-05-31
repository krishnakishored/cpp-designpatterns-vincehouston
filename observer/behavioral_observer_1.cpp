// Purpose.  Observer                   
//
// Discussion.  On the left: Subject has hard-wired the number and type of "dependent" objects, the compiler must have the declaration of the  
// concrete Obs classes to compile Subject's decl, the Obs classes exercise no reuse of i/f or impl, and Subject "pushes" updates to the Obs  
// objects.  On the right: Subject is decoupled from the number, type, and declaration of concrete Obs subclasses; the Obs objects accept
// polymorphism; and Subject broadcasts that a change has occurred followed by Obs objects requesting just the info that they want.        
#include<iostream>

using std::cout;
using std::vector;
using std::cin;
using std::endl;

class DivObs1 { 
public:                  
   DivObs1( int );                       
   void update( int );                  
private:                                
   int  div_;                           
};                                      
class ModObs1 { public:                  
   ModObs1( int );                       
   void update( int );                  
private:
   int  div_;                           
};                                      
                                        
class Subject1 {                         
public:                                 
   Subject1();                           
   void setVal( int );                  
private:                                
   int     val_;                        
   DivObs1  div_;
   ModObs1  mod_;                        
};                                      
                                        
Subject1::Subject1() : div_(4), mod_(3)   
   { }                                  
void Subject1::setVal( int v ) {         
   val_ = v;                            
   div_.update( val_ );                 
   mod_.update( val_ ); }               
                                        
DivObs1::DivObs1( int d ) { div_ = d; }   
void DivObs1::update( int v ) {          
   cout << v << " div " << div_         
      << " is " << v / div_ << endl; }  
ModObs1::ModObs1( int d ) { div_ = d; }
void ModObs1::update( int v ) {          
   cout << v << " mod " << div_         
      << " is " << v % div_ << endl; }  
                                        
int main_observer_1( void )                       
{                                       
   Subject1  subj;                       
   subj.setVal( 14 );
   return 0;                   
}
                                        
// 14 div 4 is 3                        
// 14 mod 3 is 2                        

class Obs;
class Subject {
public:
   Subject();
   void attach( Obs* );
   void setVal( int );
   int  getVal();
   void notify();
private:
   Obs*  obs_[10];
   int   num_, val_;
};
class Obs { 
public:
   virtual void update() = 0;
protected:
   Subject*  sub_;
   int       div_;
};
class DivObs : public Obs { public:
   DivObs( Subject*, int );
   void update();
};
class ModObs : public Obs { public:
   ModObs( Subject*, int );
   void update();
};
Subject::Subject()     { num_ = 0; }
int  Subject::getVal() { return val_; }
void Subject::attach( Obs* o ) {
   obs_[num_++] = o; }
void Subject::setVal( int v ) {
   val_ = v;   notify(); }
void Subject::notify() {
   for (int i=0; i < num_; i++)
      obs_[i]->update(); }
DivObs::DivObs( Subject* s, int d ) {
   sub_ = s;  div_ = d;
   sub_->attach( this ); }
void DivObs::update() {
   int v = sub_->getVal();
   cout << v << " div " << div_
      << " is " << v / div_ << endl; }
ModObs::ModObs( Subject* s, int d ) {
   sub_ = s;  div_ = d;
   sub_->attach( this ); }
void ModObs::update() {
   int v = sub_->getVal();
   cout << v << " mod " << div_
      << " is " << v % div_ << endl; }
int main( void )
{
   Subject  subj;
   DivObs   divObs1( &subj, 4 );
   DivObs   divObs2( &subj, 3 );
   ModObs   modObs3( &subj, 3 );
   subj.setVal( 14 );
   return 0;
}
// 14 div 4 is 3
// 14 div 3 is 4
// 14 mod 3 is 2
