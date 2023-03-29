#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>

class Node
{
private:
  int m_key;
  Node* m_left;
  Node* m_right;

public:

  ~Node() = default;

  Node()
  {
    m_key=0;
    m_left = nullptr;
    m_right = nullptr;
  }

  Node(int key)
  {
    m_key=key;
    m_left=nullptr;
    m_right=nullptr;
  }

  int GetKey()
  {
    return m_key;
  }

  Node* GetLeft()
  {
    return m_left;
  }

  Node* GetRight()
  {
    return m_right;
  }

  void SetLeft(Node* left)
  {
    m_left = left;
  }

  void SetRight(Node* right)
  {
    m_right = right;
  }

  int ChildAmount()
  {
    int amount = 0;
    if (GetLeft() != nullptr)
      amount++;
    if (GetRight() != nullptr)
      amount++;

    return amount;
  }
};


class BinaryTree
{

private:
  Node* m_root; 

  public:
  

  BinaryTree() {m_root = nullptr;}

//-----------Деструктор---------------//
  ~BinaryTree()
  {
    DestroyTree(m_root);
  }


  void DestroyTree(Node *root)
  {
    if(root)
      {
        DestroyTree(root->GetLeft());
        DestroyTree(root->GetRight());
        delete root;
      }
  }
//------------------------------------//


//---------------Удаление дерева (поддерева)-------------------//

  void deleteSubTree(Node *root)
  {
    if(root)
      {
        deleteSubTree(root->GetLeft());
        deleteSubTree(root->GetRight());
        root = NULL;
      }
  }

  void deleteAllTree()
  {
    deleteSubTree(m_root);
  }
//-------------------------------------------------------------//

//----------------Конструктор копирования-----------------//
  BinaryTree(const BinaryTree& copy)
  {
    if((m_root = copy.m_root))
      m_root = new Node (*copy.m_root);
    else 
      m_root = nullptr;
  }

//-------------------Копирование поддерева------------------//
  Node* copyTree(Node *root )
  {
    Node* root_copy;
    if (root == nullptr) {
        return nullptr;
    }
    root_copy = new Node(*root);
    if(root->GetLeft() != NULL)
      root_copy->SetLeft(copyTree(root->GetLeft()));
    else root_copy->SetLeft(nullptr);

    if(root->GetRight() != NULL)
      root_copy->SetRight(copyTree(root->GetRight()));
    else root_copy->SetRight(nullptr);
    return root_copy;
  }
//---------------------------------------------------------//
//------------------Проверка дерева на пустоту------------------//
bool isEmpty(Node *root)
  {
    if (root == NULL)
      return true;
    return false;
  }
//--------------------------------------------------------------//


//------------Добавление элемента ( перегрузка ) ------//
  Node* addNode(Node *root , int key)
  {
    if(!root)
      root = new Node(key);
    else if ( rand() & 2)
      root->SetLeft( addNode(root->GetLeft(),key) );
    else
      root->SetRight( addNode(root->GetRight(),key) );

    return root;
  }


