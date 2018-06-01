# cpp-designpatterns-vincehouston

## GoF Structure Similarities

#### Left-Right symbol = wrapper/wrappee or delegation or "has a" relationship
* Adapter ... wrap a legacy object that provides an incompatible interface with an object that supports the desired interface
* Facade ... wrap a complicated subsystem with an object that provides a simple interface
* Proxy ... wrap an object with a surrogate object that provides additional functionality

#### Up-Down symbol = inheritance hierarchy (promote interface to a base class and bury implementation alternatives in derived classes)
* Strategy ... define algorithm interface in a base class and implementations in derived classes
* Factory Method ... define "createInstance" placeholder in the base class, each derived class calls the "new" operator and returns an instance of itself
* Visitor ... define "accept" method in first inheritance hierarchy, define "visit" methods in second hierarchy ... a.k.a. "double dispatch"

#### Category: a wrapper wraps an inheritance hierarchy
* Builder ... the "reader" delegates to its configured "builder" ... each builder corresponds to a different representation or target
* State ... the FiniteStateMachine delegates to the "current" state object, and that state object can set the "next" state object
* Bridge ... the wrapper models "abstraction" and the wrappee models many possible "implementations" ... the wrapper can use inheritance to support abstraction specialization
* Observer ... the "model" broadcasts to many possible "views", and each "view" can dialog with the "model"

#### Category: recursive composition
* Composite ... derived Composites contain one or more base Components, each of which could be a derived Composite
* Decorator ... a Decorator contains a single base Component, which could be a derived ConcreteComponent or another derived Decorator
* Chain of Responsibility ... define "linked list" functionality in the base class and implement "domain" functionality in derived classes
* Interpreter ... map a domain to a language, the language to a recursive grammar, and the grammar to the Composite pattern

#### Cloud symbol = promote X to "full object status"
* Command ... encapsulate an object, the method to be invoked, and the parameters to be passed behind the method signature "execute"
* Iterator ... encapsulate the traversal of collection classes behind the interface "first..next..isDone"
* Mediator ... decouple peer objects by encapsulating their "many to many" linkages in an intermediary object
* Memento ... encapsulate the state of an existing object in a new object to implement a "restore" capability
* Prototype ... encapsulate use of the "new" operator behind the method signature "clone" ... clients will delegate to a Prototype object when new instances are required

#### Category: miscellaneous
* Abstract Factory ... model "platform" (e.g. windowing system, operating system, database) with an inheritance hierarchy, and model each "product" (e.g. widgets, services, data structures) with its own hierarchy ... platform derived classes create and return instances of product derived classes
* Template Method ... define the "outline" of an algorithm in a base class ... common implementation is staged in the base class, peculiar implementation is represented by "place holders" in the base class and then implemented in derived classes
* Flyweight ... when dozens of instances of a class are desired and performance boggs down, externalize object state that is peculiar for each instance, and require the client to pass that state when methods are invoked
* Singleton ... engineer a class to encapsulate a single instance of itself, and "lock out" clients from creating their own instances