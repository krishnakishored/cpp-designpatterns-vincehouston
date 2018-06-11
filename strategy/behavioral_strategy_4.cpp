
#include<iostream>

using std::cout;
using std::vector;
using std::cin;
using std::endl;
       

#include <cstdlib>
#include <ctime>

template<class STRATEGY>
class Stat {
public:
   void readVector( int v[], int n ) {
      imp_.sort( v, n );
      min_ = v[0];   max_ = v[n-1];
      med_ = v[n/2]; }
   int getMin() { return min_; }
   int getMax() { return max_; }
   int getMed() { return med_; }
private:
   int       min_, max_, med_;
   STRATEGY  imp_;
};
class SortBubble {
public:
   void sort( int v[], int n );
};
class SortShell {
public:
   void sort( int v[], int n );
};

// #include "strategy2.inc"

int main_strategy_4( void ) {
   const int NUM = 9;
   int       array[NUM];
   time_t    t;
   srand((unsigned) time(&t));
   cout << "Vector: ";
   for (int i=0; i < NUM; i++) {
      array[i] = rand() % 9 + 1;
      cout << array[i] << ' '; }
   cout << endl;
   Stat<SortBubble>  obj;
   obj.readVector( array, NUM );
   cout << "min is " << obj.getMin()
      << ", max is " << obj.getMax()
      << ", median is " << obj.getMed()
      << endl;
   Stat<SortShell>  two;
   two.readVector( array, NUM );
   cout << "min is " << two.getMin()
      << ", max is " << two.getMax()
      << ", median is " << two.getMed()
      << endl;
      return 0;
}
// Vector: 3 5 4 9 7 1 4 9 2
// Bubble: 1 2 3 4 4 5 7 9 9
// min is 1, max is 9, median is 4
// Shell:  1 2 3 4 4 5 7 9 9
// min is 1, max is 9, median is 4