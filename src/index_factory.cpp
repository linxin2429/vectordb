#include <faiss/IndexFlat.h>
#include <faiss/IndexIDMap.h>
#include "faiss_index.h"
#include "index_factory.h"

namespace vectordb {

std::once_flag IndexFactory::init_flag;
IndexFactory* IndexFactory::instance = nullptr;

void IndexFactory::init(IndexType type, int dim, MetricType metric) {
    faiss::MetricType metric_type = metric == MetricType::L2
                                        ? faiss::METRIC_L2
                                        : faiss::METRIC_INNER_PRODUCT;
    switch (type) {
        case IndexType::FLAT:
            index_map[type] = new FaissIndex(
                new faiss::IndexIDMap(new faiss::IndexFlat(dim, metric_type)));
            break;
        default:
            break;
    }
}
void* IndexFactory::getIndex(IndexType type) const {
    auto it = index_map.find(type);
    if (it != index_map.end()) {
        return it->second;
    }
    return nullptr;
}

IndexFactory* IndexFactory::getInstance() {
    std::call_once(init_flag, &IndexFactory::initInstance);
    return instance;
}

void IndexFactory::initInstance() {
    instance = new IndexFactory();
}
IndexFactory* getGlobalIndexFactory() {
    return IndexFactory::getInstance();
}
}  // namespace vectordb