#include <iostream>

class Node
{
public:
    Node() : val(), next(nullptr) {}
    Node(int val)
    {
        next = nullptr;
        prev = nullptr;
        this->val = val;
    }
    ~Node() {}
    int val;
    Node *next;
    Node *prev;
};

class Queue
{
private:
    Node *head;
    Node *tail;
    int size;
    int capacity;

public:
    Queue(int cap, int size) : head(nullptr), tail(nullptr), size(size), capacity(cap)
    {
        if (!size)
        {
            Node *newNode = new Node(0);
            head = newNode;
            Node *movingHead = head;

            for (int i = 1; i < size - 1; i++)
            {
                movingHead->next = newNode;
                newNode->prev = movingHead;
                movingHead = newNode;
            }
            tail = movingHead;
        }
    }

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
    void queue(Node *node);
    int get_size();
    void print();
};

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
void Queue::queue(Node *node)
{
    if (tail == nullptr)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    size++;
}

Node *Queue::dequeue()
{
    if (tail == nullptr)
    {
        size = 0;
        return nullptr;
    }
    else if (tail->prev != nullptr)
    {
        Node *temp = tail;
        tail = temp->prev;
        tail->next = temp;
        size--;
        return temp;
    }
    else
    {
        size = 0;
        head = nullptr;
        tail = nullptr;
        return tail;
    }
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
        Node *n = new Node(i);
        q->queue(n);
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