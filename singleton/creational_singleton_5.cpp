 // Purpose.  Singleton (Scott Meyers    
 //                      approach)       
 // Discussion.  On the left, a global   
 // object is architected to require     
 // lazy initialization (not inited un-  
 // til it is needed).  This requires    
 // all users of the object to test and  
 // potentially allocate the pointer.    
 // Singleton suggests making the class  
 // itself responsible for creating,     
 // maintaining, and providing global    
 // access to its own single instance.   
                                         
 #include <iostream>         
 using namespace std;  
    
 class GlobalClass {                     
 public:                                 
    GlobalClass( int v=0 ) {             
       value_ = v; }                     
    int  getValue() {                    
       return value_; }                  
    void setValue( int v ) {             
       value_ = v; }                     
 private:                                
    int  value_;                         
 };                                      
                                         
 // Initializing a global ptr to class   
 // GlobalClass                          
 GlobalClass*   globalObj = 0;           
                                         
 void foo( void )                        
 {                                       
    if ( ! globalObj )
       globalObj = new GlobalClass;      
    globalObj->setValue( 1 );            
    cout << "foo: globalObj is " <<      
       globalObj->getValue() << endl;    
 }                                       
                                         
 void bar( void )                        
 {
    if ( ! globalObj )                   
       globalObj = new GlobalClass;      
    globalObj->setValue( 2 );            
    cout << "bar: globalObj is " <<      
       globalObj->getValue() << endl;    
 }                                       
                                         
int main_singleton_5( void )
 {
       cout<<">>>>>>>> main_singleton_5 <<<<<<<<"<<endl;                                       
    if ( ! globalObj )                   
       globalObj = new GlobalClass;      
    cout << "main: globalObj is " <<     
       globalObj->getValue() << endl;    
    foo();                               
    bar(); 
    return 0;                              
 }                                       
                                         
 // main: globalObj is 0
 // foo: globalObj is 1                  
 // bar: globalObj is 2                  
                                         
                                         
                                         