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
        : data(data), left(nullptr), right(nullptr), height(0){}

    private:
        int data;
        Node* left;
        Node* right;
        int height;
        friend class Self_balanced_tree;
    };
    //==================================================
    //Метод возвращает высоту максимальной ветки
    int max(int left, int right);
    //Метод возвращает высоту дерева
    int getHeightTree();
    //Метод возвращает высоту узла
    int getHeightNode(Node* currentNode);
    //Метод подсчитывает высоту отдельного узла рекурсивно
    int recalculateHeightNode(Node* currentNode);
    //Метод возвращает значение баланса узла
    int getBalanceParameter(Node* currentNode);
    //==================================================
    //Метод для обновления высоты текущего дерева
    int updateHeightNode(Node* currentNode);
    //Балансировка узла
    Node* balance(Node* currentNode, int is_balance);

    //Вспомогательный метод для добавления
    Node* insertNode(Node* currentNode,int data);
    //Метод добавления элементоа + автобалансировка
    Node* insert(int data);
    //Балансировка слева-направо
    Node* right_Rotate(Node* currentNode);
    //Балансировка справа-налево
    Node* left_Rotate(Node* currentNode);


    //Деструктор нашего дерева
    ~Self_balanced_tree();
private:
    Node* root;
    int count_of_nodes;
};




#endif



