#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

template <typename T>
class Node{
    public:
    T value;
    int id;
    std::vector<T> row;
    Node *next;
    

    Node(T value,int id){
        this->value = value;
        this->id = id;
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
    Node<T> *error_ = NULL;
    std::vector<vector<T>> adj_list;


    public:
    DAG(){
        // stores how many nodes are in the data structure
        this->size_ = 0;
    }
    void addNode(T value){
        if (this->head_ == NULL){
            this->head_ = new Node<T>(value,size_);
            adj_list.push_back(this->head_->row);
            this->tail_ = this->head_;
        }
        else{
            this->tail_->next = new Node<T>(value,size_);
            this->tail_ = this->tail_->next;
            adj_list.push_back(this->tail_ ->row);
        }
        adj_list[value].push_back(0);
        // adj_list.push_back(value);
        this->size_ += 1;
    }
    bool checkNodeExist(T value){
        Node<T> *tmp = head_;
        for(;;){
            if (tmp->value == value){
                return true;
            }
            else if(tmp->next == NULL){
                return false;
            }
            else{
                tmp = tmp->next;
            }
        }
    }
    
    decltype(auto) findNode(T value){
        Node<T> *tmp = head_;
        for(;;){
            if (tmp->value == value){
                return tmp;
            }
            else if(tmp->next == NULL){
                cout << "Error: Node not found";
                tmp = error_;
                return tmp;
            }
            else{
                tmp = tmp->next;
            }
        }
    }
    void addEdge(T valueTo,T valueFrom){
        
        if (checkNodeExist(valueFrom)== false || checkNodeExist(valueTo)== false){
            cout << "Error: Node not found \n";
            return;
        }
        Node<T> *tmp = findNode(valueFrom);
        if (tmp != NULL){
            tmp->row.push_back(valueTo);
            adj_list.erase(adj_list.begin() + tmp->id);
            adj_list.insert(adj_list.begin() + tmp->id,tmp->row);
        }
        
    }
    void printEdges(){
        for (std::size_t i = 0; i < adj_list.size(); i++)
        {
            cout << "Node " << i << "-->";
            for (std::size_t j = 0; j < adj_list[i].size(); j++)
            {
                cout << adj_list[i][j] << " , ";
            }
            printf("\n");
        }
        
    }
    bool checkCycles(vector<bool> visited,T checkId){  
        Node<T> *tmp = findNode(checkId);
        if (tmp !=NULL){
            if (visited[tmp->id] == true){
                return true;
            }
            visited[tmp->id] = true;
            for(std::size_t i = 0; i <adj_list[tmp->id].size();i++){
                if (checkCycles(visited, adj_list[tmp->id][i]) == true){
                    return true;
                }
            }
            return false;
        }
    }
    bool checkCycles(){
        vector<bool> visited(size_,false);

         for (std::size_t i = 0; i < adj_list.size(); i++)
        {
            visited[i] = true;
            for (std::size_t j = 0; j < adj_list[i].size(); j++)
            {
                if (checkCycles(visited,adj_list[i][j]) == true){
                    return true;
                }
            }
            visited[i]= false;
        }
        return false;
    }
};

int main(){
    int V = 5 ;
    DAG<int> glist;
    glist.addNode(5);
    // glist.addNode(6);
    glist.addNode(2);
    // glist.addEdge(2,5);
    // glist.addEdge(6,5);
    glist.addEdge(5,2);
    // glist.addEdge(8,13);
    // glist.addEdge(9,5);
    glist.printEdges();
    bool check = glist.checkCycles();
    cout << check << "\n";
    
}
