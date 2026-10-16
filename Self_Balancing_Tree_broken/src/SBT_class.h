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
    //Деструктор нашего дерева
    ~Self_balanced_tree();

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
    
    //Метод возвращает высоту дерева
    int getHeightTree();
    //Поиск максимального элемента
    Node* max_Node();
    //Поиск минимального элемента
    Node* min_Node();
    //Поиск элемента в дереве
    Node* search(int data);
    //Обход дерева inorder (l - t - r)
    void inorder();
    //Метод для удаления узла из дерева
    Node* remove(int data);
    //Метод добавления элементоа + автобалансировка
    Node* insert(int data);
    //Метод для удаления всего дерева
    bool clear();
    //==================================================

    
private:
    Node* root;
    int count_of_nodes;

    //Мод возвращает ответ на вопрос
    bool is_empty();
    //Вспомогательный метод для удаления всего дерева
    Node* clearNode(Node* currentNode);
    //Вспомогательный метод для поиска минимального значения правой ветки (и вытягивание его)
    Node* minRightNode(Node*& currentNode);
    //Вспомогательный метод для удаления узда из дерева
    Node* removeNode(int data, Node* currentNode);
    //Вспомогательный метод для обхода дерева 
    void inorderNode(Node* currentNode);
    //Балансировка левого перегруза
    Node* left_Rotate(Node* currentNode);
    //Балансировка правого перегруза
    Node* right_Rotate(Node* currentNode);
     //Метод для обновления высоты текущего узла
    int updateHeightNode(Node* currentNode);
    //Балансировка узла
    Node* balance(Node* currentNode, int is_balance);
    //Вспомогательный метод для добавления
    Node* insertNode(Node* currentNode,int data);
    //Метод возвращает высоту максимальной из двух веток
    int max(int left, int right);
    //Метод пересчитывает высоту всех узлов дерева декурсивно
    int recalculateHeightNode(Node* currentNode);
    //Метод возвращает значение баланса узла
    int getBalanceParameter(Node* currentNode);
    //Метод возвращает высоту узла
    int getHeightNode(Node* currentNode);
};




#endif



