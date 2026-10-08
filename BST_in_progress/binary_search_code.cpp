#include <iostream>
#include <ctime>
#include <stack>
using namespace std;

/*
75. Binary Search Tree (BST)
Реализовать:
	• Insert +
	• Search +
	• Delete +
	• поиск минимального элемента +
	• поиск максимального элемента +
	• обход дерева(inorder = l -> n -> r)
    - clear() +
    - destructor BST +
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
    bool remove(int data){
        if(root == nullptr) return false;
        if(root != nullptr && root->data == data && root->left == nullptr && root->right == nullptr){
            delete root;
            root = nullptr;
            count_of_nodes--;
            return true;
        }

        Node* currentNode = root;
        while(currentNode != nullptr){
            if(data > currentNode->data){
                if(currentNode->right != nullptr){
                    if(currentNode->right->data == data && currentNode->right->left == nullptr && currentNode->right->right == nullptr){
                        delete currentNode->right;
                        currentNode->right = nullptr;
                        count_of_nodes--;
                        return true;
                    }
                } 
                currentNode = currentNode->right;
            } 
            else if(data < currentNode->data){
                if(currentNode->left != nullptr){
                    if(currentNode->left->data == data && currentNode->left->left == nullptr && currentNode->left->right == nullptr){
                        delete currentNode->left;
                        currentNode->left = nullptr;
                        count_of_nodes--;
                        return true;
                    }
                }
                currentNode = currentNode->left;
            } 
            
            //Находим минимальный элемент справа(если его нету, то максимальный элемент слева)
            else{
                if(currentNode->right != nullptr){
                    //Если это последни элемент - просто удаляем его
                    if(currentNode->right->left == nullptr && currentNode->right->right == nullptr){
                        currentNode->data = currentNode->right->data;
                        delete currentNode->right;
                        currentNode->right = nullptr;
                        count_of_nodes--;
                        return true;

                    }
                    //Иначе нужен еще один вспомогательный указатель
                    Node* helpNode = currentNode->right;
                    //Наша задача найти минимальный справа и поставить его вместо удаленного
                    //Иначе найти максимальный справа и поставить его вместо удаленного

                    //Тут мы пойдем влево и будем работать в левой стороне
                    if(helpNode->left != nullptr){
                        while(helpNode->left->left != nullptr){
                            helpNode = helpNode->left;
                        }
                        if(helpNode->left->right != nullptr){
                            currentNode->data = helpNode->left->data;
                            Node* safeNode = helpNode->left->right;
                            delete helpNode->left;
                            helpNode->left = safeNode;
                            safeNode = nullptr;
                            count_of_nodes--;
                            return true;
                        }
                        else{
                            currentNode->data = helpNode->left->data;
                            delete helpNode->left;
                            helpNode->left = nullptr;
                            count_of_nodes--;
                            return true;
                        }
                    }
                    //=============================
                    else{
                        currentNode->data = currentNode->right->data;
                        Node* safeNode = currentNode->right->right;
                        delete currentNode->right;
                        currentNode->right = safeNode;
                        count_of_nodes--;
                        return true;
                    }     
                }
                else if(currentNode->left != nullptr){
                    //Если это последни элемент - просто удаляем его
                    if(currentNode->left->left == nullptr && currentNode->left->right == nullptr){
                        currentNode->data = currentNode->left->data;
                        delete currentNode->left;
                        currentNode->left = nullptr;
                        count_of_nodes--;
                        return true;
                    }
                    Node* helpNode = currentNode->left;
                    //Думаю, достаточно просто максимально идти вправо, чтобы найти самый минимальный из левых 
                    if(helpNode->right != nullptr){
                        while(helpNode->right->right != nullptr){
                            helpNode = helpNode->right;
                        }
                        if(helpNode->right->left != nullptr){
                            currentNode->data = helpNode->right->data;
                            Node* safeNode = helpNode->right->left;
                            delete helpNode->right;
                            helpNode->right = safeNode;
                            safeNode = nullptr;
                            count_of_nodes--;
                            return true;
                        }
                        else{
                            currentNode->data = helpNode->right->data;
                            delete helpNode->right;
                            helpNode->right = nullptr;
                            count_of_nodes--;
                            return true;
                        }
                    }
                    //=============================
                    else{
                        currentNode->data = currentNode->left->data;
                        Node* safeNode = currentNode->left->left;
                        delete currentNode->left;
                        currentNode->left = safeNode;
                        count_of_nodes--;
                        return true;
                    }
                    
                    
                }
            }
        }

        //Значит мы ничего не удалили (значение не найдено)
        return false;
    }
    //============================

    //============================
    //Метод ищет минимальный элемент дерева
    Node* min(){
        if(root == nullptr) return nullptr;
        Node* currentNode = root;
        while(currentNode->left != nullptr){
                currentNode = currentNode->left;
        }
        return currentNode; 
    }
    //============================

    //============================
    //Метод ищет минимальный элемент дерева
    Node* max(){
        if(root == nullptr) return nullptr;
        Node* currentNode = root;
        while(currentNode->right != nullptr){
                currentNode = currentNode->right;
        }
        return currentNode; 
    }
    //============================

    //Возможный вспомогательный метод для обхода
    bool traversal(Node* currentNode){
        if(currentNode->left == nullptr && currentNode->right == nullptr){
            cout<<currentNode->data<<" ";
            return true;
        }

        if(currentNode->left != nullptr){
            traversal(currentNode->left);
        }

        cout<<currentNode->data<<" ";

        if(currentNode->right != nullptr){
            traversal(currentNode->right);
        }
        return true;
    }

    //============================
    //Обходи дерева (inorder = l -> n -> r)
    bool inorder(){
        if(root == nullptr) return 0;
        //Нужен ли нам вообще этот стек?
        stack<Node*> stk;
        Node* currentNode = root;

        traversal(currentNode->left);
        cout<<currentNode->data<<" ";
        traversal(currentNode->right);

        return true;
    }
    //============================

    //Метод по очищению дерева через его корень
    void clear(){
        while(count_of_nodes != 0){remove(root->data);}
    }
    //Деструктор
    ~BinarySearchTree(){clear();}
private:
    Node* root;
    int count_of_nodes;

};

int main(){
    srand(time(NULL));
    
    BinarySearchTree bst;
    int value;

    for (size_t i = 0; i < 10; i++)
    {
        value = rand()%100+1;
        cout<<value<<" ";
        bst.insert(value);
        
    }
    cout<<endl;
  
    bst.inorder();

    return 0;
}
