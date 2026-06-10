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
    std::vector<int>       data    = load_data("src/data/dataset.txt");
    const std::vector<int> queries = load_data("src/data/queries.txt");

    // 二分探索のためにデータを事前に昇順ソートする
    std::sort(data.begin(), data.end());
    const std::vector<int>& sorted_data = data;

    long long  found_count = 0;
    const auto start_time  = std::chrono::steady_clock::now(); // 計測開始

    // 各クエリに対して二分探索を実行
    for (const int& q : queries)
    {
        bool found = false;

        // 探索範囲の初期化（配列の全体）
        int left = 0, right = static_cast<int>(sorted_data.size()) - 1;
        
        while (left <= right)
        {
            // 中央のインデックスを計算
            const int mid = left + (right - left) / 2;
            
            if (sorted_data[mid] == q)
            {
                found = true;
                break; // 見つかったらループを抜ける
            }
            else if (sorted_data[mid] < q)
                left = mid + 1; // 探したい値が中央より大きい場合は右半分へ
            else
                right = mid - 1; // 探したい値が中央より小さい場合は左半分へ
        }

        if (found)
            ++found_count;
    }

    const auto end_time = std::chrono::steady_clock::now(); // 計測終了
    const auto elapsed  = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << elapsed << " " << found_count << "\n";
    return 0;
}
