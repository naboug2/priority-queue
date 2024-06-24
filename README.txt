Description
In this project, I implemented an abstraction class for a priority queue. The fundamental design of a priority queue ensures 
that, regardless of the order in which elements are added (enqueued), they are removed (dequeued) in order of their priority.

Specifically, the element with the lowest priority number is dequeued first, followed by the second-lowest, and so on, with
the highest-numbered (i.e., least urgent) item dequeued last.

Key Features
Priority-Based Dequeue: Elements are dequeued based on their priority values, with the lowest priority being dequeued first.
Tie-Breaking by Order of Insertion: If multiple elements have the same priority, ties are broken by the order of insertion. 
 This means that if an element is added to the queue with a priority value of K and there are already elements with priority
 K, the new element will be placed after the existing ones.
Flexible Storage: While a priority queue can internally store its elements in sorted or unsorted order, the essential 
 requirement is that elements are dequeued in sorted order by priority.

Implementation Details
Custom Binary Search Tree (BST): The priority queue is implemented using a custom binary search tree. Each node in the tree 
is based on the priority value and also stores the associated element values.
Node Pointers:
- Each node links to its left and right children.
- Each node also links to its parent.
- To handle duplicate priorities, nodes are marked with a dup flag set to true, and a linked list is created using the link 
   node pointer.

This implementation ensures efficient management of elements based on priority, leveraging the properties of a binary search
 tree to maintain order and facilitate quick insertion and deletion operations.