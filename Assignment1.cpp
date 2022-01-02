#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

template <typename T>
class Node{
    public:
    T value;
    Node *next;

    Node(T value){
        this->value = value;
    }
};

template <typename T>
class DAG{
    private:
    int size_;
    Node<T> *head_ = NULL;
    Node<T> *tail_ = NULL;

    public:
    DAG(){
        // stores how many nodes are in the data structure
        this->size_ = 0;
    }
    void addNode(T value){
        if (this->head_ == NULL){
            this->head_ = new Node<T>(value);
            this->tail_ = this->head_;
        }
        else{
            this->tail_->next = new Node<T>(value);
            this->tail_ = this->tail_->next;
        }
        this->size_ += 1;
    }
};

int main(){
    DAG<int> glist;
    glist.addNode(5);
    glist.addNode(2);
    printf("hi");
}

