

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// Here are the same examples NOT side-by-side, and with the
// #include "strategy2.inc" removed.

// Strategy pattern - before
//
// The class Stat has a Bubble sort algorithm hard-wired in it.
// It would be nice if the choice of algorithm were configurable.
// The Strategy pattern suggests "define a family of algorithms,
// encapsulate the hierarchy, and make them interchangeable" via
// an abstract base class.

#include <iostream>
using std::cout;

class Stat {
public:
   void readVector( int v[], int n ) {
      sort( v, n );
      m_min = v[0];
      m_max = v[n-1];
      m_median = v[n/2];
   }
   int getMin()    { return m_min; }
   int getMax()    { return m_max; }
   int getMedian() { return m_median; }
private:
   int m_min, m_max, m_median;
   void sort( int v[], int n ) {     /* Bubble sort */
      for (int i=n-1; i > 0; --i)
         for (int j=0; j < i; ++j)
            if (v[j] > v[j+1]) {
               int t = v[j];
               v[j] = v[j+1];
               v[j+1] = t;
            }
      cout << "Bubble: ";
      for (int k=0; k < n; ++k)
         cout << v[k] << ' ';
      cout << '\n';
   }
};

int main( void ) {
   const int NUM = 9;
   int       array[NUM];
   srand( time(0) );
   cout << "Vector: ";
   for (int i=0; i < NUM; ++i) {
      array[i] = rand() % 9 + 1;
      cout << array[i] << ' ';
   }
   cout << '\n';

   Stat  obj;
   obj.readVector( array, NUM );
   cout << "min is " << obj.getMin() << ", max is " << obj.getMax()
        << ", median is " << obj.getMedian() << '\n';
        return 0;
}

// Vector: 6 9 9 8 6 5 7 9 2
// Bubble: 2 5 6 6 7 8 9 9 9
// min is 2, max is 9, median is 7