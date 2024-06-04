#include <iostream>
#include <utility>

class Node
{
public:
    Node() : val(), next(nullptr) {}
    Node(int val)
    {
        next = nullptr;
        this->val = val;
    }
    ~Node() {}
    int val;
    Node *next;
};

class Queue
{
private:
    Node *head;
    Node *tail;
    int size;
    int capacity;

public:
    // constructor
    Queue(int cap) : head(nullptr), tail(nullptr), size(0), capacity(cap) {}

    // deconstructor
    ~Queue()
    {
        while (head != nullptr)
        {
            Node *temp = head;
            head = temp->next;
            delete temp;
        }
    }

    // copy constructor
    Queue(const Queue &other);

    // copy assignment constructor
    Queue &operator=(Queue &other);

    Node *dequeue();
    void queue(int val);
    int get_size();
    void print();
    int get_capacity();
};

// copy constructor
Queue::Queue(const Queue &other) : head(nullptr), tail(nullptr), size(0), capacity(other.capacity)
{
    Node *current = other.head;
    while (current != nullptr)
    {
        queue(current->val);
        current = current->next;
    }
}

// copy assignment constructor
Queue &Queue::operator=(Queue &other)
{
    if (this != &other)
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
        head = other.head;
        tail = other.tail;
        size = other.size;
        capacity = other.capacity;

        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
    return *this;
}

//  move constructor, and move assignment operator

void Queue::print()
{
    if (head == nullptr)
    {
        std::cout << "this queue is empty" << std::endl;
    }
    else
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            std::cout << temp->val << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
}

int Queue::get_capacity()
{
    return this->capacity;
}

void Queue::queue(int val)
{
    if (size == capacity)
    {
        std::cout << "the queue is full!" << std::endl;
    }
    Node *node = new Node(val);
    if (tail == nullptr)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
    size++;
}

Node *Queue::dequeue()
{
    if (head == nullptr)
    {
        size = 0;
        return nullptr;
    }

    Node *temp = head;
    head = head->next;
    if (head == nullptr)
    {
        tail = nullptr;
    }
    size--;
    temp->next = nullptr;
    return temp;
}

int Queue::get_size()
{
    return size;
}

int main()
{

    std::cout << "test: " << std::endl;
    Queue *q = new Queue(10);
    for (int i = 0; i < 10; i++)
    {
        q->queue(i);
    }

    q->print();
    std::cout << "capacity of q is " << q->get_capacity() << std::endl;
    std::cout << "size of the queue is: " << q->get_size() << std::endl;

    q->dequeue();
    // std::cout << "size of the queue is: " << q->get_size() << std::endl;
    q->dequeue();
    // std::cout << "size of the queue is: " << q->get_size() << std::endl;
    q->dequeue();
    std::cout << "size of the queue is: " << q->get_size() << std::endl;

    Queue *q2 = q;             // pointer is declared and assigned
    Queue *q3 = new Queue(20); // trigger constructor
    q3 = q;                    // pointer is reassigned
    q2->print();
    std::cout << "capacity of q2 is " << q2->get_capacity() << std::endl;
    std::cout << "capacity of q3 is " << q3->get_capacity() << std::endl;

    delete q;
    // delete q3;

    Queue q4 = *q;             // copy constructor is triggered
    Queue *q5 = new Queue(30); // constructor is trigger
    *q5 = *q;                  // copy assignment operator is triggered

    return 0;
}
