#pragma once

struct Node
{
    int   key;           // ノードが保持する値
    Node* left;          // 左の子ノードへのポインタ
    Node* right;         // 右の子ノードへのポインタ
    Node(const int k) : key(k), left(nullptr), right(nullptr) {}
};

// 二分探索木に新しいノードを挿入する関数
static Node* insert(Node* root, const int key)
{
    // 木が空の場合、新しいノードを作成して返す
    if (root == nullptr)
        return new Node(key);
    
    // 挿入する値が現在のノードより小さければ左部分木へ、それ以外は右部分木へ
    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
        
    return root;
}
