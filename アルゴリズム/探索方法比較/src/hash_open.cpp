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

    // オープンアドレス法を用いたハッシュテーブルの構築
    const size_t     table_size = data.size() * 2; // テーブルサイズをデータ数の2倍にする
    std::vector<int> hash_table(table_size, -1); // -1を空きスロットとして初期化
    for (const int& x : data)
    {
        size_t idx = static_cast<size_t>(x) % table_size;
        // 衝突が発生した場合、空きが見つかるまで次のインデックスを探す（線形探査法）
        while (hash_table[idx] != -1)
            idx = (idx + 1) % table_size;
        hash_table[idx] = x;
    }

    long long  found_count = 0;
    const auto start_time  = std::chrono::steady_clock::now(); // 計測開始

    // 各クエリに対してハッシュテーブルを探索
    for (const int& q : queries)
    {
        bool found = false;

        // ハッシュ値を計算し、空きスロットに到達するか目的の値が見つかるまで探査
        size_t idx = static_cast<size_t>(q) % table_size;
        while (hash_table[idx] != -1)
        {
            if (hash_table[idx] == q)
            {
                found = true;
                break; // 見つかったらループを抜ける
            }
            idx = (idx + 1) % table_size;
        }

        if (found)
            found_count++;
    }

    const auto end_time = std::chrono::steady_clock::now(); // 計測終了
    const auto elapsed  = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    // 実行時間（マイクロ秒）と見つかった件数を出力
    std::cout << elapsed << " " << found_count << "\n";
    return 0;
}
