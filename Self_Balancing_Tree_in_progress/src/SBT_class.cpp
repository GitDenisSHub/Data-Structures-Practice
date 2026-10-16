#include "SBT_class.h"

//==================================================
//Метод возвращает значение баланса узла
int Self_balanced_tree::getBalanceParameter(Node* currentNode){
    if(currentNode == nullptr) return 0;
    return getHeightNode(currentNode->left) - getHeightNode(currentNode->right);
}
//==================================================

//==================================================
//Метод возвращает высоту максимальной из двух веток
int Self_balanced_tree::max(int left, int right){
    if(left > right) return left;
    else return right;
}
//==================================================

//==================================================
//Метод пересчитывает высоту всех узлов дерева декурсивно
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
//Метод для обновления высоты текущего узла
int Self_balanced_tree::updateHeightNode(Node* currentNode){
    if(currentNode == nullptr) return -1;
    currentNode->height = 1 + (max(getHeightNode(currentNode->left),getHeightNode(currentNode->right)));
    return currentNode->height;
}
//==================================================

//==================================================
//Вспомогательный метод для добавления + автобалансировка 
Self_balanced_tree::Node* Self_balanced_tree::insertNode(Node* currentNode, int data)
{
    //Наш метод не multi - если значение равно узлу - мы игнорируем такое значение
    //Добавляем новый узел + сразу выставляем ему нулевую высоту, так как это лист
    if(currentNode == nullptr){ currentNode = new Node(data); currentNode->height = 0; count_of_nodes++; return currentNode;}
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
//Балансировка левого перегруза
Self_balanced_tree::Node* Self_balanced_tree::left_Rotate(Node* currentNode){

    Node* safeNode = currentNode;
    currentNode = currentNode->left;
    safeNode->left = currentNode->right;
    currentNode->right = safeNode;
    currentNode->height = recalculateHeightNode(currentNode);

    return currentNode;
}
//==================================================

//==================================================
//Балансировка правого перегруза
Self_balanced_tree::Node* Self_balanced_tree::right_Rotate(Node* currentNode){
    Node* safeNode = currentNode;
    currentNode = currentNode->right;
    safeNode->right = currentNode->left;
    currentNode->left = safeNode;
    currentNode->height = recalculateHeightNode(currentNode);

    return currentNode;
}
//==================================================

//==================================================
//Балансировка узла
Self_balanced_tree::Node* Self_balanced_tree::balance(Node* currentNode, int is_balance){
    //Сначала нужно понять в какую сторону мы поворачиваем
    //Делаем балансировку левой части
    if(is_balance > 1){
        if(getBalanceParameter(currentNode->left) <= -1){
            currentNode->left = right_Rotate(currentNode->left);
            currentNode->height = recalculateHeightNode(currentNode);
        }
        currentNode = left_Rotate(currentNode);
        
    }
    if(is_balance < -1){
        if(getBalanceParameter(currentNode->right) >= 1){
            currentNode->right = left_Rotate(currentNode->right);
            currentNode->height = recalculateHeightNode(currentNode);
        }
        currentNode = right_Rotate(currentNode);
    }
    return currentNode;
}
//==================================================

//==================================================
//Метод добавления элементоа
Self_balanced_tree::Node* Self_balanced_tree::insert(int data)
{
    root = insertNode(root, data);   
    return root;
}
//==================================================

//==================================================
//Поиск максимального элемента
Self_balanced_tree::Node* Self_balanced_tree::max_Node(){
    if(root == nullptr) return nullptr;
    Node* currentNode = root;
    while(currentNode->right != nullptr) currentNode = currentNode->right;

    return currentNode;
}
//Поиск минимального элемента
Self_balanced_tree::Node* Self_balanced_tree::min_Node(){
    if(root == nullptr) return nullptr;
    Node* currentNode = root;
    while(currentNode->left != nullptr) currentNode = currentNode->left;

    return currentNode;
}
//Поиск элемента в дереве
Self_balanced_tree::Node* Self_balanced_tree::search(int data){
    if(root == nullptr) return nullptr;
    if(data == root->data) return root;

    Node* currentNode = root;
    while(currentNode != nullptr){
        if(currentNode->data == data) return currentNode;
        if(data > currentNode->data) currentNode = currentNode->right;
        else if(data < currentNode->data) currentNode = currentNode->left;
    }
    return nullptr;
}
//==================================================

//==================================================
//Обход дерева inorder (l - t - r)
void Self_balanced_tree::inorder(){
    if(root == nullptr) cout<<"Tree is empty!"<<endl;
    else inorderNode(root);
    
}
//==================================================

//==================================================
//Метод для удаления узла из дерева + выполнение балансировки
Self_balanced_tree::Node* Self_balanced_tree::remove(int data){
    root = removeNode(data, root); 
    return root;
}
//==================================================


//==================================================
//Вспомогательный метод для удаления узла из дерева
Self_balanced_tree::Node* Self_balanced_tree::removeNode(int data, Node* currentNode){
    //Если элемент пуст - возвращаем nullptr
    if(currentNode == nullptr) return nullptr;
    //Если нету наследников - просто возвращаемся назад
    if(currentNode->left == nullptr && currentNode->right == nullptr && currentNode->data != data) return currentNode;

    if(currentNode->data == data){
        if(currentNode->height == 0){delete currentNode; currentNode = nullptr; count_of_nodes--; return currentNode;}
        //В них нечего пересчитывать, все остается так же
        if(currentNode->left == nullptr){
            Node* safeNode = currentNode;
            currentNode = currentNode->right; 
            delete safeNode;
            safeNode = nullptr;
            count_of_nodes--;
        }
        else if(currentNode->right == nullptr){
            Node* safeNode = currentNode; 
            currentNode = currentNode->left; 
            delete safeNode;
            safeNode = nullptr;
            count_of_nodes--;
        }
        else{
            //Если есть оба наследника
            //Будем смещать в его сторону наименьший элемент из правых!
            Node* safeNode = currentNode;
            currentNode = minRightNode(currentNode->right);
            currentNode->left = safeNode->left;
            if(safeNode->right != currentNode) currentNode->right = safeNode->right;
            //Обновляем высоту дерева на основе высот его потомков
            currentNode->height = recalculateHeightNode(currentNode);
            count_of_nodes--;
            delete safeNode;
            safeNode = nullptr;
        }
    }
    else if(data > currentNode->data){currentNode->right = removeNode(data, currentNode->right);}
    else{ currentNode->left = removeNode(data, currentNode->left);}

    //Сначала мы пересчитываем высоту всего дерева(иначе не знаю как)
    currentNode->height = updateHeightNode(currentNode);
    //Если перекос - делаем баланс
    int is_balance = getBalanceParameter(currentNode);
    cout<<endl<<"Наш баланс - " << is_balance << endl;
    if(is_balance > 1 || is_balance < -1){
        cout<<"У нас перекос на дереве! Выравниваем!"<<endl;
        currentNode = balance(currentNode, is_balance);
    }
    //Сначала мы пересчитываем высоту всего дерева(иначе не знаю как)
    currentNode->height = updateHeightNode(currentNode);
    is_balance = getBalanceParameter(currentNode);
    cout << "Проверяем еще раз - " << is_balance << endl;

    return currentNode;
}
//==================================================

//==================================================
//Вспомогательный метод для поиска минимального значения правой ветки (и вытягивание его)
Self_balanced_tree::Node* Self_balanced_tree::minRightNode(Node*& currentNode){

    if(currentNode->left == nullptr && currentNode->right == nullptr){
        Node* safeNode = new Node(currentNode->data);
        delete currentNode;
        currentNode = nullptr;
        return safeNode;
    }

    else if(currentNode->left == nullptr && currentNode->right != nullptr){
        Node* safeNode = currentNode;
        currentNode = currentNode->right;
        return safeNode;
    }
    else{
        //Вот тут нужно как-то проверить балансировку и изменение высот
        Node* helpNode = currentNode;
        Node* safeNode;
        while(helpNode->left != nullptr){
            safeNode = helpNode;
            helpNode = helpNode->left;
        }
        
        if(helpNode->right == nullptr) {safeNode->left = nullptr; safeNode->height = 0 ; return helpNode;}
        else{
            safeNode->left = helpNode->right;
            safeNode->height = updateHeightNode(safeNode);
            helpNode->right = nullptr;
            return helpNode;
        }
    }  
}
//==================================================

//==================================================
//Метод для удаления всего дерева
bool Self_balanced_tree::clear(){
    //Проверка6 вдруг вообще ничего делать не нужно
    if(root == nullptr) return true;

    root = clearNode(root);
    //Проверка, если удаления не было - нет смысла удалять корень
    if(is_empty()) return true;
    else return false;
}
//Мод возвращает ответ на вопрос
bool Self_balanced_tree::is_empty(){
    if(count_of_nodes == 0) return true;
    else return false;
}
//==================================================

//==================================================
//Вспомогательный метод для удаления всего дерева
Self_balanced_tree::Node* Self_balanced_tree::clearNode(Node* currentNode){
    if(currentNode == nullptr) return nullptr;
    currentNode->left = clearNode(currentNode->left);
    currentNode->right = clearNode(currentNode->right);

    delete currentNode;
    currentNode = nullptr;
    count_of_nodes--;

    return currentNode;
}
//==================================================


//==================================================
//Вспомогательный метод для обхода дерева
void Self_balanced_tree::inorderNode(Node* currentNode){
    if(currentNode == nullptr) return;

    if(currentNode->left != nullptr) inorderNode(currentNode->left);
    cout << currentNode->data << " ";
    if(currentNode->right != nullptr) inorderNode(currentNode->right);
}
//==================================================

//==================================================
//Деструктор нашего дерева
Self_balanced_tree::~Self_balanced_tree(){ clear();}
//==================================================