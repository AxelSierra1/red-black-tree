#include "../include/Node.h"

class RedBlack{
    private:
        Node* root;

        void rotate_left(Node*);                    // left rotation
        void rotate_right(Node*);                   // right rotation
        void swap_color(Node*, Node*);              // swap the colors of two nodes
        Node* replacement_node(Node*);              // gets replacement for a node

        Node* _insert(Node*, int);
        void _balance_insertion(Node*);
        void _balance_deletion(Node*);
        Node* _search(Node*, int);
        int _height(Node*);

        void _in_order(Node*);
        void _pre_order(Node*);
        void _post_order(Node*);

    public:
        RedBlack();                                 // constructor
        ~RedBlack();                                // destructor

        Node* get_root();                           // returns the root

        void insert(int VALUE);                     // adds a new Node
        void remove(int VALUE);                     // removes a node
        Node* search(int VALUE);                    // searches and returns the node with the given value

        Node* min_subtree(Node*);                   // returns the node with the smallest value in a subtree
        Node* max_subtree(Node*);                   // returns the node with the largest value in a subtree
        int get_min();                              // returns the minimum value in the tree
        int get_max();                              // returns the maximum value in the tree
        int height();                               // returns the height of the tree

        void level_order();                         // prints level-order traversal
        void in_order();
        void pre_order();
        void post_order();
};
