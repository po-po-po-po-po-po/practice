#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "common.hpp"


int main(const int argc, const char* const argv[])
{
    // コマンドライン引数のチェック
    if (argc < 2)
        return 1;
        
    // 引数から生成するデータ数を取得
    const int n = std::stoi(argv[1]);

    std::vector<int> data;
    std::vector<int> queries;
    
    // データとクエリを生成（common.hpp内で定義）
    generate_data(n, data, queries);

    // 生成したデータ（探索対象）をファイルに保存
    std::ofstream out_data("src/data/dataset.txt");
    for (const int x : data)
        out_data << x << "\n";
    out_data.close();

    // 生成したクエリ（探索する値）をファイルに保存
    std::ofstream out_queries("src/data/queries.txt");
    for (const int x : queries)
        out_queries << x << "\n";
    out_queries.close();

    return 0;
}
