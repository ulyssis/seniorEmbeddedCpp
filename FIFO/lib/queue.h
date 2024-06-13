// queue.h
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
    int queue(int val);
    int get_size() const;
    void print();
    int get_capacity() const;
};