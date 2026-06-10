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

    // 番兵（ダミーデータ）を格納するための領域を最後尾に追加
    data.push_back(0);

    long long  found_count = 0;
    const auto start_time  = std::chrono::steady_clock::now(); // 計測開始

    // 番兵を除く本来のデータサイズ
    const size_t n_minus_1 = data.size() - 1;
    for (const int& q : queries)
    {
        bool found = false;

        // 配列の最後尾に探したい値（番兵）をセット
        data.back() = q;
        size_t i    = 0;
        
        // 値が見つかるまで進む（必ず番兵で止まるため、範囲外アクセスのチェックが不要）
        while (data[i] != q)
        {
            ++i;
        }
        
        // 見つかった位置が最後尾（番兵）より前であれば、元データ内に存在したと判定
        if (i < n_minus_1)
        {
            found = true;
        }

        if (found)
            found_count++;
    }

    const auto end_time = std::chrono::steady_clock::now(); // 計測終了
    const auto elapsed  = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    std::cout << elapsed << " " << found_count << "\n";
    return 0;
}
