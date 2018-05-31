// Strategy pattern - after (template approach)
//
// A template can be used to configure a client with a Strategy.  This
// technique is appropriate if: 1) the Strategy can be selected at com-
// pile-time, and 2) it does not have to be changed at run-time.  With
// a template, there is no need to specify the interface in a SortImpl
// base class.  The Stat class now has an instance of the sort object,
// instead of a ptr to the base class.  The inheritance approach offers
// more options and expressiveness.  The template approach offers mildly
// better efficiency.
#include<iostream>
using std::cout;

template<typename STRATEGY>
class Stat {
public:
   void readVector( int v[], int n ) {
      m_impl.sort( v, n );
      m_min = v[0];
      m_max = v[n-1];
      m_median = v[n/2];
   }
   int getMin()    { return m_min; }
   int getMax()    { return m_max; }
   int getMedian() { return m_median; }
private:
   int m_min, m_max, m_median;
   STRATEGY  m_impl;
};

class SortBubble {
public:
   void sort( int v[], int n ) {
      for (int i=n-1; i > 0; --i)
         for (int j=0; j < i; ++j)
            if (v[j] > v[j+1]) {
               int t = v[j];
               v[j] = v[j+1];
               v[j+1] = t;
            }
      cout << "Bubble: ";
      for (int k=0; k < n; k++)
         cout << v[k] << ' ';
      cout << '\n';
   }
};
class SortShell {
public:
   void sort( int v[], int n ) {
      for (int g = n/2; g > 0; g /= 2)
         for (int i = g; i < n; ++i)
            for (int j = i-g; j >= 0; j -= g)
               if (v[j] > v[j+g]) {
                  int temp = v[j];
                  v[j] = v[j+g];
                  v[j+g] = temp;
               }
      cout << "Shell:  ";
      for (int k=0; k < n; k++)
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
   Stat<SortBubble>  one;
   one.readVector( array, NUM );
   cout << "min is " << one.getMin() << ", max is " << one.getMax()
        << ", median is " << one.getMedian() << '\n';

   Stat<SortShell>  two;
   two.readVector( array, NUM );
   cout << "min is " << two.getMin() << ", max is " << two.getMax()
        << ", median is " << two.getMedian() << '\n';
        return 0;
}

// Vector: 8 3 1 9 7 2 2 9 7
// Bubble: 1 2 2 3 7 7 8 9 9
// min is 1, max is 9, median is 7
// Shell:  1 2 2 3 7 7 8 9 9
// min is 1, max is 9, median is 7

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
