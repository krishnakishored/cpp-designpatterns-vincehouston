// Purpose.  Simple implementation of an Iterator (uses parallel dynamic array)
//
// Discussion.  Instead of having to write an involved stack-like solution to handle step-wise recursive descent, 
// use a little extra memory to maintain a sequential representation of the original hierarchical data.  
// The replicated data are not Node objects, they are lightweight pointers.  
// The array is initialized using a recursive method similar to traverse(Node*).

#include "CommonInclude.h"    

class Iterator1;

class BST {
   friend class Iterator1;
   struct Node {
      Node( int );
      int value;
      Node* left;
      Node* rite;
   };
   Node* root;
   int   size;
   void add( Node**, int );
   void traverse( Node* );
public:
   BST() { root = 0;  size = 0; }
   void add( int );
   void traverse();
   Iterator1* createIterator() const;
};

class Iterator1 {
   const BST* tree;
   BST::Node** array;
   int index;
   void populateArray( BST::Node* current ) {
      if (current->left) populateArray( current->left );
      array[index++] = current;
      if (current->rite) populateArray( current->rite );
   }
public:
   Iterator1( const BST* s ) {
      tree = s;
      array = 0;  index = 0;
   }
   ~Iterator1() { delete [] array; }
   void first() {
      delete [] array;
      array = new BST::Node*[tree->size];
      index = 0;
      populateArray( tree->root );
      index = 0;
   }
   void next()              { index++; }
   bool isDone()            { return index == tree->size; }
   BST::Node* currentItem() { return array[index]; }
};

int main_interpreter_3A( void ) {
      cout<<">>>>>>>> main_interpreter_3A <<<<<<<<"<<endl;
   srand( time( 0 ) );
   BST  tree;
   for (int i=0; i < 20; i++) tree.add( rand() % 20 + 1 );
   cout << "traverse: ";
   tree.traverse();
   cout << "\niterator: ";
   Iterator1* it = tree.createIterator();
   for (it->first(); ! it->isDone(); it->next())
      cout << it->currentItem()->value << ' ';
   cout << "\niterator: ";
   for (it->first(); ! it->isDone(); it->next())
      cout << it->currentItem()->value << ' ';
   cout << '\n';
   return 0;
}

// traverse: 1 2 3 7 8 9 9 10 11 11 13 14 14 14 15 17 18 19 19 20
// iterator: 1 2 3 7 8 9 9 10 11 11 13 14 14 14 15 17 18 19 19 20
// iterator: 1 2 3 7 8 9 9 10 11 11 13 14 14 14 15 17 18 19 19 20


BST::Node::Node( int v ) { value = v;  left = rite = 0; }

void BST::add( Node** n, int v ) {
   if ( ! *n)                 { *n = new Node( v );  size++; }
   else if (v <= (*n)->value) add( &((*n)->left), v );
   else                       add( &((*n)->rite), v );
}

void BST::add( int v ) { add( &root, v ); }
void BST::traverse() { traverse( root ); }

void BST::traverse( Node* n ) {
   if (n->left) traverse( n->left );
   cout << n->value << ' ';
   if (n->rite) traverse( n->rite );
}

Iterator1* BST::createIterator() const { return new Iterator1( this ); }




// Purpose.  Fairly reusable iterator for step-wise recursive descent
//
// Discussion.  The Composite/Component/Leaf code is one of the previous
// Composite demos.  Methods added were: Component::outputValue() and
// Composite::createIterator().

class Iterator;

class Component { public:
   virtual void traverse() = 0;
   virtual void outputValue() { }
};

class Leaf : public Component {
   int value;
public:
   Leaf( int val ) { value = val; }
   /*virtual*/ void traverse() { cout << value << ' '; }
   /*virtual*/ void outputValue() { traverse(); }
};

class Composite : public Component {
   vector<Component*> children;
public:
   friend class Iterator;
   void add( Component* ele ) { children.push_back( ele ); }
   /*virtual*/ void traverse() {
      for (int i=0; i < children.size(); i++)
         children[i]->traverse();
   }
   Iterator* createIterator();
};

class Memento {
public:
   struct MgrIdx {
      MgrIdx( Composite* m=0, int i=0 ) { mgr = m;  idx = i; }
      Composite* mgr;
      int        idx;
   };
   void initialize( Composite* root ) {
      vec.resize( 0 );
      vec.push_back( MgrIdx( root, 0 ) );
   }
   bool isEmpty()         { return vec.size() == 0; }
   void push( MgrIdx ds ) { vec.push_back( ds ); }
   MgrIdx top()           { return vec.back(); }
   MgrIdx pop() {
      MgrIdx ds = vec.back();
      vec.pop_back();
      return ds;
   }
private:
   vector<MgrIdx> vec;
};

// Dependencies on actual class playing the role of "Composite":
//    Composite class name, children attribute name
class Iterator {
   Composite* root;
   Memento    memento;
   bool       done;
public:
   Iterator( Composite* rooot ) { root = rooot; }
   void first() {
      memento.initialize( root );
      done = false;
   }
   void next() {
      Memento::MgrIdx ds = memento.pop();
      ds.idx++;
      // if (and while) you are at end-of-composite, go up
      while (ds.idx == ds.mgr->children.size()) {
         if (memento.isEmpty()) { done = true;  return; }
         ds = memento.pop();
         ds.idx++;
      }
      memento.push( ds );
      Composite* compo;
      if ((compo = dynamic_cast<Composite*>(ds.mgr->children[ds.idx])))
         memento.push( Memento::MgrIdx( compo, 0 ) );
   }
   Component* currentItem() {
      Memento::MgrIdx ds = memento.top();
      return ds.mgr->children[ds.idx];
   }
   bool isDone() { return done; }
};

Iterator* Composite::createIterator() { return new Iterator( this ); }

int main_interpreter_3B( void )

{
      main_interpreter_3A();
      cout<<">>>>>>>> main_interpreter_3B <<<<<<<<"<<endl;
   Composite containers[4];
   for (int i=0; i < 4; i++)
      for (int j=0; j < 3; j++)
         containers[i].add( new Leaf( i * 3 + j ) );
   for (int i=1; i < 4; i++) containers[0].add( &(containers[i]) );
   cout << "traverse: ";
   containers[0].traverse();

   Iterator* it = containers[0].createIterator();
   cout << "\niterator: ";
   for (it->first(); ! it->isDone(); it->next())
      it->currentItem()->outputValue();
   cout << '\n';
   cout << "iterator: ";
   for (it->first(); ! it->isDone(); it->next())
      it->currentItem()->outputValue();
   cout << '\n';
   delete it;
   return 0;
}

// traverse: 0 1 2 3 4 5 6 7 8 9 10 11
// iterator: 0 1 2 3 4 5 6 7 8 9 10 11
// iterator: 0 1 2 3 4 5 6 7 8 9 10 11