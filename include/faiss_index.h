#pragma once
#include <faiss/Index.h>
#include <vector>

namespace vectordb {
class FaissIndex {
   private:
    faiss::Index* index;

   public:
    FaissIndex(faiss::Index* index);

    void insert_vector(const std::vector<float>& data, uint64_t label);
    std::pair<std::vector<long>, std::vector<float>> search_vector(
        const std::vector<float>& query, int k);
};
}  // namespace vectordb