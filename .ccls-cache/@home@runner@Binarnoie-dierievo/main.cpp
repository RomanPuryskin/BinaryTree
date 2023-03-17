#include <iostream>

class Node
{
private:
  int m_key;
  Node* m_left;
  Node* m_right;

public:
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


//----------------Конструктор копирования-----------------//
  BinaryTree(const BinaryTree& copy)
  {
    copyTree(copy.m_root);
  }

  void copyTree(Node *root)
  {
    ;
  }

//------------Добавление элемента ( перегрузка ) ------------------//
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
//----------------------------------------------------------------//

//------------Получение корня-------------------//
  Node* getRoot()
  {
    return m_root;
  }
//----------------------------------------------//
  
};

void destr(const int size)
{
  BinaryTree tree;
  for(int i=0;i<size;i++)
    tree.addNode(i);
}


int main()
{
  destr(100);
return 0;
  }