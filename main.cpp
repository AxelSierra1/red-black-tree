#include "include/RedBlack.h"
#include <iostream>

using namespace std;

int main()
{
    RedBlack* tree1 = new RedBlack();
    tree1->insert(30);
    tree1->insert(23);
    tree1->insert(39);
    tree1->insert(21);
    tree1->insert(12);
    tree1->insert(10);   
    tree1->insert(32);
    tree1->insert(37);
    tree1->insert(14);
    tree1->insert(7);
    tree1->insert(26);
    
 
    tree1->remove(39);
    

    cout << "\n";
    cout << "Black: " << BLACK << "\n";
    cout << "Red: " << RED << "\n";
    cout << "\n";

    tree1->in_order();
    cout << "\n\n";
    tree1->level_order();
    cout << "\n";

    cout << "Minimum value of the tree: " << tree1->get_min() << "\n";
    cout << "Maximum value of the tree: " << tree1->get_max() << "\n";
    cout << "Height of the tree: " << tree1->height() << "\n";

    return 0;
}