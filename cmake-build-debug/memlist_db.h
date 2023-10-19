//
// Created by chen on 23-10-13.
//

#ifndef MBIST_CLUSTER_MEMLIST_DB_H
#define MBIST_CLUSTER_MEMLIST_DB_H

#include <vector>
#include <string>
class MemListDataBase {
   public:
    struct MemoryData_ {
        std::string memory_type;
        std::vector<std::string> data_paths;
    };

    //void AddMemoryData(const MemoryData_& memory_data) { memory_data_list_.push_back(memory_data); }
    const std::vector<MemoryData_>& get_memory_data_list() const { return memory_data_list_; }

   private:
    std::vector<MemoryData_> memory_data_list_;
};

#endif  //MBIST_CLUSTER_MEMLIST_DB_H
