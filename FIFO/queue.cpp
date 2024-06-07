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

    // copy assignment operator
    Queue &operator=(const Queue &other);

    // move constructor
    Queue(Queue &&other) noexcept;

    // move operator operator
    Queue &operator=(Queue &&other) noexcept;

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

// copy assignment operator
Queue &Queue::operator=(const Queue &other)
{
    if (this != &other)
    {
        // delete existing nodes in the current queue
        while (head != nullptr)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
        capacity = other.capacity;

        // copy nodes from the other queue
        Node *current = other.head;
        while (current != nullptr)
        {
            queue(current->val);
            current = current->next;
        }
    }
    return *this;
}

// move constructor
Queue::Queue(Queue &&other) noexcept : head(other.head), tail(other.tail), size(other.size), capacity(other.capacity)
{
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
    other.capacity = 0;
}
// move assignment operator
Queue &Queue::operator=(Queue &&other) noexcept
{
    if (this != &other)
    {
        // delete existing nodes in the current queue
        while (head != nullptr)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        // transfer resources from other to this
        head = other.head;
        tail = other.tail;
        size = 0;
        capacity = other.capacity;

        // Leave other in a valid but empty state
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

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
    Queue *q = new Queue(10); // constructor is triggered
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

    std::cout << "\n Shallow copy is applied:" << std::endl;
    Queue *q2 = q;             // pointer is declared and assigned
    Queue *q3 = new Queue(20); // constructor is triggered
    q3 = q;                    // pointer is reassigned
    std::cout << "capacity of q2 is " << q2->get_capacity() << std::endl;
    q2->print();
    std::cout << "capacity of q3 is " << q3->get_capacity() << std::endl;
    q3->print();

    std::cout << "\ndeep copy is used:" << std::endl;
    Queue q4 = *q; // copy constructor is triggered
    // q4 is on stack, its usage on heap is taken care by destructor
    Queue *q5 = new Queue(30); // constructor is triggered
    *q5 = *q;                  // copy assignment operator is triggered

    std::cout << "capacity of q4 is " << q4.get_capacity() << std::endl;
    q4.print();
    std::cout << "capacity of q5 is " << q5->get_capacity() << std::endl;
    q5->print();

    std::cout << "\nmove constructor:" << std::endl;

    Queue q6 = std::move(*q); // move constructor is triggered, q is changed.
    q6.print();
    std::cout << "capacity of q6 is " << q6.get_capacity() << std::endl;

    std::cout << "capacity of q6 is " << q6.get_capacity() << std::endl;
    Queue *q7 = new Queue(20);
    *q7 = std::move(*q); // move assignment operator is triggered
    std::cout << "" << std::endl;
    q7->print();
    std::cout << "capacity of q7 is " << q7->get_capacity() << std::endl;

    Queue q8(25);
    q8 = std::move(q4);
    q8.print();
    std::cout << "capacity of q8 is " << q8.get_capacity() << std::endl;

    delete q;
    return 0;
}
