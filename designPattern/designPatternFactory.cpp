/*
Factory Method Pattern
Use Case: The Factory Method pattern is used when a method returns one of several possible classes that share a common base class, based on the input parameters provided to the method. This pattern is useful in embedded systems for managing device drivers or resources where the exact type of object (e.g., specific sensor or device driver) might not be known at compile time.
*/

#include <iostream>

// Product interface
class Product
{
public:
    virtual void operate() = 0;
    virtual ~Product() {}
};

// Concrete Products
class ConcreteProductA : public Product
{
public:
    void operate() override
    {
        std::cout << "Operating ConcreteProductA" << std::endl;
    }
};

class ConcreteProductB : public Product
{
public:
    void operate() override
    {
        std::cout << "Operating ConcreteProductB" << std::endl;
    }
};

// Creator
class Creator
{
public:
    virtual Product *factoryMethod(int type)
    {
        if (type == 0)
        {
            return new ConcreteProductA();
        }
        else
        {
            return new ConcreteProductB();
        }
    }
};

int main()
{
    Creator creator;
    Product *product = creator.factoryMethod(0);
    product->operate();
    delete product;
    return 0;
}
