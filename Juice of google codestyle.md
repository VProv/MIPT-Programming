Adaptation of https://google.github.io/styleguide/cppguide.html

// Background
1. 

    #ifndef FOO_BAR_BAZ_H_
    #define FOO_BAR_BAZ_H_
    ...
    #endif 

Нужно использовать полный пусть файла в проекте.  
2. Avoid forward declaration(Объявление до определения).  
3. Inline functions: only less than 10 lines. Beware of distructors, which are often longer than they appear.  
Virtual and recursive functions are not normaly inline.The main reason for making a virtual function inline   
is to place its definition in the class, either for convenience or to document its behavior, e.g., for accessors and mutators.  

4. Names and Order of Includes.  
Use standard order for readability and to avoid hidden dependencies:  
Related header, C library, C++ library, other libraries' .h, your project's .h.  
Always indicate the relative location.(Всегда указывать относительный адрес.)  
  
In dir/foo.cc or dir/foo_test.cc, whose main purpose is to implement or test the stuff in dir2/foo2.h,   
order your includes as follows:  
(empty line between each groop)  
dir2/foo2.h.  
C system files.  
C++ system files.  
Other libraries' .h files.  
Your project's .h files.  
  
Within each section the includes should be ordered alphabetically.  
If you need some things from library A, that is included now in  one of the other headers B, include A yourself,  
unless B demonstrates that it gives A.   

// SCOPING  
5. Namespaces. (They prevent name collisions at compile time or runtime)  
Do not use using directives(using namespace std;).  
With few exceptions, place code in a namespace. Namespaces should have unique names based on the project name, and possibly its path  
Inline namespaces automatically place their names in the enclosing scope. (They are for compatibility across versions)  
    
    namespace X {
    inline namespace Y {
    void foo();
    }  // namespace Y
    }  // namespace X
    
Use this comments.  
(operation ::)  
Namespaces wrap the entire source file after includes, gflags definitions/declarations and forward declarations of classes from other namespaces.  
Example:  

    // In the .h file
    namespace mynamespace {
    
    // All declarations are within the namespace scope.
    // Notice the lack of indentation.
    class MyClass {
    public:
      ...
      void Foo();
    };

    }  // namespace mynamespace

    // In the .cc file
    namespace mynamespace {

    // Definition of functions is within scope of the namespace.
    void MyClass::Foo() {
      ...
    }
    
    }  // namespace mynamespace

Do not declare anything in namespace std.  
Do not use Namespace aliases at namespace scope in header files except in explicitly marked internal-only namespaces,   
because anything imported into a namespace in a header file becomes part of the public API exported by that file.  

6. Nonmember, Static Member, and Global Functions  
Static methods should be closely related with static data in class. You can create new class for nonmember and static member functions.  
Prefer placing nonmember functions in a namespace.  
    
    namespace myproject {
    namespace foo_bar {
    void Function1();
    void Function2();
    }  // namespace foo_bar
    }  // namespace myproject

7. Local Variables  
Place a function's variables in the narrowest scope possible, and initialize variables in the declaration.  
We encourage you to declare them in as local a scope as possible, and as close to the first use as possible.  
  
8) Static and Global Variables  
Variables of class type with static storage duration are forbidden.(Because they cause bags)  
We only allow static variables to contain POD data.  
Objects with static storage duration, including global variables, static variables, static class member variables, and function   static variables, must be Plain Old Data (POD):  
only ints, chars, floats, or pointers, or arrays/structs of POD.   
 
// Classes  
9) Doing Work in Constructors  
Avoid virtual method calls in constructors, and avoid initialization that can fail if you can't signal an error.  
If the work calls virtual functions, these calls will not get dispatched to the subclass implementations. Future modification to your class can quietly introduce this problem  
even if your class is not currently subclassed, causing much confusion.  
There is no easy way for constructors to signal errors, short of crashing the program (not always appropriate) or using exceptions (which are forbidden).  
If the work fails, we now have an object whose initialization code failed, so it may be an unusual state requiring a bool IsValid() state checking mechanism (or similar) which is easy to forget to call.  
You cannot take the address of a constructor, so whatever work is done in the constructor cannot easily be handed off to, for example, another thread.  
  
10. Implicit Conversions  
Do not define implicit conversions. Use the explicit keyword for conversion operators and single-argument constructors.  
The explicit keyword can be applied to a constructor or (since C++11) a conversion operator, to ensure that it can only be used when the destination type is explicit at the point of use, e.g. with a cast.  

    class Foo {
      explicit Foo(int x, double y);
      ...
    };

    void Func(Foo f);

Implicit conversions can make a type more usable and expressive by eliminating the need to explicitly name a type when it's   obvious.  
Implicit conversions can be a simpler alternative to overloading.  
List initialization syntax is a concise and expressive way of initializing objects.  
  
Implicit conversions can hide type-mismatch bugs, where the destination type does not match the user's expectation, or the user is unaware that any conversion will take place.  
Implicit conversions can make code harder to read, particularly in the presence of overloading, by making it less obvious what code is actually getting called.  
Constructors that take a single argument may accidentally be usable as implicit type conversions, even if they are not intended to do so.  
When a single-argument constructor is not marked explicit, there's no reliable way to tell whether it's intended to define an implicit conversion, or the author simply forgot to mark it.  
It's not always clear which type should provide the conversion, and if they both do, the code becomes ambiguous.  
List initialization can suffer from the same problems if the destination type is implicit, particularly if the list has only a single element.  

