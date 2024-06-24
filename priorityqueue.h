/// Priority Queue 
/// System: VSCode on MacOS
/// Nuha Abougoash, 2023

#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)
    
    /// Recursively prints out the values of the tree nodes in output stream
    void toStringRecursive(NODE* node, ostream& output) {
        // return nothing if there is no tree
        if (node == nullptr) {
            return;
        }
        // call the function recursively on the left child of curr node
        toStringRecursive(node->left, output);
        
        // prints the priority & value of the current node
        output << node->priority << " value: " << node->value;
        
        // print the priority & value of each dup node, if they exist
        if (node->dup) {
            NODE* curr = node->link;
            while (curr != nullptr) {
                output << endl << node->priority << " value: " << curr->value;
                curr = curr->link;
            }
        }
        output << endl;

        //  calls the function recursively on the right child of curr node
        toStringRecursive(node->right, output);
    }

    /// recursively deletes all the nodes in the tree
    void clearRecursive(NODE* node) {
        // reutrn nothing if there is no tree
        if (node == nullptr) {
            return;
        }

        // recursively call function on the left & right children of curr node
        clearRecursive(node->left);
        clearRecursive(node->right);

        // deletes all the exisiting dup nodes of curr node
        NODE* curr = node->link;
        while (curr != nullptr) {
            NODE* next = curr->link;
            delete curr;
            curr = next;
        }

        // delete current node
        delete node;
    }

    /// recursively creates a deep copy of the tree rooted at other 
    NODE* copy(NODE* other) {
        // return nothing if the tree is empty
        if (other == nullptr) {
            return nullptr;
        }

        // creates new node and copies values of corresponding node 'other' to it
        NODE* newNode = new NODE;
        newNode->priority = other->priority;
        newNode->value = other->value;
        newNode->dup = other->dup;
        newNode->link = nullptr;
        newNode->parent = nullptr;
        // recursively copies left & right subtrees of 'other' to corresponding subtrees of 'newNode'
        newNode->left = copy(other->left);
        newNode->right = copy(other->right);

        // check if 'other' has any duplicates
        if (other->dup) {
            // create deep copy of dupliactes and assign to the corresponding link pointer of 'newNode'
            NODE* currOther = other->link;
            NODE* currNew = newNode;
            // iterate thru list of duplicates
            while (currOther != nullptr) {
                // create new node newDup for each duplicate
                NODE* newDup = new NODE;
                // copy its values from corresponding node 'currOther'
                newDup->priority = currOther->priority;
                newDup->value = currOther->value;
                newDup->dup = true;
                newDup->link = nullptr;
                newDup->parent = nullptr;
                newDup->left = nullptr;
                newDup->right = nullptr;

                // update link pointer of 'currNew' to point to 'newDup'
                currNew->link = newDup;
                // update 'currNew' and 'currOther' to point to next nodes in list
                currNew = newDup;
                currOther = currOther->link;
            }
        }
        return newNode;
    }

    /// recursively compare two pointers to check if they have same structure & values
    bool compareNodes(const NODE* node1, const NODE* node2) const {
        // if both empty then return true because they are both equal 
        if (node1 == nullptr && node2 == nullptr) {
            return true;
        } // otherwise return false
        else if (node1 == nullptr || node2 == nullptr) {
            return false;
        }
        
        // check if value, priority, & duplicates of the two nodes are equal
        if (node1->value != node2->value || node1->priority != node2->priority || node1->dup != node2->dup) {
            return false;
        }

        // check is duplicates are equal
        if (node1->dup) {
            // initialize two pointers
            NODE* curr1 = node1->link;
            NODE* curr2 = node2->link;
            // loop thru list of duplicates
            while (curr1 != nullptr && curr2 != nullptr) {
                // compare the value & priority
                if (curr1->value != curr2->value || curr1->priority != curr2->priority) {
                    return false; // return false if not equal
                }
                curr1 = curr1->link;
                curr2 = curr2->link;
            }
            
            // check if both lists have same number of nodes
            if (curr1 != nullptr || curr2 != nullptr) {
                return false;
            }
        }
        // recursively call function on left & right children, return true if equal
        return compareNodes(node1->left, node2->left) && compareNodes(node1->right, node2->right);
    }