  Node* addNode(int key)
  {
    m_root=addNode(m_root ,key);
    return m_root;
  }
//------------------------------------------------------//

//------------Получение корня-------------------//
  Node* getRoot()
  {
    return m_root;
  }
//----------------------------------------------//


//----------------Количество узлов дерева------------//
  int Count(Node *root)
  {
    if(root == NULL)
      return 0;
    return Count(root->GetLeft()) + Count(root->GetRight()) + 1;
  }
//---------------------------------------------------//

//----------------------Вывод дерева горизонтально-----------------//
  void PrintTree(Node *root, int marginLeft, int Space) const
  {
    if(!root)
      return;
    PrintTree(root->GetRight(),marginLeft+Space,Space);
    std::cout<<std::string(marginLeft,' ')<<root->GetKey()<<std::endl;
    PrintTree(root->GetLeft(),marginLeft+Space,Space);
    
  }
//-----------------------------------------------------------------//

//------------------Вывод листьев дерева-----------------//
  void PrintLeaves(Node *root) const
  {
    if(!root)
      return;
    if(root)
    {
      PrintLeaves(root->GetLeft());
      PrintLeaves(root->GetRight());
      if(root->GetLeft() == NULL && root->GetRight() == NULL)
        std::cout<<root->GetKey()<<" ";
    }
  }
//-------------------------------------------------------//

//---------------Получение вектора ключей--------------//
std::vector<int> getTreeKeys()
{
  std::vector<int>treeKeys;
  getTreeKeys(m_root,treeKeys);
  return treeKeys;
}

void getTreeKeys(Node *root , std::vector<int> &treeKeys)
  {
    if(!root)
      return;
    getTreeKeys(root->GetLeft(),treeKeys);
    getTreeKeys(root->GetRight(),treeKeys);
    treeKeys.push_back(root->GetKey());

  }
//-----------------------------------------------------//

//-------------Получение минимального элемента------------//
int searchMinKey()
{
  std::vector<int> treeKeys = getTreeKeys();
  if(treeKeys.empty())
    return -1;
  auto minKey = std::min_element(treeKeys.begin(),treeKeys.end());
  return *minKey;
}
//-----------------------------------------------------//

//-----------Получение максимального элемента----------//
int searchMaxKey()
{
  std::vector<int> treeKeys = getTreeKeys();
  if(treeKeys.empty())
    return -1;
  auto maxKey = std::max_element(treeKeys.begin(),treeKeys.end());
  return *maxKey;
}
//-----------------------------------------------------//


//-------------------Получение высоты дерева-------------------//
int height(Node *root)
  {
    if(root == NULL)
      return 0;
    return 1 + std::max( height(root->GetLeft()) , height(root->GetRight()) );
  }
//-------------------------------------------------------------//


//-----------------Сумма всех ключей дерева--------------------//

int sumKeys(Node *root)
  {
    if(root == NULL)
      return 0;
    sumKeys(root->GetLeft()); 
    sumKeys(root->GetRight()); 
    return sumKeys(root->GetLeft()) + sumKeys(root->GetRight()) + root->GetKey();
  }
//-------------------------------------------------------------//


//------------Получение уровня вершины по ключу ( перегрузка )---------------//

  Node* SearchKey(Node *root , int key)
  {
    if(!root || root->GetKey() == key)
      return root;
    Node *temp = SearchKey(root->GetLeft() , key);
    if(!temp)
      temp = SearchKey(root->GetRight(), key);
    return temp;
  }

 int GetHeightKey(int key)
  {
    Node *temp = SearchKey(m_root, key);
    if( temp == NULL)
      return -1;
    else
      return (height(m_root) - height(temp)) + 1;
  }
//---------------------------------------------------------------------------//

//-------------------Оператор присваивания-----------------//
BinaryTree& operator = (const BinaryTree& other)
  {
    if (this == &other)
      return *this;
    DestroyTree(m_root);
    if((other.m_root))
      m_root = copyTree(other.m_root);
    else 
      m_root = nullptr;

    return *this;
  }
//---------------------------------------------------------//
};                                                                                    


int main()  
{
  int pupmax , pupmin;
  BinaryTree tree;
  for(int i=10;i>2;i--)
    tree.addNode(i);
  
  //BinaryTree clone;
  //clone = tree;
  //clone.PrintTree(clone.getRoot(), 2, 3);
  tree.PrintTree(tree.getRoot(),2 ,3);
 // pup = tree.Count(tree.getRoot());
  //tree.PrintLeaves(tree.getRoot());
  //pup=tree.Count(tree.getRoot());
  //pup = tree.sumKeys(tree.getRoot());
 // pupmin = tree.GetHeightKey(5);
  //std::cout<<pupmin;
  
  return 0;
}