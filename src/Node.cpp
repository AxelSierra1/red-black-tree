#include "../include/Node.h"
#include <iostream>

Node::Node(int VALUE){
    value = VALUE;
    right = nullptr;
    left = nullptr;
    parent = nullptr;
    color = RED;
}

Node::~Node(){
    delete right;
    delete left;
    delete parent;
}

bool Node::has_left(){
    return left;
}

bool Node::has_right(){
    return right;
}

bool Node::has_two_children(){
    return (left && right);
}

bool Node::is_leaf(){
    return (left == nullptr && right == nullptr);
}

// Getters and Setters
int Node::get_value(){
    return value;
}

Node* Node::get_parent(){
    return parent;
}

Node* Node::get_right(){
    return right;
}

Node* Node::get_left(){
    return left;
}

Color Node::get_color(){
    return color;
}

Node* Node::get_uncle(){
    if(parent && parent->parent){
        Node* grandparent = parent->parent;
        if(grandparent->left == parent){
            return grandparent->right;
        }else if(grandparent->right == parent){
            return grandparent->left;
        }
    }
    return nullptr;
}

Node* Node::get_sibling(){
    if(parent && parent->has_two_children()){
        if(this == parent->left) {
            return parent->right;
        }else{
            return parent->left;
        }
    }
    return nullptr;
}

void Node::set_value(int VALUE){
    value = VALUE;
}

void Node::set_parent(Node* new_parent){
    parent = new_parent;
}

void Node::set_right(Node* new_right){
    right = new_right;
}

void Node::set_left(Node* new_left){
    left = new_left;
}

void Node::set_color(Color c){
    color = c;
}
