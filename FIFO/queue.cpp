#include <iostream>

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
    Queue(int cap) : head(nullptr), tail(nullptr), size(0), capacity(cap) {}

    ~Queue()
    {
        while (head != nullptr)
        {
            Node *temp = head;
            head = temp->next;
            delete temp;
        }
    }

    Node *dequeue();
    void queue(int val);
    int get_size();
    void print();
};

// copy assignment operator, move constructor, and move assignment operator

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
    std::cout << "size of the queue is: " << q->get_size() << std::endl;

    q->dequeue();
    std::cout << "size of the queue is: " << q->get_size() << std::endl;
    q->dequeue();
    std::cout << "size of the queue is: " << q->get_size() << std::endl;
    q->dequeue();
    std::cout << "size of the queue is: " << q->get_size() << std::endl;
    // Node *head = q->dequeue();
    // std::cout << "value of head is: " << head->val << std::endl;
}