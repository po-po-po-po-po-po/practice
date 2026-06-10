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

    long long  found_count = 0;
    const auto start_time  = std::chrono::steady_clock::now(); // 計測開始

    const size_t n = data.size();
    // 各クエリに対して線形探索を実行
    for (const int& q : queries)
    {
        bool found = false;

        // 配列の先頭から順番に探索
        for (size_t i = 0; i < n; ++i)
        {
            if (data[i] == q)
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

    // 実行時間（マイクロ秒）と見つかった件数を出力
    std::cout << elapsed << " " << found_count << "\n";
    return 0;
}
