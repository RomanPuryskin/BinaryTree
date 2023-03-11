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

int main()
{
return 0;
  }