11. Copyable and Movable Types

Support copying and/or moving if these operations are clear and meaningful for your type. Otherwise, disable the implicitly   generated special functions that perform copies and moves. 

A copyable type allows its objects to be initialized or assigned from any other object of the same type, without changing the   value of the source. For user-defined types, the copy behavior is defined by the copy constructor and the copy-assignment   operator. string is an example of a copyable type.  

A movable type is one that can be initialized and assigned from temporaries (all copyable types are therefore movable).   std::unique_ptr<int> is an example of a movable but not copyable type. For user-defined types, the move behavior is defined by   the move constructor and the move-assignment operator.  

If you define a copy or move constructor, define the corresponding assignment operator, and vice-versa.   
If you do not want to support copy/move operations on your type, explicitly disable them using = delete in the public: section:  

12. Structs vs. Classes  

Use a struct only for passive objects that carry data; everything else is a class.  

13. Inheritance(Наследование)  

Composition is often more appropriate than inheritance. When using inheritance, make it public.  

When a sub-class inherits from a base class, it includes the definitions of all the data and operations that the parent base   class defines. In practice, inheritance is used in two major ways in C++: implementation inheritance, in which actual code is   inherited by the child, and interface inheritance, in which only method names are inherited. 

Implementation inheritance reduces code size by re-using the base class code as it specializes an existing type. Because   inheritance is a compile-time declaration, you and the compiler can understand the operation and detect errors. Interface   inheritance can be used to programmatically enforce that a class expose a particular API. Again, the compiler can detect errors,   in this case, when a class does not define a necessary method of the API.   

All inheritance should be public. If you want to do private inheritance, you should be including an instance of the base class   as a member instead.  

Do not overuse implementation inheritance. Composition is often more appropriate. Try to restrict use of inheritance to the   "is-a" case: Bar subclasses Foo if it can reasonably be said that Bar "is a kind of" Foo.  

Make your destructor virtual if necessary. If your class has virtual methods, its destructor should be virtual.  

Limit the use of protected to those member functions that might need to be accessed from subclasses. Note that data members   should be private.  

For clarity, use exactly one of override, final, or virtual when declaring an override.  

14. Multiple Inheritance  

Only very rarely is multiple implementation inheritance actually useful. We allow multiple inheritance only when at most one of   the base classes has an implementation; all other base classes must be pure interface classes tagged with the Interface suffix.  

15. Interfaces  

Classes that satisfy certain conditions are allowed, but not required, to end with an Interface suffix.  

A class is a pure interface if it meets the following requirements:  

    * It has only public pure virtual ("= 0") methods and static methods (but see below for destructor).  
    * It may not have non-static data members.  
    * It need not have any constructors defined. If a constructor is provided, it must take no arguments and it must be protected.  
     *If it is a subclass, it may only be derived from classes that satisfy these conditions and are tagged with the Interface suffix.  

16. Operator Overloading  

Operator keyword  
Do not create user-defined literals.  
The operator keyword also permits user code to define new kinds of literals using operator""  
, and to define type-conversion functions such as operator bool().  

    * Providing a correct, consistent, and unsurprising set of operator overloads requires some care, and failure to do so can lead to confusion and bugs.  
    * Overuse of operators can lead to obfuscated code, particularly if the overloaded operator's semantics don't follow convention.  
    * The hazards of function overloading apply just as much to operator overloading, if not more so.  
    * Operator overloads can fool our intuition into thinking that expensive operations are cheap, built-in operations.  
    * Finding the call sites for overloaded operators may require a search tool that's aware of C++ syntax, rather than e.g. grep.  
    * If you get the argument type of an overloaded operator wrong, you may get a different overload rather than a compiler error. For example, foo < bar may do one thing, while &foo < &bar does something totally different.  
    * Certain operator overloads are inherently hazardous. Overloading unary & can cause the same code to have different meanings depending on whether the overload declaration is visible. Overloads of &&, ||, and , (comma) cannot match the evaluation-order semantics of the built-in operators.  
    * Operators are often defined outside the class, so there's a risk of different files introducing different definitions of the same operator. If both definitions are linked into the same binary, this results in undefined behavior, which can manifest as subtle run-time bugs.  
    * User-defined literals allow the creation of new syntactic forms that are unfamiliar even to experienced C++ programmers.  

Define overloaded operators only if their meaning is obvious, unsurprising, and consistent with the corresponding built-in operators.  

Define operators only on your own types. More precisely, define them in the same headers, .cc files, and namespaces as the types they operate on. That way, the operators are available wherever the type is, minimizing the risk of multiple definitions.   
If you define an operator, also define any related operators that make sense, and make sure they are defined consistently. For example, if you overload <, overload all the comparison operators, and make sure &lt and > never return true for the same arguments.

Don't go out of your way to avoid defining operator overloads. For example, prefer to define ==, =, and &lt &lt, rather than Equals(), CopyFrom(), and PrintTo(). Conversely, don't define operator overloads just because other libraries expect them. For example, if your type doesn't have a natural ordering, but you want to store it in a std::set, use a custom comparator rather than overloading <.  

Type conversion operators are covered in the section on implicit conversions. The = operator is covered in the section on copy constructors. Overloading << for use with streams is covered in the section on streams. See also the rules on function overloading, which apply to operator overloading as well.

17. Access Control

Make data members private, unless they are static const (and follow the naming convention for constants). For technical reasons, we allow data members of a test fixture class to be protected when using Google Test).  














