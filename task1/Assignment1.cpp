#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <list>
using namespace std;

// linked list used to create new noddes
template <typename T>
class Node{
    public:
    T value;
    int id;
    std::vector<T> row;
    Node *next;
    
    // each node has a templated value and an id
    // the id is to prevent confusion if two nodes have the same value
    Node(T value,int id){
        this->value = value;
        this->id = id;
    }

};

// DAG class
template <typename T>
class DAG{
    private:
    // holds the size (amount of nodes) in the DAG
    int size_;
    Node<T> *head_ = NULL;
    Node<T> *tail_ = NULL;
    Node<T> *error_ = NULL;
    Node<T> *search = NULL;
    // a vector of vectors holds the edges
    // this makes it so every node's id has a vector with all the edges that it points to
    std::vector<vector<T>> adj_list;



    public:
    DAG(){
        // stores how many nodes are in the data structure
        // initially set to 0
        this->size_ = 0;
    }
    // function used to add a node
    void addNode(T value){
        // checks if it is the first node and if so the head needs to be added first
        if (this->head_ == NULL){
            // new node is created
            this->head_ = new Node<T>(value,size_);
            // the node is given its own vector in the adj_list to handle its edges
            adj_list.push_back(this->head_->row);
            this->tail_ = this->head_;
        }
        else{
            this->tail_->next = new Node<T>(value,size_);
            this->tail_ = this->tail_->next;
            adj_list.push_back(this->tail_ ->row);
        }
        // the size of the DAG is incremeneted
        this->size_ += 1;
    }
    // function checks if a node with the parsed value exists
    bool checkNodeExist(T value){
        // it starts looking from the head of the list
        Node<T> *tmp = head_;
        // loops for the duration of the  linked list
        for(;;){
            // checks if the value in the node matches the parsed value
            if (tmp->value == value){
                return true;
            }
            // if the next is null then the linked list has been exhausted
            else if(tmp->next == NULL){
                return false;
            }
            // goes to the next node to check its value
            else{
                tmp = tmp->next;
            }
        }
    }
    
    // function used to find and return an node in the linked list with the parsed value
    decltype(auto) findNode(T value){
        // it starts looking from the head of the list
        Node<T> *tmp = head_;
        // loops for the duration of the  linked list
        for(;;){
            // checks if the value in the node matches the parsed value
            if (tmp->value == value){
                // returns the found node
                return tmp;
            }
            // if the next is null then the linked list has been exhausted
            // returns a Null node
            else if(tmp->next == NULL){
                cout << "Error: Node not found";
                tmp = error_;
                return tmp;
            }
            // moves on the the next node to check it
            else{
                tmp = tmp->next;
            }
        }
    }

    // function used to add a node from a value to a value
    void addEdge(T valueTo,T valueFrom){
        // checks first that both nodes exits and if they dont it returns an error message
        if (checkNodeExist(valueFrom)== false || checkNodeExist(valueTo)== false){
            cout << "Error: Node not found \n";
            return;
        }
        // uses findNode to get the from node
        Node<T> *tmp = findNode(valueFrom);
        // checks if the node returned is null if it is
        if (tmp != NULL){
            // the To edge is added to the vector of the from edge
            tmp->row.push_back(valueTo);
            // adj_list is updated with the new values
            adj_list.erase(adj_list.begin() + tmp->id);
            adj_list.insert(adj_list.begin() + tmp->id,tmp->row);
        }
        //if check cycles = 0 there are no cycles
        if (checkCycles() == 1){
            // if a cycle is detected then an error message is outputted
            cout << "Error addition of edge " << valueFrom << " to " << valueTo << " would result in a cycle! \nAborting\n";
            // the steps are reverted
            tmp->row.pop_back();
            adj_list.erase(adj_list.begin() + tmp->id);
            adj_list.insert(adj_list.begin() + tmp->id,tmp->row);
        }   
    }

