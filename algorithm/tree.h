//
// Created by root on 3/12/17.
//

#ifndef TEST2_TREE_H
#define TEST2_TREE_H

struct TreeNode;
typedef struct TreeNode *SearchTree;
typedef struct TreeNode *position;


struct TreeNode{
    int element;
    SearchTree left;
    SearchTree right;
};

SearchTree makeEmpty(SearchTree t);
position find(int element, SearchTree t);
position findMin(SearchTree t);
position findMax(SearchTree t);
SearchTree insert(int x, SearchTree t);
SearchTree  delete(int x, SearchTree t);
int retrieve(position p);

#endif //TEST2_TREE_H
