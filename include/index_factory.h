#pragma once

#include <map>
#include <mutex>
namespace vectordb {
class IndexFactory {
   public:
    enum class IndexType { FLAT, UNKNOWN = -1 };

    enum class MetricType { L2, IP };

    void init(IndexType type, int dim, MetricType metric = MetricType::L2);
    void* getIndex(IndexType type) const;

    static IndexFactory* getInstance();

   private:
    static void initInstance();
    std::map<IndexType, void*> index_map;
    static std::once_flag init_flag;
    static IndexFactory* instance;
};

IndexFactory* getGlobalIndexFactory();
}  // namespace vectordb