    // function prints out all the nodes in the DAG
    void printNodes(){
        Node<T> *tmp = head_;
        cout << "Printing nodes : \n";
        // the linked list is looped through and all nodes are printed
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

    // function prints out the adjacency list
    void printEdges(){
        for (std::size_t i = 0; i < adj_list.size(); i++)
        {
            // prints out the node and it's connected edges (the ones it's pointing to)
            cout << "Node " << i << "-->";
            for (std::size_t j = 0; j < adj_list[i].size(); j++)
            {
                cout << adj_list[i][j] << " , ";
            }
            printf("\n");
        }  
    }

    // removes all the edges connecting to a node
    void removeAssociatedEdges(T value){
        Node<T> *tmp = findNode(value);
        adj_list.erase(adj_list.begin() + tmp->id);

        // the adjacency list is looped through and all associations with that node are removed
        for (std::size_t i = 0; i < adj_list.size(); i++)
        {
            for (std::size_t j = 0; j < adj_list[i].size(); j++)
            {
                if (adj_list[i][j] ==  value){
                    // node is removed
                    adj_list[i].erase(std::remove(adj_list[i].begin(),adj_list[i].end(),value));
                    break;
                }

            }
        }
    }

    // function that removes nodes
    void removeNode(T value){
        // all the edges connected to this node are removed
        removeAssociatedEdges(value);
        // the node to be removed is found
        Node<T> *tmp = findNode(value);
        // search is used to get the node before the node to be removed so we may skip over it
        Node<T> *search = head_;
        // if the Node to be removed is the head
        if(search->id == tmp->id){
            // the head is set to be the next node in the list
            this->head_=this->head_->next;
            // size of the DAG is decremented
            this->size_ -= 1;
            search = head_;
            // the id of all nodes is decremented to represent the removal
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
        // if it is not the head
        else if(search->id != tmp->id){
            // the list is searched through checking when the "search"'s next is equal to the node to be removed 
            while(search->next->id != tmp->id){
                search = search->next;
            }
            // the removed node is now set to be skipped in the linked list
            search->next = tmp->next;
            search = tmp;
            // all the nodes after the removed node has their id decremented to represent the removal
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

   // checkCycles function (below) is overloaded
   // recursion is used to follow each path to it's end
   // if a node is encountered more than once in this path there is a cycle
   // the id of the node it should continue from is parsed along with the visited vector
    bool checkCycles(vector<bool> visited,T checkId){  
        Node<T> *tmp = findNode(checkId);
        if (tmp !=NULL){
            // if the node has already been visited return true
            if (visited[tmp->id] == true){
                return true;
            }
            // the nodes value is changed to show it has been visited
            visited[tmp->id] = true;
            // the path of this node is now followed
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
    // function checks for any cycles in the adjacency list
    // function will go through the adj_list following though each path of each edge
    // if a node is visited more than once in a path then there is a cycle in the adjacency list
    // a -> b -> c -> a is a cycle

    bool checkCycles(){
        // visited vector is set to the size of the vector of vectors
        // initially set to all 0's
        // when a node is visited this is set to a 1
        vector<bool> visited(size_,false);

        // adjecency list is looped through
        for (std::size_t i = 0; i < adj_list.size(); i++)
        {
            // for each vector in the vector it starts by setting that vector's id to true
            visited[i] = true;
            // each of the nodes that this node points to also have to have their paths followed to termination
            for (std::size_t j = 0; j < adj_list[i].size(); j++)
            {
                // the overloaded function is called to followm the path of every edge in this vector
                if (checkCycles(visited,adj_list[i][j]) == true){
                    return true;
                }
            }
            // moves on to the next vector in the adjacency list 
            visited[i]= false;
        }
        return false;
    }
    // a list of edges is parsed and added to the adjacency list
    void passListEdges(list<T> edges, T from){
        for (T x : edges) {
            addEdge(x,from);
	    }
    }
    // the adjacency list is returned
    decltype(auto) returnListEdges(){
        return adj_list;
    }
};

int main(){
    DAG<char> glist;
    // list<string> my_list = { "friends", "are", "very", "cool" };
    glist.addNode('a');
    glist.addNode('b');
    glist.addNode('c');
    glist.addNode('d');;
    glist.addEdge('b','a');
    glist.addEdge('c','b');
    glist.addEdge('d','c');
    glist.addEdge('b','d');
    // glist.printEdges();
    glist.removeNode('b');
    glist.printNodes();
    glist.printEdges();
    
    
}
