#pragma once

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// データ生成用関数
inline void generate_data(const int n, std::vector<int>& data, std::vector<int>& queries)
{
    std::mt19937                       gen(12345);
    std::uniform_int_distribution<int> dist(-999999999, 999999999);

    data.reserve(n);               // 領域確保
    for (int i = 0; i < n; ++i)    // データの生成
    {
        data.push_back(dist(gen));
    }

    constexpr int m = 500;
    queries.reserve(m);            // 領域確保
    for (int i = 0; i < m; ++i)    // クエリの生成
    {
        if (i % 2 == 0)
        {    // データからランダムに選択
            std::uniform_int_distribution<int> idx_dist(0, n - 1);
            queries.push_back(data[idx_dist(gen)]);
        }
        else
        {    // ランダムな値を生成
            queries.push_back(dist(gen));
        }
    }
}

// データをファイルから読み込む関数
inline std::vector<int> load_data(const std::string& filename)
{
    std::ifstream    in(filename);    // ファイルを開く
    std::vector<int> vec;
    int              val;
    while (in >> val)    // ファイルから整数を読み込む
    {
        vec.push_back(val);    // 配列に追加
    }
    return vec;
}
