#include <iostream>
#include <limits>


using namespace std;

/// @brief Linked list node element which points to the next and the previous nodes
/// @tparam T Generic type of the node element value
template <typename T>
struct Node
{
    // Next node element pointer
    Node<T> *next_node = nullptr;
    // Prevoius node element pointer
    Node<T> *prev_node = nullptr;

    // Node value
    T value;

    /// @brief Get the next linked element
    /// @return pointer to the next linked element
    Node<T>* next(){
      return next_node;  
    }

    /// @brief Get the previous linked element
    /// @return pointer to the previous linked element
    Node<T>* prev(){
        return prev_node;
    }
};

/// @brief Linked list to hold list elements of the specified type
/// @tparam T Generic type of the list elements
template <typename T>
struct List
{
    Node<T> *first = nullptr;
    Node<T> *last = nullptr;

    /// @brief Adds element to the end of the list
    /// @param t Generic type element to be added to the list
    /// @return Pointer to the node element created
    Node<T>* add(T t){
        // Calculate size needed for memory allocation
        size_t size = sizeof(Node<T>);

        // Allocate memory size of size_t and cast the pointer to a Node pointer for use
        Node<T> *node = (Node<T>*) malloc(size);

        node->value = t;        // Set the value of the node
        
        if(last){               // check that the list is not empty by checking if it has a last node pointer
            node->prev_node = last;
            last->next_node = node;
            last = node;        // change the last element to the new node
        }else{
            // the list must be empty
            // set the last and the first element to this new node
            first = node;   
            last = node;
        }
        // Return the new node for further operations by the caller.
        return node;
    }


    /// @brief Removes an element from the list
    /// @param node The pointer to the element to be deleted
    void remove(Node<T> *node){
        if(node){   // check if node pointer provided is not a nullptr to avoid segmentation faults
            
            if(node->next_node && node->prev_node){   // Intermidiate element
                // Remove the node element and reconnect the broken link btwn the previous and the next element
                node->next_node->prev_node = node->prev_node;
                node->prev_node->next_node = node->next_node;
                // free the memory block
                free(node);

            }else if(node->next_node){               // First element
                // since we are removing the first element 
                // Nullify the previous node pointer of the next element so as to "shift" elements to the left
                node->next_node->prev_node = nullptr;

                // set the next node as the first element since we are removing the first element
                first = node->next_node;
                // free the memory block
                free(node);

            }else if(node->prev_node){               // Last element
                // since we are removing the last element 
                // Nullify the next node pointer of the previous element so as to "shift" elements to the left
                node->prev_node->next_node = nullptr;

                // set the previous node as the last element since we are removing the last element
                last = node->prev_node;
                // free the memory block
                free(node);

            }else{
                // No idea what element this is, but free it anyway
                // must be the last and the first element in the list (a list with one node)
                if(first == node){
                    first = nullptr;
                    last = nullptr;
                }
                free(node);
            }
        }else{
            // An invalid pointer was provided
            return;
        }
    }

    /// @brief Checks if list is empty
    /// @return True if list is empty
    bool empty(){
        // if the first element isa nullptr then the list is empty
        return first == nullptr;
    }

    /// @brief Clears all the elements from the linked list
    void clear(){
        // remove the last element while the list is not empty
        while (!empty())
        {
            remove(last);
        }
        
    }
};


int main(){
    int size = 0;       // size of the elements to input
    List<string> names; // linkedlist instance

    while (true)        // Loop infinately until user provides correct input
    {
        // prompt user to insert size
        cout<<"Enter number of names to insert: ";
        cin>>size;
        
        //  check if user provided a string instead of integer
        if(!cin){   // handle bad user input
            cin.clear();    // clear input stream buffer
            cout<<"Invalid value, Try again\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // force user to input the value again
            continue;
        }

        if(size< 0){
            cout<<"Value out of range\n";
            // force user to input the value again
            continue;
        }
        // exit the loop if all checks passed
        break;
    }


    for (int i = 0; i < size; i++)
    {
        // prompt user to insert names
        string name;
        cout<<i+1<<": ";
        cin>>name;
        // add name to linked list
        names.add(name);
    }
    
    // output the names
    cout<<"Names\n=============\n";
    // get the first element in the loop
    Node<string> *node = names.first;

    while (node)        // loop until no next element is available (node is null)
    {
        cout<<node->value<<endl;
        // get and assign the next element
        node = node->next();
    }


    return 0;
}
// we are done here