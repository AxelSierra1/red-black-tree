#include "../include/RedBlack.h"
#include <iostream>
#include <queue>

using namespace std;

//==================== Private ====================

void RedBlack::rotate_left(Node* parent) {
    Node* node = parent->get_right();
    Node* left = node->get_left();

    parent->set_right(left);
    if (left) {
        left->set_parent(parent);
    }

    node->set_left(parent);
    node->set_parent(parent->get_parent());

    if (!parent->get_parent()) {
        root = node;
    } else if (parent == parent->get_parent()->get_left()) {
        parent->get_parent()->set_left(node);
    } else {
        parent->get_parent()->set_right(node);
    }

    parent->set_parent(node);
}

void RedBlack::rotate_right(Node* parent) {
    Node* node = parent->get_left();
    Node* right = node->get_right();

    parent->set_left(right);
    if (right) {
        right->set_parent(parent);
    }

    node->set_right(parent);
    node->set_parent(parent->get_parent());

    if (!parent->get_parent()) {
        root = node;
    } else if (parent == parent->get_parent()->get_left()) {
        parent->get_parent()->set_left(node);
    } else {
        parent->get_parent()->set_right(node);
    }

    parent->set_parent(node);
}

void RedBlack::swap_color(Node* node1, Node* node2) {
    Color temp_color = node1->get_color();
    node1->set_color(node2->get_color());
    node2->set_color(temp_color);
}

Node* RedBlack::replacement_node(Node* node) {
    if (node->has_two_children()) { // if it has two children, return the max of the left subtree
        return max_subtree(node->get_left());
    }
    if (node->is_leaf()) { // if it’s a leaf, return nullptr
        return nullptr;
    }
    if (node->get_left()) { // if it has only one child, return that child
        return node->get_left();
    } else if (node->get_right()) {
        return node->get_right();
    }
    return nullptr;
}

Node* RedBlack::_insert(Node* node, int VALUE) {
    if (VALUE < node->get_value()) {
        if (node->has_left()) {
            return _insert(node->get_left(), VALUE);
        } else {
            Node* new_node = new Node(VALUE);
            node->set_left(new_node);
            node->get_left()->set_parent(node);
            return new_node;
        }
    } else {
        if (node->has_right()) {
            return _insert(node->get_right(), VALUE);
        } else {
            Node* new_node = new Node(VALUE);
            node->set_right(new_node);
            node->get_right()->set_parent(node);
            return new_node;
        }
    }
}


/*
Rebalancing CASES:
CASE 1: Red parent, red uncle                                   // Recolor parent and uncle to black, grandparent to red
CASE 2a: Red parent, black uncle, left parent, right child      // Left rotation
CASE 2b: Red parent, black uncle, right parent, left child      // Right rotation
CASE 3a: Red parent, black uncle, left parent, left child       // Right rotation, recolor parent to black, grandparent to red
CASE 3b: Red parent, black uncle, right parent, right child     // Left rotation, recolor parent to black, grandparent to red
*/
void RedBlack::_balance_insertion(Node* node) {
    if (node == root) {
        node->set_color(BLACK);
        return;
    }
    if (node->get_parent()->get_color() == BLACK) {
        // No need to balance
        return;
    }

    // From this point, we know the parent is red
    Node* parent = node->get_parent();
    Node* grandparent = parent->get_parent();
    Node* uncle = node->get_uncle();

    if (uncle && uncle->get_color() == RED) { // CASE 1: Red parent and red uncle
        parent->set_color(BLACK);
        uncle->set_color(BLACK);
        grandparent->set_color(RED);

        _balance_insertion(grandparent);
        return;
    }

    // From here, uncle is black (and parent is red)
    if (node == parent->get_right() && parent == grandparent->get_left()) { // CASE 2a
        rotate_left(parent);              // After rotation, becomes CASE 3a
        node = node->get_left();          // After rotation, parent becomes child of node, so redefine node

    } else if (node == parent->get_left() && parent == grandparent->get_right()) { // CASE 2b
        rotate_right(parent);             // After rotation, becomes CASE 3b
        node = node->get_right();         // After rotation, parent becomes child of node, so redefine node
    }

    // After balancing CASE 2, we now handle CASE 3 (node and parent are still red)
    parent = node->get_parent();
    grandparent = parent->get_parent();
    parent->set_color(BLACK);
    grandparent->set_color(RED);

    if (parent == grandparent->get_left()) { // CASE 3a: Left parent, left child
        rotate_right(grandparent);
    } else {                                 // CASE 3b: Right parent, right child
        rotate_left(grandparent);
    }

    _balance_insertion(parent);
}

