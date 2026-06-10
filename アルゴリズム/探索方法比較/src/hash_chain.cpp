#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "common.hpp"


int main()
{
    // データの読み込み
    const std::vector<int> data    = load_data("src/data/dataset.txt");
    const std::vector<int> queries = load_data("src/data/queries.txt");

    // チェイン法を用いたハッシュテーブルの構築
    const size_t                table_size = data.size();
    std::vector<std::list<int>> hash_table(table_size);
    for (const int& x : data)
    {
        // ハッシュ値を計算してリストに追加（衝突時はリストに連結）
        hash_table[x % table_size].push_back(x);
    }

    long long  found_count = 0;
    const auto start_time  = std::chrono::steady_clock::now(); // 計測開始

    // 各クエリに対してハッシュテーブルを探索
    for (const int& q : queries)
    {
        bool found = false;

        // ハッシュ値を計算して対応するリストを探索
        const size_t idx = static_cast<size_t>(q) % table_size;
        for (const int& x : hash_table[idx])
        {
            if (x == q)
            {
                found = true;
                break; // 見つかったらループを抜ける
            }
        }

        if (found)
            found_count++;
    }

    const auto end_time = std::chrono::steady_clock::now(); // 計測終了
    const auto elapsed  = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << elapsed << " " << found_count << "\n";
    return 0;
}
