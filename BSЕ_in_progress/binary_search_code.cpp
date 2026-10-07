#include <iostream>
#include <ctime>
using namespace std;

/*
75. Binary Search Tree (BST)
Реализовать:
	• Insert +
	• Search +
	• Delete(правый наименьший)
	• поиск минимального элемента
	• поиск максимального элемента
	• обход дерева (3 варианта или один?)
    - clear()
    - destructor BST
Тренирует: бинарный поиск, рекурсивную работу с деревьями и поддержание свойства BST.


*/

class BinarySearchTree{
public:
    BinarySearchTree()
    : root(nullptr), count_of_nodes(0){}    
    BinarySearchTree(int data)
    : root(new Node(data)), count_of_nodes(1){}

    class Node{
    public:
        Node(int data)
        : data(data), left(nullptr), right(nullptr){}

    private:
        int data;
        Node* left;
        Node* right;
        friend class BinarySearchTree;
    };

    //============================
    //Метод добавления элементов в дерево
    Node* insert(int data){
        //Сначала мы проверяем, а есть ли вообще корень? (Без него никакого дерева нету)
        if(root == nullptr){
            root = new Node(data);
            count_of_nodes++;
            return root;
        }
        //Этим указателем мы будем перемещаться по дереву
        Node* currentNode = root;
        //Циклом перемещаемся по дереву в поиске подходящего варианта(результат получим в любом случае)
        while(true){
            if(data > currentNode->data){
                if(currentNode->right != nullptr){
                    currentNode = currentNode->right;
                } 
                else{
                    currentNode->right = new Node(data);
                    count_of_nodes++;
                    return currentNode->right;
                }
            }
            else if(data < currentNode->data){
                if(currentNode->left != nullptr){
                    currentNode = currentNode->left;
                } 
                else{
                    currentNode->left = new Node(data);
                    count_of_nodes++;
                    return currentNode->left;
                    
                }
            }
            else return nullptr;
        }
    }
    //============================

    //============================
    //Метод поиска узла в дереве
    Node* find(int data){
        //Если дерево пусто - просто вернем нуль, не будем писать много cout, ловим логику проги
        if(root == nullptr) return nullptr;
        Node* currentNode = root;
        //Обходим дерево в поиске нужного элемента
        while(currentNode != nullptr){
            if(data == currentNode->data){ return currentNode;}
            else if(data > currentNode->data){
                if(currentNode->right != nullptr) currentNode = currentNode->right;
                else return nullptr;
            }
            else{
                if(currentNode->left != nullptr) currentNode = currentNode->left;
                else return nullptr;
            }
        }
        return nullptr;
    }
    //============================

    //============================
    //Метод по удалению узла
    Node* remove(int data){
        if(root == nullptr) return nullptr;
        Node* currentNode = root;

        while(currentNode != nullptr){
            if(data > currentNode->data) currentNode = currentNode->right;
            else if(data < currentNode->data) currentNode = currentNode->left;
            //Находим минимальный элемент справа(если его нету, то максимальный элемент слева)
            else{
                if(currentNode->right != nullptr){
                    //Нужен еще один вспомогательный указатель
                    Node* helpNode = currentNode->right;
                    //Думаю, достаточно просто максимально идти влево, чтобы найти самый минимальный из правы
                    //(перед ним, чтобы потом его удалить) 
                    //Но нужно знать, есть ли у следующего левого следующий левый
                    
                    while(helpNode != nullptr){
                        if(helpNode->left != nullptr){
                            if(helpNode->left->left != nullptr){
                                helpNode = helpNode->left;
                            }
                            else{
                                helpNode = helpNode->left;
                                currentNode->data = helpNode->left->data;
                                delete helpNode->left;
                                helpNode->left = nullptr;
                            } 
                        }
                    }
                    
                    
                    //Когда мы доходим до этого минимального элемента - мы копируем у него значение и удаляем его
                    currentNode = 
                    
                }
                else if(currentNode->left != nullptr){
                    //Думаю, достаточно просто максимально идти вправо, чтобы найти самый минимальный из левых 
                    
                }
            }
        }


        return nullptr;
    }
    //============================

private:
    Node* root;
    int count_of_nodes;

};

int main(){
    srand(time(NULL));
    
    BinarySearchTree bst;


    for (size_t i = 0; i < 5; i++)
    {
        bst.insert(rand()%10+1);
    }
    
    cout << bst.find(4) << endl;
  
    

    return 0;
}
