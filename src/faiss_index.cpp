#include "faiss_index.h"

namespace vectordb {
FaissIndex::FaissIndex(faiss::Index* index) : index(index) {}

void FaissIndex::insert_vector(const std::vector<float>& data, uint64_t label) {
    long id = static_cast<long>(label);
    index->add_with_ids(1, data.data(), &id);
}
std::pair<std::vector<long>, std::vector<float>> FaissIndex::search_vector(
    const std::vector<float>& query, int k) {
    int dim = index->d;
    int num_queries = query.size() / dim;
    std::vector<long> indices(num_queries * k);
    std::vector<float> distances(num_queries * k);
    index->search(num_queries, query.data(), k, distances.data(),
                  indices.data());
    return {indices, distances};
}
}  // namespace vectordb