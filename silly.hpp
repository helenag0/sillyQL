//
//  silly.hpp
//  project3
//
//   IDENTIFIER  = C0F4DFE8B340D81183C208F70F9D2D797908754D
//

#ifndef silly_hpp
#define silly_hpp

#include "TableEntry.h"
#include <stdio.h>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>
#include "xcode_redirect.hpp"


#endif /* silly_hpp */



class Table {
    
private:
    
    
    
//    std::string comp_entry_string;
//    std::bool comp_entry_bool;
//    std::string comp_entry_int;
//    std::string comp_entry_double;
    
    
    
//    operator() compare functor: constatns = col index
    // pass in as ctor: idx for col = blah, val
    //create comparator objects (<, >, =), use for print where + delete
    
    
public:
    
//    Table();
//    Table(std::vector<std::string> col_names, std::vector<EntryType> col_types, std::vector<std::vector<TableEntry>> table) : col_names(col_names), col_types(col_types), table(table) {}
    bool is_quiet = false;
    uint32_t bst_idx;
    std::vector<std::string> col_names;
    std::vector<EntryType> col_types;
//    TableEntry comp_entry;
//    uint32_t comp_col_idx;
    
    std::map<TableEntry, std::vector<uint32_t>> bst_index; //vector holds indices
    std::unordered_map<TableEntry, std::vector<uint32_t>> hash_index; //vector hold indices
    
    std::vector<std::vector<TableEntry>> table; //move this back to private
    
 
    void func_create(std::string tablename);
//    void func_remove(std::unordered_map<std::string, Table> db);
    void func_insert(std::string tablename);
    void func_print(std::string tablename);
    void func_delete(std::string tablename);
    int func_print_all(std::vector<uint32_t> names_idx);
    int func_print_where(TableEntry entry, uint32_t idx, char op, std::vector<uint32_t> names_idx);
    
    TableEntry type_helper(uint32_t idx);
    TableEntry get_entry(TableEntry t);
    void func_generate(std::string tablename);
    
    
    
    
};

struct compare_greater {
    bool operator()(const std::vector<TableEntry> &row);
    uint32_t idx;
    TableEntry entry;
    
    compare_greater(uint32_t idx, TableEntry entry) : idx(idx), entry(entry) {}
    
};

struct compare_less {
    bool operator()(const std::vector<TableEntry> &row);
    uint32_t idx;
    TableEntry entry;
    
    compare_less(uint32_t idx, TableEntry entry) : idx(idx), entry(entry) {}
    
};

struct compare_equal {
    bool operator()(const std::vector<TableEntry> &row);
    uint32_t idx;
    TableEntry entry;
    
    compare_equal(uint32_t idx, TableEntry entry) : idx(idx), entry(entry) {}
    
};

//bool compare_greater(const std::vector<TableEntry> row, TableEntry entry, Table t);

//bool compare_less(const std::vector<TableEntry> row, Table t);
//
//bool compare_equal(const std::vector<TableEntry> row, Table t);

//struct compare_greater {
//    bool operator()(const std::vector<TableEntry> row, uint32_t index, TableEntry val);
//};




class Database {
    
private:
    
    
//    Table curr_table;
    
public:
    
    bool on = false;
    std::unordered_map<std::string, Table> db;
    std::unordered_map<std::string, Table> getDB();
    void func_remove(std::unordered_map<std::string, Table> db, std::string tablename);
//    void func_join(std::unordered_map<std::string, Table> db);
    void func_join(std::string table1, std::string table2, std::unordered_map<std::string, Table> db);
    void execute();
    
    
};




