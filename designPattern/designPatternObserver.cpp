/*
Observer Pattern
Use Case: The Observer pattern is ideal in scenarios where changes in one object's state need to be communicated to other objects without those objects needing to constantly check (poll) the state of the first object. This pattern is widely used in GUI toolkits and event management systems, where changes, such as sensor data updates, need to trigger multiple reactions.
*/
#include <iostream>
// #include <vector>
// #include <algorithm>

// Observer interface
class Observer
{
public:
    virtual void update(int value) = 0;
};

// Concrete Observer
class ConcreteObserver : public Observer
{
private:
    int observerState;

public:
    void update(int value) override
    {
        observerState = value;
        std::cout << "Observer state updated to " << observerState << std::endl;
    }
};

// Subject interface
class Subject
{
private:
    std::vector<Observer *> observers;

public:
    void attach(Observer *observer)
    {
        observers.push_back(observer);
    }
    void detach(Observer *observer)
    {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void notify(int value)
    {
        for (Observer *observer : observers)
        {
            observer->update(value);
        }
    }
};

// Concrete Subject
class ConcreteSubject : public Subject
{
private:
    int subjectState;

public:
    void setState(int value)
    {
        subjectState = value;
        notify(subjectState); // Notify all observers about the change
    }
};

int main()
{
    ConcreteSubject subject;
    ConcreteObserver observer1, observer2;

    subject.attach(&observer1);
    subject.attach(&observer2);

    subject.setState(123); // Both observers will be notified
    return 0;
}
