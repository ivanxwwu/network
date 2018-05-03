//
// Created by root on 3/12/17.
//

#include "tree.h"
#include <stdio.h>
#include <stddef.h>

SearchTree makeEmpty(SearchTree t){
    if(t != NULL){
        makeEmpty(t->left);
        makeEmpty(t->right);
        free(t);
    }
    return NULL;
}


position find(int x, SearchTree t){
    if(t == NULL) return NULL;
    if(x<t->element)return find(x, t->left);
    else if(x>t->element)return find(x, t->right);
    else
        return t;
}


position findMin(SearchTree t){
    if(t==NULL) return NULL;
    if(t->left != NULL)
        return findMin(t->left);
    else
        return t;
//    while(t->left != NULL){
//        t = t->left;
//    }
//    return t;
}


position findMax(SearchTree t){
    if(t==NULL) return NULL;
    if(t->right != NULL)
        return findMax(t->right);
    else
        return t;
//    while(t->right != NULL){
//        t = t->right;
//    }
//    return t;
}


SearchTree insert(int x, SearchTree t){
    if(t==NULL) {
        t = (SearchTree)malloc(sizeof(SearchTree));

        if(t == NULL){
            return NULL;
        }
        else{
            t->element = x;
            t->left = NULL;
            t->right = NULL;
        }
    }
    else if(x>t->element){
        t->right = insert(x, t->right);
    }
    else if(x<t->element){
        t->left = insert(x, t->left);
    }
    return t;
}


SearchTree  delete(int x, SearchTree t){
    if(t==NULL) return NULL;
    position temp;
    if(x>t->element){
        t->right = delete(x, t->right);
    }
    else if(x<t->element){
        t->left = delete(x, t->left);
    }
    else if(t->left && t->right){
        temp = findMin(t->right);
        t->element = t->temp;
        t->right = delete(t->element, t->right);
    }
    else if(t->left || t->right){
        temp = t;
        if(t->left != NULL){
            t = t->left;
        }
        else{
            t = t->right;
        }
        free(temp);
    }
    else{
        free(t);
        t = NULL;
    }
    return t;
}


int retrieve(position p){

}

int main(){

    SearchTree t = (SearchTree)malloc(sizeof(SearchTree));
    t->element = 6;
    insert(3, t);
    insert(10, t);
    position p = findMin(t);
    printf("%d\n", p->element);
    p = findMax(t);
    printf("%d\n", p->element);
}