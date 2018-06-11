#include <iostream>
using std::cout;
using std::endl;

class Widget { public:
   virtual void draw() = 0;
};
class MotifBtn : public Widget {
public:
   void draw() { cout << "MotifBtn"
      << endl; }
};
class WindowsBtn : public Widget {
public:
   void draw() { cout << "WindowsBtn"
      << endl; }
};
class Factory { public:
   virtual Widget* createBtn() = 0;
};
class MotifFactory : public Factory {
public:
   Widget* createBtn() {
      return new MotifBtn; }
};
class WindowsFactory : public Factory {
public:
   Widget* createBtn() {
      return new WindowsBtn; }
};
Factory* factory;
void doThisWindow() {
   // create window, attach btn
   Widget* w = factory->createBtn();
   w->draw(); }
void doThatWindow() {
   // create window, attach btn
   Widget* w = factory->createBtn();
   w->draw(); }

int main_abstractfactory_2( void )
{
#ifdef MOTIF
   factory = new MotifFactory;
#else // WINDOWS
   factory = new WindowsFactory;
#endif
   // create window, attach btn
   Widget* w = factory->createBtn();
   w->draw();
   doThisWindow();
   doThatWindow();
   return 0;
}
// MotifBtn
// MotifBtn
// MotifBtn