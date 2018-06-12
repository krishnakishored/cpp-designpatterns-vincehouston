// Purpose.  Mediator design pattern demo.
// 
// Discussion.  Though partitioning a system into many objects generally enhances reusability, proliferating interconnections tend to reduce it again
// You can avoid this problem by capsulating the interconnections (i.e. the collective behavior) in a separate "mediator" object.  
// A mediator is responsible for controlling and coordinating the interactions of a group of objects.  

// In this example, the dialog box object is functioning as the mediator.  Child widgets of the dialog box do not know, or care, who their siblings are.  
// Whenever a simulated user interaction occurs in a child widget [Widget::changed()], the widget does nothing except "delegate" that event to its parent dialog
// box [_mediator->widgetChanged( this )]. FileSelectionDialog::widgetChanged() encapsulates all collective behavior for the dialog box (it serves as the hub of communication).
// The user may choose to "interact" with a simulated: filter edit field, directories list, files list, or selection edit field.

#include "CommonInclude.h"     
class FileSelectionDialog;

class Widget {
public:
	Widget( FileSelectionDialog* mediator, char* name ) {
		_mediator = mediator;
		strcpy( _name, name); }
	virtual void changed();
	virtual void updateWidget() = 0;
	virtual void queryWidget() = 0;
	virtual ~Widget(){}// TODO: delete called on 'Widget' that is abstract but has non-virtual destructor [-Wdelete-non-virtual-dtor]
protected:
	char                 _name[20];
private:
	FileSelectionDialog* _mediator;
};

class List : public Widget {
public:
	List( FileSelectionDialog* dir, char* name ) : Widget( dir, name ) { }
    void queryWidget()  { cout << "   " << _name << " list queried" << endl; }
	void updateWidget() { cout << "   " << _name << " list updated" << endl; }
};

class Edit : public Widget {
public:
    Edit( FileSelectionDialog* dir, char* name ): Widget( dir, name ) { }
    void queryWidget()  { cout << "   " << _name << " edit queried" << endl; }
    void updateWidget() { cout << "   " << _name << " edit updated" << endl; }
};


class FileSelectionDialog {
public:
	enum Widgets { FilterEdit, DirList, FileList, SelectionEdit };
	FileSelectionDialog() {
		_components[FilterEdit]    = new Edit( this, (char*)"filter" );
		_components[DirList]       = new List( this, (char*)"dir" );
		_components[FileList]      = new List( this, (char*)"file" );
		_components[SelectionEdit] = new Edit( this, (char*)"selection" ); }
	virtual ~FileSelectionDialog();
	void handleEvent( int which ) {
		_components[which]->changed(); }
	virtual void widgetChanged( Widget* theChangedWidget ) {
		if (theChangedWidget == _components[FilterEdit] ) {
			_components[FilterEdit]->    queryWidget();
			_components[DirList]->       updateWidget();
			_components[FileList]->      updateWidget();
			_components[SelectionEdit]-> updateWidget(); }
		else if (theChangedWidget == _components[DirList] ) {
			_components[DirList]->       queryWidget();
			_components[FileList]->      updateWidget();
			_components[FilterEdit]->    updateWidget();
			_components[SelectionEdit]-> updateWidget(); }
		else if (theChangedWidget == _components[FileList] ) {
			_components[FileList]->      queryWidget();
 			_components[SelectionEdit]-> updateWidget(); }
		else if (theChangedWidget == _components[SelectionEdit] ) {
			_components[SelectionEdit]-> queryWidget();
			cout << "   file opened" << endl; } }
private:
	Widget* _components[4];
};

FileSelectionDialog::~FileSelectionDialog() {
	for (int i=0; i < 3; i++)
		delete _components[i]; } // message: delete called on 'Widget' that is abstract but has non-virtual destructor [-Wdelete-non-virtual-dtor]


void Widget::changed() {
	_mediator->widgetChanged( this ); }


int main_mediator_2() 
{
	cout<<">>>>>>>> main_mediator_2 <<<<<<<<"<<endl;    
	FileSelectionDialog fileDialog;
	int                 i;

	cout << "Exit[0], Filter[1], Dir[2], File[3], Selection[4]: ";
	cin >> i;

	while (i)
	{
		fileDialog.handleEvent( i-1 );
		cout << "Exit[0], Filter[1], Dir[2], File[3], Selection[4]: ";
		cin >> i;
	}
  return 0;
}

// Exit[0], Filter[1], Dir[2], File[3], Selection[4]: 1
//    filter edit queried
//    dir list updated
//    file list updated
//    selection edit updated
// Exit[0], Filter[1], Dir[2], File[3], Selection[4]: 2
//    dir list queried
//    file list updated
//    filter edit updated
//    selection edit updated
// Exit[0], Filter[1], Dir[2], File[3], Selection[4]: 3
//    file list queried
//    selection edit updated
// Exit[0], Filter[1], Dir[2], File[3], Selection[4]: 4
//    selection edit queried
//    file opened
// Exit[0], Filter[1], Dir[2], File[3], Selection[4]: 3
//    file list queried
//    selection edit updated