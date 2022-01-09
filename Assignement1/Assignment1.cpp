#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <list>
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

template <typename T>
class DAG{
    private:
    int size_;
    Node<T> *head_ = NULL;
    Node<T> *tail_ = NULL;
    Node<T> *error_ = NULL;
    Node<T> *search = NULL;
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
        //if check cycles = 0 there are no cycles
        if (checkCycles() == 1){
            cout << "Error addition of edge " << valueFrom << " to " << valueTo << " would result in a cycle! \nAborting\n";
            tmp->row.pop_back();
            adj_list.erase(adj_list.begin() + tmp->id);
            adj_list.insert(adj_list.begin() + tmp->id,tmp->row);
        }
        
    }
    void printNodes(){
        Node<T> *tmp = head_;
        cout << "Printing nodes : \n";
        for(;;){
            cout << tmp->value << " , ";
            if (tmp->next == NULL){
                cout << "\n";
                break;
            }
            else{
                tmp = tmp->next;
            }
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
    void removeAssociatedEdges(T value){
        Node<T> *tmp = findNode(value);
        adj_list.erase(adj_list.begin() + tmp->id);

        for (std::size_t i = 0; i < adj_list.size(); i++)
        {
            for (std::size_t j = 0; j < adj_list[i].size(); j++)
            {
                if (adj_list[i][j] ==  value){
                    adj_list[i].erase(std::remove(adj_list[i].begin(),adj_list[i].end(),value));
                    break;
                }

            }
        }
    }
    void removeNode(T value){
        removeAssociatedEdges(value);
        Node<T> *tmp = findNode(value);
        Node<T> *search = head_;
        if(search->id == tmp->id){
            this->head_=this->head_->next;
            this->size_ -= 1;
            search = head_;
            for(;;){
                search->id = search->id - 1;
                if (search->next == NULL){
                    break;
                }
                else{
                    search = search->next;
                }
            }
        }
        else if(search->id != tmp->id){
            while(search->next->id != tmp->id){
                search = search->next;
            }
            search->next = tmp->next;
            search = tmp;
            for(;;){
                search->id = search->id - 1;
                if (search->next == NULL){
                    break;
                }
                else{
                    search = search->next;
                }
            }
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
        // added to have a return statement in case of NULL
        return false;
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
    void passListEdges(list<T> edges, T from){
        for (T x : edges) {
            addEdge(x,from);
	    }
    }
};

int main(){
    DAG<string> glist;
    list<string> my_list = { "friends", "are", "very", "cool" };
    glist.addNode("friends");
    glist.addNode("are");
    glist.addNode("very");
    glist.addNode("cool");
    glist.addNode("hello");
    glist.addNode("goodbye");
    glist.addNode("bet");
    // glist.addEdge(2,5);
    glist.passListEdges(my_list,"hello");
    glist.addEdge("bet","goodbye");
    glist.addEdge("hello","goodbye");
    glist.printEdges();
    glist.removeNode("bet");
    glist.printNodes();
    glist.printEdges();
    
    
}
