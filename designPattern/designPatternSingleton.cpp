/*
 Singleton Pattern
Use Case: The Singleton pattern ensures a class has only one instance and provides a global point of access to it. This is particularly useful in embedded systems for managing shared resources like buffer pools, device interfaces, or configuration settings.
*/
#include <iostream>

class Singleton
{
private:
    static Singleton *instance;
    Singleton() {} // Private constructor

public:
    static Singleton *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Singleton();
        }
        return instance;
    }

    void doSomething()
    {
        std::cout << "Doing something with the singleton instance" << std::endl;
    }
};

Singleton *Singleton::instance = nullptr;

int main()
{
    Singleton *singleton = Singleton::getInstance();
    singleton->doSomething();
    return 0;
}
