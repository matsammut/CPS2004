#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

template <typename T>
class Node{
    public:
    T value;
    Node *next;

    Node(T value){
        this->value = value;
    }
};
struct graphEdge{
    int to,from;
};

template <typename T>
class DAG{
    private:
    int size_;
    Node<T> *head_ = NULL;
    Node<T> *tail_ = NULL;
    std::vector<T> *adj_list;


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
        // adj_list[value].push_back(0);
        adj_list.push_back(value);
        this->size_ += 1;
    }
    void addEdge(T valueTo,T valueFrom){

    }
    void printEdges(){
        for (const T& i : adj_list) {
            cout << i << "  ";
        }
    }
};

int main(){
    int V = 5 ;
    DAG<int> glist;
    glist.addNode(5);
    glist.addNode(2);
    printf("hi");
    glist.printEdges();
}

