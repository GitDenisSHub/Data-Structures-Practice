#pragma once
#ifndef _SBT_CLASS_H_
#define _SBT_CLASS_H_

#include <iostream>
using namespace std;


class Self_balanced_tree{
public:
    //Конструктор без параметров
    Self_balanced_tree()
    : root(nullptr), count_of_nodes(0){}
    //Конструктор с параметрами
    Self_balanced_tree(int data)
    : root(new Node(data)), count_of_nodes(1){}

    //Класс узлов
    class Node{
    public:
        Node(int data)
        : data(data), left(nullptr), right(nullptr){}

    private:
        int data;
        Node* left;
        Node* right;
        friend class Self_balanced_tree;
    };

    //Вспомогательный метод для добавления
    Node* insertNode(Node* node,int data);
    //Метод добавления элементоа + автобалансировка
    Node* insert(int data);



    //Деструктор нашего дерева
    ~Self_balanced_tree();
private:
    Node* root;
    int count_of_nodes;
};




#endif



