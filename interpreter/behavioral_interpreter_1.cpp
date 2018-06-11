// Purpose.  Interpreter          
//                                
// Define a grammar for a language and map each rule to a class.
                                  
#include <iostream>             
#include <string>     

using std::cout;
using std::endl;     
using std::cin;  
          
                                  
int sub(char* i, char* o, char* c) 
{  
  strcat(o, c);  strcpy(i, &(i[1])); 
   return 1; 
}
class A { public:                      
   int eval( char* i, char* o ) {      
      if (i[0] == 'a')                 
         return sub(i,o,(char*)"1");          
      return 0; } };                   
class B { public:                      
   int eval( char* i, char* o ) {      
      if (i[0] == 'b')                 
         return sub(i,o,(char*)"2");
      return 0; } };                   
class C { public:                      
   int eval( char* i, char* o ) {      
      if (i[0] == 'c')                 
         return sub(i,o,(char*)"3");          
      return 0; } };                   
class D { public:                      
   int eval( char* i, char* o ) {      
      if (i[0] == 'd')                 
         return sub(i,o,(char*)"4");          
      return 0; } };                   
class E { public:                      
   int eval( char* i, char* o ) {      
      if (i[0] == 'e')                 
         return sub(i,o,(char*)"5");          
      return 0; } };                   
class F { public:
   int eval( char* i, char* o ) {      
      if (i[0] == 'f')                 
         return sub(i,o,(char*)"6");          
      return 0; } };                   
class G { public:                      
   int eval( char* i, char* o ) {      
      if (i[0] == 'g')                 
         return sub(i,o,(char*)"7");          
      return 0; } };
class H { public:                      
   int eval( char* i, char* o ) {      
      if (i[0] == 'h')                 
         return sub(i,o,(char*)"8");          
      return 0; } };                   
                                       
class Arti { public:                   
   int eval( char* i, char* o ) {      
      if (a.eval(i,o)) return 1;       
      if (b.eval(i,o)) return 1;       
      return 0; }                      
private:                               
   A a;  B b;                          
};
class Noun { public:                   
   int eval( char* i, char* o ) {      
      if (c.eval(i,o)) return 1;       
      if (d.eval(i,o)) return 1;       
      return 0; }                      
        private:
     C c;  D d;
  };

  class Acti { public:
     int eval( char* i, char* o ) {
        if (e.eval(i,o)) return 1;
        if (f.eval(i,o)) return 1;
        return 0; }
  private:
     E e;  F f;
};



 class Pass { public:
    int eval( char* i, char* o ) {
       if (g.eval(i,o)) return 1;
       if (h.eval(i,o)) return 1;
       return 0; }
 private:
    G g;  H h;
 };

 class NP { public:
    int eval( char* i, char* o ) {
       if (arti.eval(i,o))
          if (noun.eval(i,o)) return 1;
       return 0; }
 private:
    Arti arti;  Noun noun;
 };
 class Verb { public:
    int eval( char* i, char* o ) {
       if (acti.eval(i,o)) return 1;
       if (pass.eval(i,o)) return 1;
       return 0; }
 private:
    Acti acti;  Pass pass;
 };

 class Sent { public:
    int eval( char* i, char* o ) {
       if (np.eval(i,o))
          if (verb.eval(i,o)) return 1;
       return 0; }
 private:
    NP np;  Verb verb;
 };

 int main_interpreter_1( void )
 {
    Sent S;  char* t[] = {(char *)"ace",(char *)"bdh",
                 (char *) "abc",(char *)"ceg",(char *)"bcfgh"};
    char  i[10], o[10];
    for (int j=0; j < 5; j++) {
       strcpy(i,t[j]); strcpy(o,"");
       cout << i << " is ";
       if ( ! S.eval(i,o) || i[0])
          cout << "bad" << endl;
       else
          cout << o << endl; }
    return 0;
 }

 // ace is 135
 // bdh is 248
 // abc is bad
 // ceg is bad
 // bcfgh is bad