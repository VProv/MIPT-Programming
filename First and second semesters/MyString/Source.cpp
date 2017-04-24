#include <iostream>
using namespace std;

class A
{
public:
    int getA()
    {
        return a;
    }
    void setA(int b)
    {
        a = b;
    }
private:
    friend ostream & operator<< (ostream & output, A & a)
    {
        output << "a = " << a.getA();
        return output;
    }
    int a;
};

int main()
{
    A a;
    a.setA(5);
    cout << a << endl;
    return 0;
}