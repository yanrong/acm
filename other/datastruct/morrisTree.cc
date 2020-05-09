#include <iostream>
using std::cout;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
/**
**��ǰ�ڵ���cur��ʾ
** 1�����cur�����ӣ�cur�����ƶ�cur=cur->right
** 2�����cur�����ӣ��ҵ�cur�����������ҽڵ㣬��Ϊmostright��
**     ���mostright����ָ��Ϊ�� ����ָ��cur,mostright->right=cur��cur�����ƶ���cur=cur->left;
**     ���mostright����ָ��ָ��cur ����ָ��� mostright->right=null cur�����ƶ���cur=cur->right;
**/
class morrisTree{
public:
    void morrisPreorder(TreeNode* root){
        if(root == nullptr){
            return ;
        }
        TreeNode *cur = root;
        TreeNode *mostRight = nullptr;
        while (cur != nullptr)
        {
            mostRight = cur->left;
            if(mostRight != nullptr){
                while(mostRight->right != nullptr && mostRight->right != cur){
                    mostRight = mostRight->right;
                }
                if(mostRight->right == nullptr){
                    mostRight->right = cur; // right point to parent
                    //get the value, next step will visit right child
                    cout<< cur->val<< " ";
                    cur = cur->left;
                    //why continue, we have been reach the left-right most, 
                    //next step visit left child
                    continue;
                }else{
                    mostRight->right = nullptr;
                }
            }else{//if the left child is empty, visit parent node
                cout<<cur->val<<" ";
            }
            cur = cur->right;
        }
    }

    void morrisInorder(TreeNode* root){
        if(root == nullptr){
            return;
        }
        TreeNode *cur = root, *mostRight = nullptr;
        while(cur != nullptr){
            mostRight = cur->left; //visit the left tree
            if(mostRight != nullptr){
                while(mostRight->right != nullptr && mostRight->right != cur){
                    mostRight = mostRight->right;
                }
                if(mostRight->right == nullptr){
                    mostRight->right = cur;
                    cur = cur->left;
                    continue;
                }else{
                    mostRight->right = nullptr;
                }
            }
            cout<<cur->val<<" ";
            cur = cur->right;
        }
    }

    void morrisPostorder(TreeNode* root){
        if(root != nullptr){
            return;
        }
        TreeNode *cur = root, *mostRight = nullptr;
        while(cur != nullptr){
            mostRight = cur->left;
            if(mostRight != nullptr){
                while(mostRight->right != nullptr && mostRight->right != cur){
                    mostRight = mostRight->right;
                }
                if(mostRight->right == nullptr){
                    mostRight->right = cur;
                    cur = cur->left;
                    continue;
                }else{
                    mostRight->right = nullptr;
                    printEdge(cur->left);
                }
            }
            cur = cur->right;
        }
        printEdge(root);
    }

    void printEdge(TreeNode *root){
        root = rightReverse(root);
        TreeNode *cur = root;
        while(cur != nullptr){
            cout<<cur->val<< " ";
            cur = cur->right;
        }
        rightReverse(root);
    }

    TreeNode* rightReverse(TreeNode *root){
        TreeNode *cur = root->right, *prev = root;
        prev->right = nullptr;
        while(cur != nullptr){
            TreeNode *tmp = cur;
            cur = cur->right;
            tmp->right = prev;
            prev = tmp;
        }
        return prev;
    }
};