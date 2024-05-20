#include <iostream>
#include <chrono>
#include <time.h>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

struct Tree
{
    int key;
    Tree* left;
    Tree* right;
};

Tree* getFreeTree(int value)
{
    Tree* root = new Tree;
    root->left = root->right = NULL;
    root->key = value;
    return root;
}

int sizeOfTree(Tree* root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return (sizeOfTree(root->left) + sizeOfTree(root->right));
    }
}

void insert(int currKey, Tree* root)
{
    if (currKey < root->key)
    {
        if (root->left != NULL)
        {
            insert(currKey, root->left);
        }
        else
        {
            root->left = new Tree;
            root->left->key = currKey;
            root->left->left = root->left->right = NULL;
        }
    }
    else if (currKey > root->key)
    {
        if (root->right != NULL)
        {
            insert(currKey, root->right);
        }
        else
        {
            root->right = new Tree;
            root->right->key = currKey;
            root->right->left = root->right->right = NULL;
        }
    }
    else
    {
        return;
    }
}

Tree* readFromF()
{
    Tree* root;
    ifstream database("C:\\Users\\mitya\\source\\repos\\BinaryTree\\DataForTree.txt");// Следует указать путь к файлу на своем устройстве!
    if (!database.is_open())
    {
        cout << "Ошибка открытия файла!\n";
        return NULL;
    }
    else
    {
        int value;
        string s;
        int startValue;
        if (getline(database, s))
        {
            startValue = stoi(s);
        }
        else
        {
            cout << "В файле нет данных!\n";
            return NULL;
        }
        root = getFreeTree(startValue);
        while (getline(database, s))
        {
            value = stoi(s);
            insert(value, root);
        }
    }
    return root;
}

Tree* createTree(int choise)
{
    Tree* root;
    int n;
    auto clockStart = chrono::high_resolution_clock::now();
    auto clockEnd = chrono::high_resolution_clock::now();
    int startValue;
    int end = 99;
    int start = -99;
    string a;
    bool isEnd = false;
    switch (choise)
    {
    case 1:
        cout << "Введите количество элементов бинарного дерева\n";
        cin >> n;
        srand(time(NULL));
        clockStart = chrono::high_resolution_clock::now();
        startValue = rand() % (end - start + 1) + start;
        root = getFreeTree(startValue);
        for (int i = 1; i < n; i++)
        {
            int value = rand() % (end - start + 1) + start;
            insert(value, root);
        }
        clockEnd = chrono::high_resolution_clock::now();
        cout << "Время создания бинарного дерева: ";
        cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
        return root;
        break;
    case 2:
        cout << "Введите элементы бинарного дерева:\nВведите ""end"" для завершения ввода\n";
        clockStart = chrono::high_resolution_clock::now();
        startValue = 0;
        cin >> a;
        if (a == "end")
        {
            isEnd = true;
            cout << "Не введено ни одного значения, дерево не может быть сформировано, выход...\n";
            exit(0);
        }
        else
        {
            startValue = stoi(a);
        }
        root = getFreeTree(startValue);
        n = 1;
        int value;
        while (!isEnd)
        {
            cin >> a;
            if (a == "end")
            {
                isEnd = true;
                break;
            }
            else
            {
                value = stoi(a);
            }
            insert(value, root);
            n++;
        }
        clockEnd = chrono::high_resolution_clock::now();
        cout << "Время создания бинарного дерева: ";
        cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
        return root;
        break;
    case 3:
        cout << "Создание дерева по данным из файла\n";
        clockStart = chrono::high_resolution_clock::now();
        root = readFromF();
        clockEnd = chrono::high_resolution_clock::now();
        cout << "Время создания бинарного дерева: ";
        cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
        return root;
        break;
    default:
        cout << "Выход из программы...\n";
        exit(0);
    }
}

/*void printTree(Tree* root)
{

}*/

Tree* deleteTreeElem(int currKey, Tree* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        if (currKey == root->key)
        {
            Tree* tmp, * ptr;
            if (root->right == NULL)
            {
                tmp = root->left;
            }
            else
            {
                ptr = root->left;
                if (ptr->left == NULL)
                {
                    ptr->left = root->left;
                    tmp = ptr;
                }
                else
                {
                    Tree* pmin = ptr->left;
                    while (pmin->left != NULL)
                    {
                        ptr = pmin;
                        pmin = ptr->left;
                    }
                    ptr->left = pmin->right;
                    pmin->left = root->left;
                    pmin->right = root->right;
                    tmp = pmin;
                }
            }
            delete root;
            return tmp;
        }
        else if (currKey < root->key)
        {
            root->left = deleteTreeElem(currKey, root->left);
        }
        else
        {
            root->right = deleteTreeElem(currKey, root->right);
        }
    }
    return root;
}

