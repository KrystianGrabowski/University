#include<iostream>
#include<stdio.h>
#include<string>
#include <algorithm>
#include <stdlib.h>  
#include <unistd.h>  

//AVL
struct Node{
    Node * left = NULL;
    Node * right = NULL;
    long long int val;
    unsigned short height;

};

bool exists = 0;
bool lower_exists = 0;
bool upper_exists = 0;

Node * root;

unsigned short height(Node *n){
    if (n == NULL){
        return 0;
    }
    else{
        return n->height;
    }
}

Node* rotate_right(Node *y){
    Node * a = y->left;
    if (a == NULL){
        y->left = NULL;
        a = y;

        //y->height = std::max(height(y->left), height(y->right))+1;
        a->height = std::max(height(a->left), height(a->right))+1;
    }
    else{
        y->left = a->right;
        a->right = y;

        y->height = std::max(height(y->left), height(y->right))+1;
        a->height = std::max(height(a->left), height(a->right))+1;
    }

    return a;
} 

Node* rotate_left(Node *x){
    Node * a = x->right;
    if (a == NULL){
        x->right = NULL;
        a = x;

        //x->height = std::max(height(x->left), height(x->right))+1;
        a->height = std::max(height(a->left), height(a->right))+1; //I 2379
    }
    else{
        x->right = a->left;
        a->left = x;

        x->height = std::max(height(x->left), height(x->right))+1;
        a->height = std::max(height(a->left), height(a->right))+1;
    }

    return a;
} 



Node* insert_Node(Node* newnode, long long int v){
 
    if (newnode == NULL){
        newnode = new Node;
        newnode->val = v;
        newnode->height = 1;
        return newnode;
    }
    if (v < newnode->val){
        newnode->left = insert_Node(newnode->left, v);
    }
    else if (v > newnode->val) {
        newnode->right = insert_Node(newnode->right, v);
    }
    newnode->height = std::max(height(newnode->left), height(newnode->right)) + 1;
    short balance = height(newnode->left) - height(newnode->right);

    if (balance > 1){
        if (newnode->left->val > v){
            return rotate_right(newnode);
        }
        else{
            newnode->left = rotate_left(newnode->left);
            return rotate_right(newnode);
        }
    }

    if (balance < -1){
        if (newnode->right->val < v){
            return rotate_left(newnode);
        }
    else{

        newnode->right = rotate_right(newnode->right);
        return rotate_left(newnode);
        }
    }

    return newnode;
}

long long int minval(Node* newnode){
    while(newnode->left != NULL){
        newnode = newnode->left;
    }
    return newnode->val;
}

Node* delete_Node(Node* newnode, long long int v){

    if (newnode == NULL){
        delete newnode;
        return NULL;
    }

    if (newnode->val == v){
        exists = 1;
        if (newnode->left == NULL || newnode->right == NULL){
            if (newnode->left == NULL && newnode->right == NULL){
                delete newnode;
                return NULL;   
            }
            else{
                if (newnode->left == NULL){
                    newnode->val = newnode->right->val;
                    newnode->left = newnode->right->left;
                    newnode->right->left = NULL;
                    newnode->right = delete_Node(newnode->right, newnode->right->val);
                }
                else{
                    newnode->val = newnode->left->val;
                    newnode->right = newnode->left->right;
                    newnode->left->right = NULL;
                    newnode->left = delete_Node(newnode->left, newnode->left->val);
                }   
            }   
        }
        else{
            long long int minimal = minval(newnode->right);
            newnode->val = minimal;
            newnode->right = delete_Node(newnode->right, minimal);
        }
    }
    else{
        if (v < newnode->val){
            newnode->left = delete_Node(newnode->left, v);
        }
        else{
            newnode->right = delete_Node(newnode->right, v);
        }
    }
    newnode->height = std::max(height(newnode->left), height(newnode->right)) + 1;
    return newnode;

}


long long int upper(Node* newnode, long long int v){
    if (newnode == NULL){
        return 0;
    }
    if (newnode->val == v){
        upper_exists = 1;
        return v;
    }
    if (v < newnode->val){
        upper_exists = 1;
        if (newnode->left != NULL){
            long long int deep = upper(newnode->left, v);
            if(abs(newnode->val - v) <= abs(deep - v)){
                return newnode->val;
            }
            else{
                return deep;
            }
        }
        else{
            return newnode->val;
        }
    }
    else{
        if (newnode->right != NULL){
            return upper(newnode->right, v);
        }

    }


    return newnode->val;
}

long long int lower(Node* newnode, long long int v){
    if (newnode == NULL){
        return 0;
    }
    if (newnode->val == v){

        lower_exists = 1;
        return v;
    }
    if (v > newnode->val){
        lower_exists = 1;
        if (newnode->right != NULL){
            long long int deep = lower(newnode->right, v);
            if(abs(newnode->val - v) <= abs(deep - v)){
                return newnode->val;
            }
            else{
                return deep;
            }
        }
        else{
            return newnode->val;
        }
    }
    else{
        if (newnode->left != NULL){
            return lower(newnode->left, v);
        }
        
    }


    return newnode->val;
}



int main(){
    int p = 0;
    if(scanf("%d", &p) != 1){
        printf("ERROR");
    }
    for(int i=0; i<p; i++){
        char op;
        long long int num;
        if(scanf(" %c", &op ) != 1){
            printf("ERROR");
        }
        if(scanf("%lli", &num ) != 1){
            printf("ERROR");
        }

        if(op == 'I'){
            root = insert_Node(root, num);
        }
        if(op == 'D'){
            exists = 0;
            root = delete_Node(root, num);
            if(exists == 1){
                printf("OK\n");
            }
            else{
                printf("BRAK\n");
            }
            
        }
        if(op == 'U'){
            upper_exists = 0;
            long long int u = upper(root, num);
            if(upper_exists == 1){
                printf("%lli\n", u);
            }
            else{
                printf("BRAK\n");            
            }
        }
        if(op == 'L'){
            lower_exists = 0;
            long long int l = lower(root, num);
            if(lower_exists == 1){
                printf("%lli\n", l);
            }
            else{
                printf("BRAK\n");
            }
        }

        
        
    }
    return 0;
}