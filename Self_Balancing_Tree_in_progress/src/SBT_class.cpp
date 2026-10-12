#include "SBT_class.h"
//Формула высоты H = H(r) - H(l)
//Лист имеет высоту 0
//Пустое поддерево (nullptr) имеет высоту −1.
//Высота любого другого узла равна высоте его самого высокого поддерева плюс один.
//h(v)=1+max(h(v_L),h(v_R))

//==================================================
//Метод возвращает значение баланса узла
int Self_balanced_tree::getBalanceParameter(Node* currentNode){
    if(currentNode == nullptr) return 0;
    return getHeightNode(currentNode->left) - getHeightNode(currentNode->right);
}
//==================================================

//==================================================
//Метод возвращает высоту максимальной ветки
int Self_balanced_tree::max(int left, int right){
    if(left > right) return left;
    else return right;
}
//==================================================

//==================================================
//Метод подсчитывает высоту отдельного узла рекурсивно
int Self_balanced_tree::recalculateHeightNode(Node* currentNode){
    if(currentNode == nullptr) return -1;

    currentNode->height = 1 + (max(recalculateHeightNode(currentNode->left),recalculateHeightNode(currentNode->right)));
    return currentNode->height;
}
//==================================================

//==================================================
//Метод возвращает высоту узла
int Self_balanced_tree::getHeightNode(Node* currentNode){
    if(currentNode == nullptr) return -1;
    return currentNode->height;
}
//Метод возвращает высоту дерева
int Self_balanced_tree::getHeightTree(){
    if(root == nullptr) return -1;
    return root->height;
}
//==================================================

//==================================================
//Метод для обновления высоты текущего дерева
int Self_balanced_tree::updateHeightNode(Node* currentNode){
    if(currentNode == nullptr) return -1;
    currentNode->height = 1 + (max(getHeightNode(currentNode->left),getHeightNode(currentNode->right)));
    return currentNode->height;
}
//==================================================


//Мы сначала добавляем элемент через рекурсию и потом через рекурсию возвращаем значения назад
//Сначала возвращаем элемент предыдущему с его высотой и снова возвращаем его предыдущему
//Тот получает высоту следующего наследника и если левая сторона больше второй - мы сразу делаем баланс
//Если H <= 1 - дерево не требует балансировки
//==================================================
//Вспомогательный метод для добавления + автобалансировка 
Self_balanced_tree::Node* Self_balanced_tree::insertNode(Node* currentNode, int data)
{
    //Наш метод не multi - если значение равно узлу - мы игнорируем такое значение
    //Добавляем новый узел + сразу выставляем ему нулевую высоту, так как это лист
    if(currentNode == nullptr){ currentNode = new Node(data); currentNode->height = 0; return currentNode;}
    //При возвращении от листов к корню: каждый раз обновляем высоту
    //продолжаем искать место для вставки
    if(data < currentNode->data){currentNode->left = insertNode(currentNode->left, data);}
    else if(data > currentNode->data){currentNode->right = insertNode(currentNode->right, data);}
    else return currentNode;
 
    //Обновляем выстоту узла(используя готовые высоты наследников) 
    //Поэтому, если элемент не будет добавлен, то и значения нигде не изменятся
    currentNode->height = updateHeightNode(currentNode); 

    int is_balance = getBalanceParameter(currentNode);
    if(is_balance > 1 || is_balance < -1) currentNode = balance(currentNode, is_balance);

    return currentNode;
}
//==================================================

//==================================================
//Балансировка слева-направо
Self_balanced_tree::Node* Self_balanced_tree::right_Rotate(Node* currentNode){

}
//==================================================

//==================================================
//Балансировка слева-направо
Self_balanced_tree::Node* Self_balanced_tree::left_Rotate(Node* currentNode){

}
//==================================================

//==================================================
//Балансировка узла
Self_balanced_tree::Node* Self_balanced_tree::balance(Node* currentNode, int is_balance){
    
    while(is_balance > 1 && is_balance < -1){
        if(currentNode->height > 1){
            left_Rotate(currentNode);
        }
        else right_Rotate(currentNode);
    }
    

}
//==================================================

//==================================================
//Метод добавления элементоа
Self_balanced_tree::Node* Self_balanced_tree::insert(int data)
{
    root = insertNode(root, data);   
    count_of_nodes++;
    return nullptr;
}

//Деструктор нашего дерева
Self_balanced_tree::~Self_balanced_tree(){

}
//==================================================