Tree* search(int currKey, Tree* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        if (currKey == root->key)
        {
            return root;
        }
        else if (currKey < root->key)
        {
            return search(currKey, root->left);
        }
        else
        {
            return search(currKey, root->right);
        }
    }
}

void preOrderTravers(Tree* root)
{
    if (root)
    {
        cout << root->key << " ";
        preOrderTravers(root->left);
        preOrderTravers(root->right);
    }
    else
    {
        return;
    }
}

void postOrderTravers(Tree* root)
{
    if (root)
    {
        postOrderTravers(root->left);
        postOrderTravers(root->right);
        cout << root->key << " ";
    }
}

void levelOrderTravers(Tree* root)
{
    queue<Tree*> q;
    q.push(root);
    while (!q.empty())
    {
        Tree* tree = q.front();
        cout << tree->key << " ";
        q.pop();

        if (tree->left != NULL)
        {
            q.push(tree->left);
        }
        if (tree->right != NULL)
        {
            q.push(tree->right);
        }
    }
}

void destroyTree(Tree* root)
{
    if (root != NULL)
    {
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    }
}

void menu()
{
    cout << "Как Вы хотите заполнить дерево?\n1. Случайными числами\n2. Ввод всех элементов в консоль\n3. Получение элементов из файла\n0. Выход\n";
    int choise;
    cin >> choise;
    Tree* root = createTree(choise);
    int menuPick;
    while (true)
    {
        int prevSize = 0;
        int currSize = 0;
        cout << "1. Вставка элемента в дерево\n2. Удаление элемента дерева\n3. Получение элемента дерева\n4. Прямой обход\n5. Обратный обход\n6. Обход в ширину\n0. Выход\n";
        cin >> menuPick;
        int currKey;
        auto clockStart = chrono::high_resolution_clock::now();
        auto clockEnd = chrono::high_resolution_clock::now();
        switch (menuPick)
        {
        case 1:
            cout << "Введите число, которое хотите добавить: ";
            cin >> currKey;
            prevSize = sizeOfTree(root);
            clockStart = chrono::high_resolution_clock::now();
            insert(currKey, root);
            clockEnd = chrono::high_resolution_clock::now();
            currSize = sizeOfTree(root);
            if (prevSize == currSize)
            {
                cout << "\nЧисло не было добавлено, т.к. оно уже есть в дереве\n";
            }
            else
            {
                cout << "\nЧисло успешно добавлено в дерево\n";
            }
            /*printTree(root);
            */
            cout << "Время добавления элемента в бинарное дерево: ";
            cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
            preOrderTravers(root);
            break;
        case 2:
            cout << "Введите число, которое хотите удалить: ";
            cin >> currKey;
            clockStart = chrono::high_resolution_clock::now();
            if (deleteTreeElem(currKey, root))
            {
                clockEnd = chrono::high_resolution_clock::now();
                cout << "\nЧисло успешно удалено\n";
            }
            else
            {
                clockEnd = chrono::high_resolution_clock::now();
                cout << "\nЧисло не было найдено и удалено\n";
            }
            /*printTree(root);
            */
            cout << "Время удаления элемента из бинарного дерева: ";
            cout << (chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count()) << "ms\n";
            preOrderTravers(root);
            break;
        case 3:
            cout << "Введите число, которое хотите найти: ";
            cin >> currKey;
            if (search(currKey, root))
            {
                cout << "\nЧисло найдено\n";
            }
            else
            {
                cout << "\nТакого числа нет в дереве\n";
            }
            break;
        case 4:
            preOrderTravers(root);
            break;
        case 5:
            postOrderTravers(root);
            break;
        case 6:
            levelOrderTravers(root);
            break;
        default:
            cout << "Выход из программы...\n";
            destroyTree(root);
            exit(0);
        }
    }
}

int main()
{
    setlocale(0, "");
    menu();
}

