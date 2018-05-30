// Purpose.  Command                    
//                                      
// Discussion.  On the left, an IOU has been encapsulated as a struct, and TheBoss class is tightly coupled to that struct.  
// On the right,TheBoss is only coupled to the abstract class Command.  Lots of possible derived classes could be substituted: IOUs that call payUp() on
// Deadbeats, Checks that call cash() on Banks, Stocks that call redeem() on Companies.  
// Each "command" is a "token" that gets transfered from one holder to another, until someone chooses to "execute" it.         
#include <iostream>  
#include <string>  
using std::cout;
// using std::cin;
using std::endl;

class Deadbeat 
{ 
public:                
   Deadbeat( int v ) { cash_ = v; }     
   int payUp( int v ) {                 
      cash_ -= v;  return v; }          
   int rptCash() { return cash_; }      
private:                                
   int cash_;                           
};                                      
                                        
struct IOU 
{                            
   Deadbeat*  objPtr;                   
   int (Deadbeat::*funPtr)( int );
   int amt;                      
};                                      
                                        
class Enforcer 
{ 
public:                
   Enforcer( IOU& m ) : mkr_(m) { }     
   IOU& collect() { return mkr_; }      
private:                                
   IOU& mkr_;
};                                      
                                        
class TheBoss {                         
public:                                 
   TheBoss() { cash_ = 1000; }          
   void collect( IOU& i ) 
   {                  
      cash_ +=                          
         ((i.objPtr)->*i.funPtr)(i.amt); 
   }                                    
   int rptCash() { return cash_; }
private:                                
   int cash_;                           
};                                      
                                        
int main( void )                       
{                                       
   Deadbeat joe(90), tom(90);           
   IOU one ={&joe, &Deadbeat::payUp,60};
   IOU two ={&tom, &Deadbeat::payUp,70}; 
   Enforcer quido(one), lucca(two);     
   TheBoss  don;                        
                                        
   don.collect( quido.collect() );      
   don.collect( lucca.collect() );      
   cout << "joe has $" << joe.rptCash();
   cout << "tom has $" << tom.rptCash(); 
   cout << "don has $" << don.rptCash(); 
   return 0;
}   



class Command { public:
   virtual int execute() = 0;
};
class IOU2 : public Command {
public:
   typedef int (Deadbeat::*Meth)(int);
   IOU2( Deadbeat* r, Meth a, int m ) {
      obj_ = r;
      mth_ = a;
      amt_ = m; }
   int execute() {
      return (obj_->*mth_)( amt_ ); }
private:
   Deadbeat*  obj_;
   Meth       mth_;
   int        amt_;
};
class Enforcer2 {
public:
   Enforcer2( Command& c ) : cmd_(c) {}
   Command& collect() { return cmd_; }
private:
   Command& cmd_;
};
class TheBoss2 {
public:
   TheBoss2() { cash_ = 1000; }
   void collect( Command& cmd ) 
   {
      cash_ += cmd.execute(); 
   }
   int rptCash() { return cash_; }
private:
   int cash_;
};

int main_2( void )
{
   Deadbeat joe(90), tom(90);
   IOU2 one(&joe, &Deadbeat::payUp, 60);
   IOU2 two(&tom, &Deadbeat::payUp, 70);
   Enforcer2 quido(one), lucca(two);
   TheBoss2  don;
   don.collect( quido.collect() );
   don.collect( lucca.collect() );
   cout << "joe has $" << joe.rptCash();
   cout << "tom has $" << tom.rptCash();
   cout << "don has $" << don.rptCash();
   return 0;
}
// joe has $30
// tom has $20
// don has $1130