/*
Rebalancing CASES:
CASE (1): The node to delete is red
CASE (2): The DB (double black) node is the root
CASE (3): DB’s sibling is black, and both sibling's children are black
CASE (4): DB’s sibling is red
CASE (5): DB’s sibling is black, the far child is black, and the near child is red
CASE (6): DB’s sibling is black, and the far child is red

BALANCING ACTIONS:
(1): Delete the node from the tree
(2): Remove DB and repaint root black
(3): Delete DB (if it's nullptr), repaint DB's sibling red. If DB's parent is black, make it the new DB. Otherwise, repaint it black
(4): Swap the colors of DB’s parent and sibling, rotate from DB’s parent in the direction of DB, rebalance again
(5): Swap the color of the sibling with its red child, rotate from the sibling in the direction of DB, then apply (6)
(6): Swap the colors of DB’s parent and sibling, rotate from DB’s parent in the direction of DB, repaint DB black, repaint DB's far sibling's child black
*/
void RedBlack::_balance_deletion(Node* node) {
    Node* sibling;
    while ((node != root) && (node->get_color() == BLACK)) {
        if (node == node->get_parent()->get_left()) {
            sibling = node->get_parent()->get_right();
            if (sibling->get_color() == RED) { // CASE 4
                sibling->set_color(BLACK);
                node->get_parent()->set_color(RED);
                rotate_left(node->get_parent());
                sibling = node->get_parent()->get_right();
            }

            if (sibling->get_left()->get_color() == BLACK && sibling->get_right()->get_color() == BLACK) { // CASE 3
                sibling->set_color(RED);
                node = node->get_parent();
            } else {
                if (sibling->get_right()->get_color() == BLACK) { // CASE 5
                    sibling->get_left()->set_color(BLACK);
                    sibling->set_color(RED);
                    rotate_right(sibling);
                    sibling = node->get_parent()->get_right();
                }

                // CASE 6
                sibling->set_color(node->get_parent()->get_color());
                node->get_parent()->set_color(BLACK);
                sibling->get_right()->set_color(BLACK);
                rotate_left(node->get_parent());
                node = root;
            }
        } else {
            sibling = node->get_parent()->get_left();
            if (sibling->get_color() == RED) { // CASE 4
                sibling->set_color(BLACK);
                node->get_parent()->set_color(RED);
                rotate_right(node->get_parent());
                sibling = node->get_parent()->get_left();
            }

            if (sibling->get_left()->get_color() == BLACK && sibling->get_right()->get_color() == BLACK) { // CASE 3
                sibling->set_color(RED);
                node = node->get_parent();
            } else {
                if (sibling->get_left()->get_color() == BLACK) { // CASE 5
                    sibling->get_right()->set_color(BLACK);
                    sibling->set_color(RED);
                    rotate_left(sibling);
                    sibling = node->get_parent()->get_left();
                }

                // CASE 6
                sibling->set_color(node->get_parent()->get_color());
                node->get_parent()->set_color(BLACK);
                sibling->get_left()->set_color(BLACK);
                rotate_right(node->get_parent());
                node = root;
            }
        }
    }
    node->set_color(BLACK);
}

Node* RedBlack::_search(Node* node, int VALUE) {
    if (VALUE < node->get_value()) {
        if (node->has_left()) {
            return _search(node->get_left(), VALUE);
        } else {
            return nullptr;
        }
    } else if (VALUE > node->get_value()) {
        if (node->has_right()) {
            return _search(node->get_right(), VALUE);
        } else {
            return nullptr;
        }
    } else {
        return node; // Found the value
    }
}

int RedBlack::_height(Node* node) {
    if (node == nullptr) {
        return 0;
    } else {
        int left_height = _height(node->get_left());
        int right_height = _height(node->get_right());
        return std::max(left_height, right_height) + 1;
    }
}

void RedBlack::_in_order(Node* node) {
    if (node == nullptr) {
        return;
    } else {
        _in_order(node->get_left());        // Visit left subtree
        cout << node->get_value();          // Visit the node
        cout << ", ";
        _in_order(node->get_right());       // Visit right subtree
    }
}

void RedBlack::_pre_order(Node* node) {
    if (!node) {
        return;
    } else {
        cout << node->get_value();          // Visit the node
        cout << ", ";
        _pre_order(node->get_left());      // Visit left subtree
        _pre_order(node->get_right());     // Visit right subtree
    }
}

void RedBlack::_post_order(Node* node) {
    if (!node) {
        return;
    } else {
        _post_order(node->get_left());     // Visit left subtree
        _post_order(node->get_right());    // Visit right subtree
        cout << node->get_value();          // Visit the node
        cout << ", ";
    }
}

RedBlack::RedBlack() {
    root = nullptr;  // The tree starts with no nodes (empty tree)
}

