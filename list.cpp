#include <iostream>


template <class T>
class Node {
public:
    Node* next;
    T _value;
    Node(const T& initVal): _value(initVal), next(nullptr) {}
    ~Node() {}

};

template <class T>
class List {
public:
    Node<T>* head;
    Node<T>* tail;
    int len;

    List() : head(nullptr), tail(nullptr), len(0) {}

    template <class ... Args>
    List(Args... args): head(nullptr), tail(nullptr), len(0){
        (pushBack(args), ...);
    }


    void pushBack(T value){
        this->len += 1;
        Node<T>* newNode = new Node<T>(value);
        if(this->head == nullptr){
            this->head = newNode;
        }
        if(this->tail != nullptr){
            this->tail->next = newNode;
        }
        this->tail = newNode;
    }

    void pushFront(T value){
        this->len += 1;
        Node<T>* newNode = new Node<T>(value);
        if(this->tail == nullptr){
            this->tail = newNode;
        }
        if(this->head != nullptr){
            newNode->next = this->head;
        }
        this->head = newNode;
    }

    void popFront(){
        if(this->head == nullptr) return;
        if (this->head == this->tail) {
            delete this->tail;
            this->head = this->tail = nullptr;
            this->len = 0;
        }
        else{
            Node<T>* node = this->head;
            this->head = node->next;
            delete node;
            this->len = this->len -1;
        }
    }
    void popBack(){
        if(this->tail == nullptr) return;
        if (this->head == this->tail) {
            delete this->tail;
            this->head = this->tail = nullptr;
            this->len = 0;
        }

        Node<T>* node = this->head;
        while(node->next != this->tail){
            node = node->next;
        }
        node->next = NULL;
        delete this->tail;
        this->tail = node;
        this->len = this->len -1;

    }
    void insert(int position, T value){
        if(position >= this->len){
            throw std::out_of_range("list index out of range");}

        Node<T>* left = this->getAt(position);
        Node<T>* right = left->next;

        if(right == nullptr) {
            this->pushBack(value);
        }else {
            Node<T>* newNode = new Node<T>(value);
            left->next = newNode;
            newNode->next = right;
        }




    }

    void remove(int position){
        if(position >= this->len){
            throw std::out_of_range("list index out of range");}
        if(position == 0){
            this->popFront();
            return;
        }

        Node<T>* left = this->getAt(position - 1);
        Node<T>* node = left->next;
        Node<T>* right = node->next;

        if(right == nullptr) {
            this->popBack();
            return;
        }
        left->next = right;
        delete node;
    }

    int length(){
       return this->len;
    }


    Node<T>* getAt(int position){
        if(position < this->len){
            if(position < 0){
                position = this->len + position;
                if(position < 0 ){
                    throw std::out_of_range("list index out of range");
                }
                Node<T>* node = this->head;
                for(int i = 0; i < position; i++){
                    node = node->next;
                }
                return node;
            }

            Node<T>* node = this->head;
            for(int i = 0; i < position; i++){
                node = node->next;
            }
            return node;
        }
        else {throw std::out_of_range("list index out of range");}
    }



    void show(){
        for(Node<int>* node = this->head; node!= nullptr; node = node->next){
            if(node != this->tail) {
                std::cout << node->_value << ",";
            }
            else {
                std::cout << node->_value;
            }
        }
        std::cout<< std::endl;
    }



};


int main() {
    List<int> a(2,3,4);
    std::cout<< "LEN = " << a.length()<< std::endl;
    a.pushBack(5);
    a.pushFront(1);

    a.show();

    std::cout<< "LEN = " << a.length()<< std::endl;
    a.remove(1);
    a.show();



    return 0;
}

