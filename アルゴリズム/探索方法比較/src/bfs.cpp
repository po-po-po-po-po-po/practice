#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "Node.hpp"
#include "common.hpp"


int main()
{
    // データの読み込み
    const std::vector<int> data    = load_data("src/data/dataset.txt");
    const std::vector<int> queries = load_data("src/data/queries.txt");

    // データを二分探索木に挿入して構築
    Node* root = nullptr;
    for (const int& val : data)
        root = insert(root, val);

    long long  found_count = 0;
    const auto start_time  = std::chrono::steady_clock::now(); // 計測開始

    // 各クエリに対して木上の探索を実行
    for (const int& q : queries)
    {
        bool found = false;

        // 幅優先探索(BFS)のためのキュー
        std::queue<const Node*> queue;
        if (root != nullptr)
            queue.push(root);
            
        while (!queue.empty())
        {
            // キューの先頭要素を取り出す
            const Node* current = queue.front();
            queue.pop();
            
            if (current->key == q)
            {
                found = true;
                break; // 見つかったらループを抜ける
            }
            
            // 左右の子ノードがあればキューに追加する（幅優先）
            if (current->left != nullptr)
                queue.push(current->left);
            if (current->right != nullptr)
                queue.push(current->right);
        }

        if (found)
            ++found_count;
    }

    const auto end_time = std::chrono::steady_clock::now(); // 計測終了
    const auto elapsed  = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << elapsed << " " << found_count << "\n";
    return 0;
}