RedBlack::~RedBlack() {
    delete root;  // Deletes the root node (and recursively deletes its children)
}

Node* RedBlack::get_root() {
    return root;  // Return the root of the tree
}

void RedBlack::insert(int VALUE) {
    if (!root) {
        root = new Node(VALUE);         // If the tree is empty, create a new root
        _balance_insertion(root);          // Balance the tree after insertion
        return;
    }
    root->set_color(BLACK);            // Set the root's color to black
    _balance_insertion(_insert(root, VALUE));  // Insert the value and then balance the tree
}

void RedBlack::remove(int VALUE) {
    Node* node = search(VALUE);  // Find the node with the given value in the tree
    if (!node) {
        // The value is not in the tree, nothing to delete
        return;
    }
    
    if (node->is_leaf()) {  // CASE 1: The node to delete is a leaf
        if (node == root) {  // If it's the root node
            root = nullptr;  // Tree becomes empty
            return;
        }
        // If the node is the right child of its parent
        if (node == node->get_parent()->get_right()) {
            node->get_parent()->set_right(nullptr);
        } else {  // If it's the left child of its parent
            node->get_parent()->set_left(nullptr);
        }
        // Balance the tree after deletion
        _balance_deletion(node);
    } 
    else if (node->has_two_children()) {  // CASE 2: The node has two children
        // Replace with the minimum node from the right subtree
        Node* max_node = replacement_node(node);  // Find the replacement node (maximum of left subtree)
        int max_value = max_node->get_value();  // Get the value of the replacement node
        remove(max_value);  // Recursively delete the replacement node
        node->set_value(max_value);  // Replace the value of the current node with the replacement's value
        node->set_color(BLACK);  // Ensure the color is valid after replacement
    } 
    else if (node->get_left()) {  // CASE 3: The node has only a left child
        // Replace the node with its left child
        Node* child = node->get_left();
        if (node == root) {  // If the node to delete is the root
            child->set_parent(nullptr);
            root = child;
        } else {
            child->set_parent(node->get_parent());
            if (node == node->get_parent()->get_left()) {  // If the node is the left child of its parent
                node->get_parent()->set_left(child);
            } else {  // If the node is the right child of its parent
                node->get_parent()->set_right(child);
            }
        }
        _balance_deletion(replacement_node(node));  // Balance the tree after deletion
    } 
    else if (node->get_right()) {  // CASE 4: The node has only a right child
        // Replace the node with its right child
        Node* child = node->get_right();
        if (node == root) {  // If the node to delete is the root
            child->set_parent(nullptr);
            root = child;
        } else {
            child->set_parent(node->get_parent());
            if (node == node->get_parent()->get_left()) {  // If the node is the left child of its parent
                node->get_parent()->set_left(child);
            } else {  // If the node is the right child of its parent
                node->get_parent()->set_right(child);
            }
        }
        _balance_deletion(replacement_node(node));  // Balance the tree after deletion
    }
}


Node* RedBlack::search(int VALUE) {
    if (!root) {
        return nullptr;
    }
    return _search(root, VALUE);
}


Node* RedBlack::min_subtree(Node* node) {
    if (node->get_left()) {
        return min_subtree(node->get_left());
    } else {
        return node;
    }
}


Node* RedBlack::max_subtree(Node* node) {
    if (node->get_right()) {
        return max_subtree(node->get_right());
    } else {
        return node;
    }
}


int RedBlack::get_min() {
    return min_subtree(root)->get_value();
}


int RedBlack::get_max() {
    return max_subtree(root)->get_value();
}

int RedBlack::height() {
    return _height(root);
}


void RedBlack::level_order() {
    if (!root) {
        // empty tree
        return;
    }
    queue<Node*> queue; // define a queue
    queue.push(root);

    while (!(queue.empty())) {   // while(queue has elements)
        int size = queue.size();
        for (int i = 0; i < size; i++) {
            Node* node = queue.front();
            queue.pop();
            cout << node->get_value() << "->C:" << node->get_color() << " ";

            if (node->get_left()) {
                queue.push(node->get_left());
            }
            if (node->get_right()) { 
                queue.push(node->get_right());
            }
        }
        cout << "\n";
    }
}


void RedBlack::in_order() {
    if (!root) {
        cout << "[ ]";
    } else {
        cout << "[ ";
        _in_order(root);
        cout << "]";
    }
}


void RedBlack::pre_order() {
    if (!root) {
        cout << "[ ]";
    } else {
        cout << "[ ";
        _pre_order(root);
        cout << "]";
    }
}


void RedBlack::post_order() {
    if (!root) {
        cout << "[ ]";
    } else {
        cout << "[ ";
        _post_order(root);
        cout << "]";
    }
}