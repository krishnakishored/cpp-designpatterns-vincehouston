










// Purpose.  Template Method design pattern demo.
// 
// Discussion.  The "template method" establishes the steps to be
// performed.  All standard, or invariant, steps have their implementation
// provided by the abstract base class.  All variable steps are not
// defined in the base class, but must be defined by concrete derived
// classes.  "stepFour" below is an embellishment on the design pattern
// where the base class provides a default implementation, and then the
// derived class may extend that method by: overriding the method,
// "calling-back" to the base class to leverage its implementation, and
// then adding its own peculiar behavior.

#include <iostream>

using std::cout;
using std::endl;

class IncompleteAlgorithm {
public:
   void doIt() {       // this is the Template Method
      stepOne();       // invariant, standard
      stepTwo();       // invariant, standard
      stepThree();     // variable,  supplied by subclass
      stepFour(); }    // variable,  default provided
private:
   void stepOne() {
      cout << "IncompleteAlgorithm::stepOne" << endl; }
   void stepTwo() {
      cout << "IncompleteAlgorithm::stepTwo" << endl; }
   virtual void stepThree() = 0;
protected:
   virtual void stepFour() {
      cout << "IncompleteAlgorithm::stepFour" << endl; }
};

class FillInTheTemplate : public IncompleteAlgorithm {
   /* virtual */ void stepThree() {
      cout << "FillInTheTemplate::stepThree" << endl; }
   /* virtual */ void stepFour() {
      IncompleteAlgorithm::stepFour();
      cout << "FillInTheTemplate::stepFour" << endl; }
};

int main() {
   FillInTheTemplate  theThingToDo;
   theThingToDo.doIt();
   return 0;
}

// IncompleteAlgorithm::stepOne
// IncompleteAlgorithm::stepTwo
// FillInTheTemplate::stepThree
// IncompleteAlgorithm::stepFour
// FillInTheTemplate::stepFour




// Purpose.  Template Method design pattern demo
//
// romanNumeral ::= {thousands} {hundreds} {tens} {ones}
// thousands, hundreds, tens, ones ::= nine | four | {five} {one} {one} {one}
// nine ::= "CM" | "XC" | "IX"
// four ::= "CD" | "XL" | "IV"
// five ::= 'D' | 'L' | 'V'
// one  ::= 'M' | 'C' | 'X' | 'I'

#include <iostream>
#include <string>
using namespace std;
class Thousand;  class Hundred;  class Ten;  class One;

class RNInterpreter {
public:
   static int interpret( string input );
   void interpret( string& input, int& total ) {               // Template Method
      int index = 0;
      if (input.substr(0,2) == nine()) {
         total += 9 * multiplier();
         index += 2;
      } else if (input.substr(0,2) == four()) {
         total += 4 * multiplier();
         index += 2;
      } else {
         if (input[0] == five()) {
            total += 5 * multiplier();
            index = 1;
         }
         for (int end = index + 3 ; index < end; index++)
            if (input[index] == one())
               total += 1 * multiplier();
            else break;
      }
      // remove all leading chars processed
      input.replace( 0, index, "" );
   }
private:
   virtual char one()        = 0;   virtual string four() = 0;  // placeholders
   virtual char five()       = 0;   virtual string nine() = 0;  // placeholders
   virtual int  multiplier() = 0;                               // placeholders
   static Thousand thousands;       static Hundred hundreds;
   static Ten      tens;            static One     ones;
};

class Thousand : public RNInterpreter {
   char  one()        { return 'M'; }    string four() { return ""; }
   char  five()       { return '\0'; }   string nine() { return ""; }
   int   multiplier() { return 1000; }
};
class Hundred : public RNInterpreter {
   char  one()        { return 'C'; }   string four() { return "CD"; }
   char  five()       { return 'D'; }   string nine() { return "CM"; }
   int   multiplier() { return 100; }
};
class Ten : public RNInterpreter {
   char  one()        { return 'X'; }   string four() { return "XL"; }
   char  five()       { return 'L'; }   string nine() { return "XC"; }
   int   multiplier() { return 10; }
};
class One : public RNInterpreter {
   char  one()        { return 'I'; }   string four() { return "IV"; }
   char  five()       { return 'V'; }   string nine() { return "IX"; }
   int   multiplier() { return 1; }
};

Thousand RNInterpreter::thousands;
Hundred  RNInterpreter::hundreds;
Ten      RNInterpreter::tens;
One      RNInterpreter::ones;

/*static*/ int RNInterpreter::interpret( string input ) {
   int total = 0;
   thousands.interpret( input, total );
   hundreds.interpret( input, total );
   tens.interpret( input, total );
   ones.interpret( input, total );
   // if any input remains, the input was invalid, return 0
   if (input != "") return 0;
   return total;
}

int main_template_7( void ) {
   string  input;
   cout << "Enter Roman Numeral: ";
   while (cin >> input) {
      cout << "   interpretation is " << RNInterpreter::interpret( input ) << endl;
      cout << "Enter Roman Numeral: ";
}  
return 0;
}

// Enter Roman Numeral: MCMXCVI
//    interpretation is 1996
// Enter Roman Numeral: MMMCMXCIX
//    interpretation is 3999
// Enter Roman Numeral: MMMM
//    interpretation is 0
// Enter Roman Numeral: MDCLXVIIII
//    interpretation is 0
// Enter Roman Numeral: CXCX
//    interpretation is 0
// Enter Roman Numeral: MDCLXVI
//    interpretation is 1666
// Enter Roman Numeral: DCCCLXXXVIII
//    interpretation is 888s