public:
    // default constructor that initializes an empty priority queue
    priorityqueue() {
        root = nullptr;
        size = 0;
        curr = nullptr;
    }
    
    // assignment operator overload for assigning one priority queue to another
    priorityqueue& operator=(const priorityqueue& other) {
        // check bojects match each other ] 
        if (this == &other) {
            return *this; // return reference to itself
        }
        clear(); // clear current tree
        // copy other tree
        root = copy(other.root);
        size = other.size;
        curr = nullptr;

        return *this; // return refrence to updated queue
    }
    
    // clears the priority queue by freeing the memory associated with it
    void clear() {
        clearRecursive(root); // clear the queue recursivley
        // reset variables
        root = nullptr;
        size = 0;
        curr = nullptr;
    }
    
    // destructor for freeing the memory associated with the priority queue
    ~priorityqueue() { clear(); }
    
    //inserts a value with a given priority into the priority queue
    void enqueue(T value, int priority) {
        // create & initilaize a new node 
        NODE* newNode = new NODE;
        newNode->value = value;
        newNode->priority = priority;
        newNode->dup = false;
        newNode->link = nullptr;
        newNode->parent = nullptr;
        newNode->left = nullptr;
        newNode->right = nullptr;

        // if root empty, set root to newNode 
        if (root == nullptr) {
            root = newNode;
            size++; // increment size
            return;
        }

        // otherwise travers the tree to find correct position for new node
        NODE* currNode = root;
        while (currNode != nullptr) {
            // if priority of newNode is less than currNode, go left
            if (priority < currNode->priority) {
                // if there is no left child, insert newNode
                if (currNode->left == nullptr) {
                    currNode->left = newNode;
                    newNode->parent = currNode; // update parent
                    size++; // increment size
                    break;
                } 
                // otherwise, continue to traverse left
                else {
                    currNode = currNode->left;
                }
            } 

            // if priority of newNode greater than currNode, go right
            else if (priority > currNode->priority) {
                // if no right child, insert newNode 
                if (currNode->right == nullptr) {
                    currNode->right = newNode;
                    newNode->parent = currNode;
                    size++; // increment size
                    break;
                } 
                // otherwise keep traversing right
                else {
                    currNode = currNode->right;
                }
            }

            // if priority or newNode equal to currNode, then duplicate
            else {
                NODE* prevNode = currNode;
                while (prevNode->link != nullptr) {
                    prevNode = prevNode->link;
                }
                // insert newNode as linked node
                prevNode->link = newNode;
                // update parent and dup
                newNode->parent = currNode; 
                currNode->dup = true;
                size++; // increment size

                // if currNode null or equal to currNode
                if (curr == nullptr || curr == currNode) {
                    curr = newNode; // set equal to newNode
                }
                break;
            }
        }
    }

    // removes the element with the highest priority (lowest priority value) from the priority queue and returns its value
    T dequeue() {
        // if root null, return defualt value
        if (root == nullptr) {
            return T();
        }

        // find node with lowest priority
        NODE* nodeToRemove = root;
        NODE* parentNode = nullptr;

        while (nodeToRemove->left != nullptr) {
            parentNode = nodeToRemove;
            nodeToRemove = nodeToRemove->left;
        }

        // get value of the node to be removed
        T valueOut = nodeToRemove->value;

        // if the node had dups, remove the first duplicate 
        if (nodeToRemove->dup) {
            NODE* nextNode = nodeToRemove->link;
            // update linked list
            nodeToRemove->value = nextNode->value;
            nodeToRemove->link = nextNode->link;
            // if theres no more dups, update the dup flag
            if (nodeToRemove->link == nullptr) {
                nodeToRemove->dup = false;
            }
            delete nextNode;
        } 
        
        // otherwise, remove the node and update tree
        else {
            if (parentNode != nullptr) {
                parentNode->left = nodeToRemove->right;
            } 
            else {
                root = nodeToRemove->right;
            }

            if (nodeToRemove->right != nullptr) {
                nodeToRemove->right->parent = parentNode;
            }
            delete nodeToRemove;
        }
        size--; // decrement the size
        return valueOut; // return value of removed node
    }
    
    // returns the number of elements in the priority queue
    int Size() { return size; }
    
    // resets the internal state for an inorder traversal
    void begin() {
        // set curr node to root
        curr = root;
        // traverse tree
        while (curr != nullptr && curr->left != nullptr) {
            curr = curr->left;
        }
    }

    // returns the next elements value & priority in an inorder traversal and advances the internal state
    bool next(T& value, int &priority) {
        // if curr node is null
        if (curr == nullptr) {
            return true; // return true to show no more nodes in tree
        }

        // set value & priority to the values of curr node
        value = curr->value;
        priority = curr->priority;

        // if curr node has link, set the curr node to the link and return true
        if (curr->link != nullptr) {
            curr = curr->link;
        } 
        // otherwise, find the next node in tree
        else {
            // if curr node has right child, set curr node to leftmost node in right subtree
            if (curr->right != nullptr) {
                curr = curr->right;
                while (curr->left != nullptr) {
                    curr = curr->left;
                }
            } 
            else {
                while (curr->parent != nullptr && curr == curr->parent->right) {
                    curr = curr->parent;
                }
                curr = curr->parent;
            }
        }
        return true; // return true to show next value and priority has been found
    }

    // returns a string representation of the entire priority queue in order
    string toString() {
        ostringstream ss; // create output string stream
        toStringRecursive(root, ss); // call recursive helper function
        return ss.str(); // return the string representation of queue
        
    }
    
    // returns the value of the next element in the priority queue without removing it
    T peek() {
        // if root null, return defualt value
        if (root == nullptr) {
            return T(); 
        }

        //set the first node to the leftmost node in the tree
        NODE* firstNode = root;
        while (firstNode->left != nullptr) {
            firstNode = firstNode->left;
        }

        // set valueOut to value of firstNode and return
        T valueOut = firstNode->value;
        return valueOut;
    }
    
    // equality operator overload to compare two priority queues
    bool operator==(const priorityqueue& other) const {
        // if size of the two queues are different, then not equal
        if (size != other.size) {
            return false;
        }
        // otherwise call recursive function to compare each node in queue
        return compareNodes(root, other.root);
            
    }
    
    // returns the root node of the custom BST, used for testing purposes
    void* getRoot() {
        return root;
    }
};