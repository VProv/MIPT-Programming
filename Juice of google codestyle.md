Adaptation of https://google.github.io/styleguide/cppguide.html

// Background
1) 
#ifndef FOO_BAR_BAZ_H_
#define FOO_BAR_BAZ_H_
...
#endif 
Нужно использовать полный пусть файла в проекте.
2) Avoid forward declaration(Объявление до определения).
3) Inline functions: only less than 10 lines. Beware of distructors, which are often longer than they appear.
Virtual and recursive functions are not normaly inline.The main reason for making a virtual function inline 
is to place its definition in the class, either for convenience or to document its behavior, e.g., for accessors and mutators.
4) Names and Order of Includes.
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
5) Namespaces. (They prevent name collisions at compile time or runtime)
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

6) Nonmember, Static Member, and Global Functions
Static methods should be closely related with static data in class. You can create new class for nonmember and static member functions.
Prefer placing nonmember functions in a namespace.
namespace myproject {
namespace foo_bar {
void Function1();
void Function2();
}  // namespace foo_bar
}  // namespace myproject

7) Local Variables
Place a function's variables in the narrowest scope possible, and initialize variables in the declaration.
We encourage you to declare them in as local a scope as possible, and as close to the first use as possible.

8) Static and Global Variables
Variables of class type with static storage duration are forbidden.(Because they cause bags)
We only allow static variables to contain POD data.
Objects with static storage duration, including global variables, static variables, static class member variables, and function static variables, must be Plain Old Data (POD):
only ints, chars, floats, or pointers, or arrays/structs of POD. 

// Classes
9) Doing Work in Constructors
Avoid virtual method calls in constructors, and avoid initialization that can fail if you can't signal an error.
If the work calls virtual functions, these calls will not get dispatched to the subclass implementations. Future modification to your class can quietly introduce this problem
even if your class is not currently subclassed, causing much confusion.
There is no easy way for constructors to signal errors, short of crashing the program (not always appropriate) or using exceptions (which are forbidden).
If the work fails, we now have an object whose initialization code failed, so it may be an unusual state requiring a bool IsValid() state checking mechanism (or similar) which is easy to forget to call.
You cannot take the address of a constructor, so whatever work is done in the constructor cannot easily be handed off to, for example, another thread.

10) Implicit Conversions
Do not define implicit conversions. Use the explicit keyword for conversion operators and single-argument constructors.
The explicit keyword can be applied to a constructor or (since C++11) a conversion operator, to ensure that it can only be used when the destination type is explicit at the point of use, e.g. with a cast.
class Foo {
  explicit Foo(int x, double y);
  ...
};

void Func(Foo f);

Implicit conversions can make a type more usable and expressive by eliminating the need to explicitly name a type when it's obvious.
Implicit conversions can be a simpler alternative to overloading.
List initialization syntax is a concise and expressive way of initializing objects.

Implicit conversions can hide type-mismatch bugs, where the destination type does not match the user's expectation, or the user is unaware that any conversion will take place.
Implicit conversions can make code harder to read, particularly in the presence of overloading, by making it less obvious what code is actually getting called.
Constructors that take a single argument may accidentally be usable as implicit type conversions, even if they are not intended to do so.
When a single-argument constructor is not marked explicit, there's no reliable way to tell whether it's intended to define an implicit conversion, or the author simply forgot to mark it.
It's not always clear which type should provide the conversion, and if they both do, the code becomes ambiguous.
List initialization can suffer from the same problems if the destination type is implicit, particularly if the list has only a single element.

11) Copyable and Movable Types

