# Red-Black tree implementation
This project provides an implementation of a Red-Black Tree, a self-balancing binary search tree, in C++. The Red-Black Tree ensures that the tree remains balanced by following specific rules when performing insertions and deletions.

## Features
- Insertion: Automatically balances the tree after adding a new node.
- Deletion: Removes a node and rebalances the tree to maintain Red-Black properties.
- Traversal: Supports multiple types of tree traversal:
  - In-order Traversal
  - Pre-order Traversal
  - Post-order Traversal
  - Level-order Traversal
- Minimum and Maximum Values: Retrieves the smallest and largest values in the tree.
- Height Calculation: Computes the height of the tree.

## Red-Black Tree Properties
1. Each node is either red or black.
2. The root node is always black.
3. Every leaf node (NIL) is black.
4. If a red node has children, then the children must be black (i.e., no two red nodes can be adjacent).
5. For each node, every path from that node to its descendant NIL nodes has the same number of black nodes.

## Structure
```
red-black-tree/
├── include/
│   ├── Node.h
│   └── RedBlack.h
├── src/
│   ├── Node.cpp
│   └── RedBlack.cpp
├── main.cpp
└── README.md
```

## How to compile and run
Create the build directory if it doesn't exist
```
mkdir -p build
```
Compile
```
g++ -o build/tree_example main.cpp src/Node.cpp src/RedBlack.cpp -Iinclude
```
Run
```
./build/tree_example
```
