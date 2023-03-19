#include <iostream>
#include <string>
#include <vector>

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
    copyTree(copy.m_root);
  }

  void copyTree(Node *root)
  {
    ;
  }
//-------------------------------------------------------//

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

  int Count(Node *root)
  {
    if(root == NULL)
      return 0;
    else
    {
      if(root->GetLeft()!=NULL)
        return Count(root->GetLeft())+1;
      if(root->GetRight()!=NULL)
        return Count(root->GetRight())+1;
    }
  }

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
void getTreeKeys(Node *root) const
  {
    std::vector<int> treeKeys;
    if(!root)
      return;
    if(root)
    {
      getTreeKeys(root->GetLeft());
      getTreeKeys(root->GetRight());
      treeKeys.push_back(root->GetKey());
    }

    for (auto& v : treeKeys){
        std::cout << v << " ";
    }
  }
//-----------------------------------------------------//
};


int main()
{
  int pup;
  BinaryTree tree;
  for(int i=0;i<19;i++)
    tree.addNode(i);

  tree.PrintTree(tree.getRoot(),2 ,3);
 // pup = tree.Count(tree.getRoot());
  //std::cout<<pup;
  //tree.PrintLeaves(tree.getRoot());

return 0;
  }