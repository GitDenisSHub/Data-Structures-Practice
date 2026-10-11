#include "SBT_class.h"

//Вспомогательный метод для добавления
Self_balanced_tree::Node* Self_balanced_tree::insertNode(Node* node, int data)
{
    if(node == nullptr){ node = new Node(data); return node;}
    if(data < node->data){node->left = insertNode(node->left, data); return node;}
    if(data > node->data){node->right = insertNode(node->right, data); return node;}
    else return node;

}


//Метод добавления элементоа + автобалансировка
Self_balanced_tree::Node* Self_balanced_tree::insert(int data)
{
    root = insertNode(root, data);   

    count_of_nodes++;
    return nullptr;
}

//Деструктор нашего дерева
Self_balanced_tree::~Self_balanced_tree(){

}