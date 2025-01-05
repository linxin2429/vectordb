#include <faiss/IndexFlat.h>

#include <iostream>

int main() {
  int dim = 64;                   // 向量维度
  faiss::IndexFlatL2 index(dim);  // 构建索引

  // 使用索引...

  return 0;
}