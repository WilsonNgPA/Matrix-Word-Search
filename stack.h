//Ng, Pei Aou Wilson 100332292
//stack h file

#ifndef STACK_H
#define STACK_H


template<typename T>
class stack{
    public:
        //Default constructor
        stack();
        //Push x into stack
        void push(T x);
        //Pop top element from stack
        T pop();
        //Returns top element from stack
        T peek();
        //Check if stack is empty
        bool isEmpty();
        //Destructor
        ~stack();
        //Copy constructor
        stack(const stack<T>& s);
        //Assignment operator
        const stack<T>& operator=(const stack<T>& s);
    private:
    //node struct
        struct node{
            T data;
            node* next;
        };
        //Top node of stack
        node* top;
        //Copy stack
        node* copyStack(node* s);
        //Delete stack
        node* deleteStack(node* s);
};

//Copy stack
template<typename T>
typename stack<T>::node* stack<T>::copyStack(node* s) {
    if(!s) {
        return s;
    }
    return new node{s -> data, copyStack(s -> next)};
}

//Delete stack
template<typename T>
typename stack<T>::node* stack<T>::deleteStack(node* s) {
    if(s) {
        deleteStack(s -> next);
        delete s;
    }
    return nullptr;
}

//Default constructor
template<typename T>
stack<T>::stack() {
    top = nullptr;
}

//Checks if stack is empty
template<typename T>
bool stack<T>::isEmpty() {
    return !top;
}

//Push x into stack
template<typename T>
void stack<T>::push(T x) {
    top = new node{x, top};
}

//Look at top element in stack
template<typename T>
T stack<T>::peek() {
    if(isEmpty()) {
        std::cerr << "Invalid peek" << std::endl;
        exit(1);
    }
    return top -> data;
}

//Remove top element from stack
template<typename T>
T stack<T>::pop() {
    T ret_val = peek();
    node* temp = top -> next;
    delete top;
    top = temp;
    return ret_val;
}

//Destructor
template<typename T>
stack<T>::~stack() {
    node* temp;
    while(top) {
        temp = top -> next;
        delete top;
        top = temp;
    }
}

//Copy constructor
template<typename T>
stack<T>::stack(const stack<T>& s) {
    top = copyStack(s.top);
}

//Assignment operator
template<typename T>
const stack<T>& stack<T>::operator=(const stack<T>& s) {
    if(&s == this) {
        return *this;
    }
    top = deleteStack(top);
    top = copyStack(s.top);
    return *this;
}

#endif
