#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <iostream>
template <typename KeyType, typename ValueType>
class TreeMultimap
{private:
    
    struct Node
    {
        Node (const KeyType& key, const ValueType& value)
        {
            m_key=key;
            m_val=value;
            left=right=nullptr;
        }
        KeyType m_key;
        ValueType m_val;
        Node *left,*right;
    };
        Node *m_root;
        //Node *it_root;
    
        void FreeTree(Node*cur)
        {
            if(cur==nullptr)
                return;
            FreeTree(cur->left);
            FreeTree(cur->right);
            delete cur;
        }
  public:
    class Iterator
    {
    private:
              

        Node *it_root;
        Node *m_cur;
      public:
        Iterator()
        {
//            TreeMultimap<int,int>::Iterator it; // doesn't point to any value
//             if (!it.is_valid()) std::cout << "This will print!\n";
            it_root=nullptr;
            m_cur=nullptr;// Replace this line with correct code.
        }
        Iterator(Node *n)
                {
                    it_root=n;
                    m_cur=it_root;
                }

        ValueType& get_value() const
        {
            return m_cur->m_val;  // Replace this line with correct code.
        }

        bool is_valid() const
        {
            if (m_cur==nullptr)
                           return false;
                       else
                           return true;   // Replace this line with correct code.
        }

        void advance()
        {
            if (m_cur->left != nullptr)
                            m_cur = m_cur->left;
                        else if( m_cur->left==nullptr)
                        {
                            m_cur=nullptr;
                        } // Replace this line with correct code.
        }

      
    };

    TreeMultimap()
    {
        m_root=nullptr;// Replace this line with correct code.
    }

    ~TreeMultimap()
    {
        FreeTree(m_root);  // Replace this line with correct code.
    }

    void insert(const KeyType& key, const ValueType& value)
    {
                if(m_root==nullptr) {
                    m_root=new Node(key,value); return;}
                    Node *cur=m_root;
                for(;;)
                {
                    if(key==cur->m_key)
                    {
                        Node *Temp;
                        Temp = cur->left;
                        cur->left=new Node(key,value);
                        cur->left->left=Temp;
        
                        return;
                    }
                    if(key<cur->m_key)
                    {
                        if(cur->left!=nullptr)
                            cur=cur->left;
                        else
                        {
                            cur->left=new Node(key,value);
                            return;
                        }
                    }
                    else if(key>cur->m_key)
                    {
                        if (cur->right!=nullptr)
                            cur=cur->right;
                        else
                        {
                            cur->right=new Node(key,value);
                            return;
                        }
                    }
                }        // Replace this line with correct code.
    }

    Iterator find(const KeyType& key) const
    {
                Node *ptr = m_root;
     //   std::cout << ptr << std::endl;
                while (ptr!=nullptr)
                {
                    if (key==ptr->m_key)
                    {
                        Iterator it = Iterator(ptr);
                        return it;
                    }
                    else if (key<ptr->m_key)
                        ptr=ptr->left;
                    else
                        ptr = ptr->right;
                }
  //      std::cout << "HERE3" << std::endl;
                Iterator invalidit= Iterator();
  //      std::cout << "HERE4" << std::endl;
        return invalidit;
        
                return Iterator();   // Replace this line with correct code.
    }

  
};

#endif // TREEMULTIMAP_INCLUDED
