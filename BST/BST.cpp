/*
Basic BST<int> with support for
- insert
- remove
- search
- findMin/findMax
- inorderPrint

TODO: BST template
*/

#include <iostream>
using namespace std;

class BSTNode{
        int val;
        BSTNode* parent = nullptr;
        BSTNode* left = nullptr, *right = nullptr;
        friend class BST;
        public:
        BSTNode(int val) : val(val) {}
        ~BSTNode() {
            if(left) delete left;
            if(right) delete right;
        }
        int getVal() {return val;}
};

class BST{
    BSTNode* root = nullptr;

    BSTNode* _insert(int key, BSTNode* n) {
        if(!n) {
            n = new BSTNode(key);
        }
        if(n->val < key) {
            n->right = _insert(key, n->right);
            n->right->parent = n;
        } else if(n->val > key) {
            n->left = _insert(key, n->left);
            n->left->parent = n;
        }
        return n;
    }

    void _inorderPrint(BSTNode* node) {
        if(!node) return;
        _inorderPrint(node->left);
        cout << node->val << " ";
        _inorderPrint(node->right);
    }

    BSTNode* removeRoot(BSTNode* n) {
        if(!n->left) return n->right;
        if(!n->right) return n->left;

        // find the smallest node on the right to add root->left to it
        //  then make root->right the new root
        BSTNode* trvrs = n->right;
        while(trvrs->left)
            trvrs = trvrs->left;
        trvrs->left = n->left;
        BSTNode* newRoot = n->right;
        n->left = n->right = nullptr;
        delete n;
        return newRoot;
    }

public:
    ~BST() {
        if(root) delete root;
    }

    void insert(int key) {
        root = _insert(key, root);
    }

    void inorderPrint() {
        _inorderPrint(root);
        cout << endl;
    }

    BSTNode* search(int key) {
        BSTNode* cur = root;
        while(cur) {
            if(cur->val == key) break;
            else if(cur->val < key) cur = cur->right;
            else if(cur->val > key) cur = cur->left;
        }
        return cur;
    }

    void remove(int key) {
        BSTNode* cur = root;
        // Find the node to delete
        while(cur) {
            if(cur->val == key) break;
            else if(cur->val < key) cur = cur->right;
            else cur = cur->left;
        }

        if(cur) { // found the node
            if(cur->parent == nullptr) // remove the root
                root = removeRoot(cur);
            else if(cur->parent->right == cur)
                cur->parent->right = removeRoot(cur);
            else
                cur->parent->left = removeRoot(cur);
        }
    }

    BSTNode* findMin() {
        BSTNode* cur = root;
        while(cur->left)
            cur = cur->left;
        return cur;
    }

    BSTNode* findMax() {
        BSTNode* cur = root;
        while(cur->right)
            cur = cur->right;
        return cur;
    }
};

int main() {
    BST* root = new BST();
    root->insert(2);
    root->insert(4);
    root->insert(1);
    root->insert(0);
    root->inorderPrint();
    BSTNode* test1 = root->search(3);
    if(test1 == nullptr) cout << "not found" << endl;
    BSTNode* test2 = root->search(1);
    if(test1 == nullptr) cout << test2->getVal() << endl;
    cout << "Min: " << root->findMin()->getVal() << endl;
    root->remove(5); // key to be removed not on list
    root->inorderPrint();
    root->remove(4);
    root->inorderPrint();
    root->remove(1);
    root->inorderPrint();
    cout << root->findMax()->getVal() << endl;
    root->insert(2); // existing key
    root->insert(4);
    cout << root->findMax()->getVal() << endl;
    root->inorderPrint();
}