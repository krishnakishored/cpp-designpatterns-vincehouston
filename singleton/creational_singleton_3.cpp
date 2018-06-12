 // Purpose.  Singleton destroyer        
 //
 // Discussion.  Vlissides describes that Singletons can be cleaned-up by "wrapping" the ptr in a stack based static member of another       
 // class whose sole responsibility is to have its destructor delete the Singleton's ptr.  The Singleton destroyer is automatically created before main() is run, and       
 // initially contains a null ptr. The first time the inst() method is called, the destroyer is meaningfully initialized.            

#include "CommonInclude.h"               
                                         
 class GlobalClass {                     
 public:                                 
    int  getValue() {                    
       return value_; }                  
    void setValue( int v ) {             
       value_ = v; }                     
    static GlobalClass* inst() {         
       if ( ! globalObj_ )               
          globalObj_ = new GlobalClass;  
       return globalObj_; }              
 protected:                              
    GlobalClass( int v=0 ) {             
       value_ = v; }                     
    ~GlobalClass() { }                   
 private:                                
    int    value_;                       
    static GlobalClass* globalObj_;
 };                                      
                                         
 // Allocating and initializing          
 // GlobalClass's static data member     
 // (the ptr, not a GlobalClass inst)
 GlobalClass*                            
    GlobalClass::globalObj_ = 0;         
                                         
 void foo( void ) {                      
    GlobalClass::inst()->setValue( 1 );  
    cout << "foo: globalObj is " <<      
       GlobalClass::inst()->getValue()   
       << endl;                          
 }                                       
 void bar( void ) {                      
    GlobalClass::inst()->setValue( 2 );  
    cout << "bar: globalObj is " << GlobalClass::inst()->getValue() << endl;                          
 }                                       

int main_singleton_3( void ) 
{
    cout<<">>>>>>>> main_singleton_3 <<<<<<<<"<<endl;                       
    cout << "main: globalObj is " <<     
       GlobalClass::inst()->getValue()   
       << endl;                          
    foo();                               
    bar();
    return 0;
 }                                       
                                         
 // main: globalObj is 0                 
 // foo: globalObj is 1                  
 // bar: globalObj is 2                  