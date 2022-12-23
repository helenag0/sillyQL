//
//  silly.cpp
//  project3
//
//  IDENTIFIER  = C0F4DFE8B340D81183C208F70F9D2D797908754D
//

#include "silly.hpp"
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>


//#include "xcode_redirect.hpp"
//#include "TableEntry.h"
//#include "database.hpp"

using namespace std;

//Table::Table(std::vector<std::string> col_names, std::vector<EntryType> col_types, std::vector<std::vector<TableEntry>> table) {
//    col_names = col_names;
//    col_types = col_types;
//    table = table;
//}

bool compare_greater::operator()(const std::vector<TableEntry> &row) {
    // >
    if(row[idx] > entry) {
        return true;
    }
    else {
        return false;
    }
}


bool compare_less::operator()(const std::vector<TableEntry> &row) {
    // <
    if(row[idx] < entry) {
        return true;
    }
    else {
        return false;
    }
    
}

bool compare_equal::operator()(const std::vector<TableEntry> &row) {
    // =
    if(row[idx] == entry) {
        return true;
    }
    else {
        return false;
    }
}

std::unordered_map<std::string, Table> Database::getDB() {
    return db;
}

//Table::Table() {}

void Database::execute() {
    
//    Database d;
    std::unordered_map<std::string, Table> db = getDB();
    
    std::string command;
//    Table t = curr_table;
    
    cout << "% "; // ??
    cin >> command;
    
    do {
        
        if (cin.fail()) {
            cerr << "Error: Reading from cin has failed" << endl;
            exit(1);
        } // if
        
        
//        std::vector<std::string> col_names;
//        std::vector<EntryType> col_types;
//        std::vector<std::vector<TableEntry>> table;
//        Table t;
        if(command == "CREATE") {
            std::string tablename;
            cin >> tablename;
            if(db.find(tablename) != db.end()) { //check that tablename is not already in database
                cout << "Error during CREATE: Cannot create already existing table " << tablename << '\n';
                getline(cin, tablename);
                cout << "% "; // ??
                cin >> command;
                continue;
            }
            Table& t = db[tablename];
            t.func_create(tablename);
            cout << "% "; // ??
            cin >> command;
        }
        
        else if(command[0] == '#') {
            getline(cin, command);
            cout << "% "; // ??
            cin >> command;
            continue; //trash this line and keep going
        }
        
        else if(command == "REMOVE") {
            std::string tablename;
            cin >> tablename;

            if(db.find(tablename) == db.end()) { //if key does not exist
                cout << "Error during REMOVE: " << tablename << " does not name a table in the database" << '\n';
        //        return;
                getline(cin, tablename);
                cout << "% "; // ??
                cin >> command;
                continue;
            }
            func_remove(db, tablename);
            cout << "% "; // ??
            cin >> command;
        }
        
        else if(command == "INSERT") {
            std::string junk;
            std::string tablename;
            cin >> junk >> tablename;
            if(db.find(tablename) == db.end()) { //if key does not exist
                cout << "Error during INSERT: " << tablename << " does not name a table in the database" << '\n';
                getline(cin, tablename);
                cout << "% "; // ??
                cin >> command;
        //        return;
                continue;
            }
            
            Table& t = db[tablename];
            t.func_insert(tablename);
            cout << "% "; // ??
            cin >> command;
        }
        
        else if(command == "PRINT") {
            std::string junk;
            std::string tablename;
            cin >> junk >> tablename;
            if(db.find(tablename) == db.end()) { //if key does not exist
                cout << "Error during PRINT: " << tablename << " does not name a table in the database" << '\n';
                getline(cin, tablename);
                cout << "% "; // ??
                cin >> command;
        //        return;
                continue;
            }
            Table& t = db[tablename];
//            if(d.is_quiet == true) {
//                t.is_quiet = true;
//            }
            if(on == true) {
                t.is_quiet = true;
            }
            else {
                t.is_quiet = false;
            }
            t.func_print(tablename);
            cout << "% "; // ??
            cin >> command;
        }
        else if(command == "DELETE") {
            std::string junk;
            std::string tablename;
            cin >> junk >> tablename;
            if(db.find(tablename) == db.end()) { //if key does not exist
                cout << "Error during DELETE: " << tablename << " does not name a table in the database" << '\n';
                getline(cin, tablename);
                cout << "% "; // ??
                cin >> command;
        //        return;
                continue;
            }
            Table& t = db[tablename];
            t.func_delete(tablename);
            cout << "% "; // ??
            cin >> command;
        }
        else if(command == "JOIN") {
            std::string junk;
            std::string table1;
            std::string table2;
            cin >> table1 >> junk >> table2 >> junk;
            if(db.find(table1) == db.end()) { //if key does not exist
                cout << "Error during JOIN: " << table1 << " does not name a table in the database" << '\n';
                getline(cin, table1);
                cout << "% "; // ??
                cin >> command;
                continue;
            }
            if(db.find(table2) == db.end()) { //if key does not exist
                cout << "Error during JOIN: " << table2 << " does not name a table in the database" << '\n';
                getline(cin, table2);
                cout << "% "; // ??
                cin >> command;
                continue;
            }
            Table& t1 = db[table1];
            if(on == true) {
                t1.is_quiet = true;
            }
            else {
                t1.is_quiet = false;
            }
            func_join(table1, table2, db);
            cout << "% "; // ??
            cin >> command;
        }
        else if(command == "GENERATE") {
            std::string junk;
            std::string tablename;
            cin >> junk >> tablename;
            if(db.find(tablename) == db.end()) { //if key does not exist
                cout << "Error during GENERATE: " << tablename << " does not name a table in the database" << '\n';
                getline(cin, tablename);
                cout << "% "; // ??
                cin >> command;
        //        return;
                continue;
            }
            
            Table& t = db[tablename];
            t.func_generate(tablename);
            cout << "% "; // ??
            cin >> command;
        }
        
        else {
            getline(cin, command);
            cout << "Error: unrecognized command" << '\n';
            cout << "% "; // ??
            cin >> command;
            continue;
//            continue; //trash this line and keep going
        }
        
//        cout << "% "; // ??
//        cin >> command;
    }
    while(command != "QUIT");
    
    //when command is quit
    //clean up memory!!
    cout << "Thanks for being silly!" << '\n';
    
}

void Table::func_create(std::string tablename) {
    
//    Database d;
//    std::unordered_map<std::string, Table> db = d.getDB();
    
    // CREATE <tablename> <N> <coltype1> <coltype2> ... <coltypeN> <colname1> <colname2> ... <colnameN>
    
//    std::string tablename;
    std::string coltype;
    std::string colname;
    int num;
//        vector<EntryType> types;
//    cin >> tablename;
//    if(db.find(tablename) != db.end()) { //check that tablename is not already in database
//        cout << "Error during CREATE: Cannot create already existing table " << tablename << '\n';
//        exit(1);
//    }
//        unordered_map<string, TableEntry> tablename;
//    Table& new_table = db[tablename];
    cin >> num;
    int i = 0;
    while(i != num) {
        cin >> coltype;
        switch(coltype[0]) {
            case 'b'     :
//                new_table.col_types.push_back(EntryType::Bool);
                col_types.push_back(EntryType::Bool);
                i++;
                continue;
            case 's'   :
//                new_table.col_types.push_back(EntryType::String);
                col_types.push_back(EntryType::String);
                i++;
                continue;
            case 'i'      :
//                new_table.col_types.push_back(EntryType::Int);
                col_types.push_back(EntryType::Int);
                i++;
                continue;
            case 'd'   :
//                new_table.col_types.push_back(EntryType::Double);
                col_types.push_back(EntryType::Double);
                i++;
                continue;
        }
    }
    
    
    cout << "New table " << tablename << " with column(s) ";
    
    for(int i = 0; i < num; i++) {
        cin >> colname;
//        new_table.col_names.push_back(colname);
        col_names.push_back(colname);
//        new_table.table.emplace_back(colname);
        cout << colname << " ";
        
        // table = < col_name<col_entry>>
//            tablename[colname] = vector<vector<(types[i])>> colname;
    }
    cout << "created" << '\n';

// New table <tablename> with column(s) <colname1> <colname2> ... <colnameN> created

}

void Database::func_remove(std::unordered_map<std::string, Table> db, std::string tablename) {

    Table& t = db[tablename];
    t.bst_index.clear();
    t.hash_index.clear();
    db.erase(tablename); //const? needs to erase key and val associated with tablename key
    
    cout << "Table " << tablename << " deleted" << '\n';
}

void Table::func_insert(std::string tablename) {
    
    std::string junk;
    uint32_t num;
    cin >> num >> junk;

    uint32_t j = static_cast<uint32_t>(col_types.size());
    uint32_t curr_size = static_cast<uint32_t>(table.size());
    table.resize(num + curr_size);
   
    cout << "Added " << num << " rows to " << tablename <<
    " from position " << curr_size << " to " << (num + (curr_size - 1)) << '\n';
    
//    uint32_t y = curr_size;
    for(uint32_t i = curr_size; i < (curr_size + num); i++) {
//        table[i].reserve(col_types.size());
            for(uint32_t x = 0; x < j; x++) {
                switch(col_types[x]) {
                    case EntryType::Int: {
                        int val_i;
                        cin >> val_i;
                        table[i].emplace_back(val_i);
                        // cout << val_i << " ";
                        break;
                    }
                        
                    case EntryType::Bool: {
                        bool val_b;
                        cin >> val_b;
                        table[i].emplace_back(val_b);
                        // cout << val_b << " ";
                        break;
                    }
                    
                    case EntryType::String: {
                        std::string val_s;
                        cin >> val_s;
                        table[i].emplace_back(val_s);
                        // cout << val_s << " ";
                        break;
                    }
                 
                        
                    case EntryType::Double: {
                        double val_d;
                        cin >> val_d;
                        table[i].emplace_back(val_d);
                        // cout << val_d << " ";
                        break;
                    }
                }
            
        }
//        cout << '\n';
    }
    
    if(!bst_index.empty()) {
        bst_index.clear();
        for(uint32_t j = 0; j < table.size(); j++) {
            bst_index[table[j][bst_idx]].emplace_back(j);
        }
    }
    
    
}

void Table::func_print(std::string tablename) {
    
    //PRINT FROM <tablename> <N> <print_colname1> <print_colname2> ... <print_colnameN> {WHERE <colname> <OP> <value> | ALL}
    uint32_t num;
    std::string junk;
    cin >> num;
    
    
    std::string c_n;
    std::vector<std::string> names;
    std::vector<uint32_t> names_idx;
    
    for(uint32_t i = 0; i < num; i++)  {
        cin >> c_n;
        if(std::find(col_names.begin(), col_names.end(), c_n) == col_names.end()) {
            cout << "Error during PRINT: " << c_n << " does not name a column in " << tablename << '\n';
            getline(cin, c_n);
            return;
        }
        names.emplace_back(c_n);
        if(i != (num - 1)) {
            cout << c_n << " ";
        }
        else {
            cout << c_n << '\n';
        }
    }
    
//    for(uint32_t i = 0; i < col_names.size(); i++) {
//        for(auto& it2 : names) {
//            if(col_names[i] == it2) {
//                names_idx.push_back(i);
//            }
//        }
//
//    }
    for(auto& it2 : names) {
        uint32_t i = 0;
        while(col_names[i] != it2) {
            i++;
        }
        names_idx.push_back(i);
//        for(uint32_t i = 0; i < col_names.size(); i++) {
//            if(col_names[i] == it2) {
//                names_idx.push_back(i);
//            }
//        }
        
    }
    
    
    cin >> junk;
    int m = 0;
    
    if(junk == "ALL") {
        m = func_print_all(names_idx);
    }

    if(junk == "WHERE") {
        char op;
        cin >> c_n >> op;
        if(std::find(col_names.begin(), col_names.end(), c_n) == col_names.end()) {
            cout << "Error during PRINT: " << c_n << " does not name a column in " << tablename << '\n';
            getline(cin, c_n);
            return;
        }
        uint32_t i = 0;
        while(col_names[i] != c_n) {
            i++;
        }
        TableEntry entry = type_helper(i);
        m = func_print_where(entry, i, op, names_idx);
              
        
    }
    
    cout << "Printed " << m << " matching rows from " << tablename << '\n';
    

}


int Table::func_print_all(std::vector<uint32_t> names_idx) {
    
    int m = 0;
    
    for(uint32_t i = 0; i < table.size(); i++) {
        // for each row, print relevant cols
        for(uint32_t j = 0; j < names_idx.size(); j++) {
            if(is_quiet == false) {
                if(j == (names_idx.size() - 1)) {
                    cout << table[i][names_idx[j]];
                }
                else {
                    cout << table[i][names_idx[j]] << " ";
                }
            }
            
                
       
        }
        m++;
        if(is_quiet == false) {
            cout << '\n';
        }
        
    }
//    cout << '\n';
    return m;
}

int Table::func_print_where(TableEntry entry, uint32_t idx, char op, std::vector<uint32_t> names_idx) {
    int m = 0;
    
    if(!bst_index.empty() && bst_idx == idx) {
        
            switch(op) {
                case('>'): {
                    for(map<TableEntry, vector<uint32_t>>::iterator it = bst_index.begin(); it != bst_index.end(); it++) {
                        for(uint32_t y = 0; y < (*it).second.size(); y++) {
                            if(table[(*it).second[y]][idx] > entry) {
                                for(uint32_t x = 0; x < names_idx.size(); x++) {
                                    if(is_quiet == false) {
                                        cout << table[(*it).second[y]][names_idx[x]] << " ";
                                    }
                                    
                                    
                                }
                                if(is_quiet == false) {
                                    cout << '\n';
                                }
                                
                                m++;
                            }
                        }
                    }
                    break;
                }
                case('<'): {
                    for(map<TableEntry, vector<uint32_t>>::iterator it = bst_index.begin(); it != bst_index.end(); it++) {
                        for(uint32_t y = 0; y < (*it).second.size(); y++) {
                            if(table[(*it).second[y]][idx] < entry) {
                                for(uint32_t x = 0; x < names_idx.size(); x++) {
                                    if(is_quiet == false) {
                                        cout << table[(*it).second[y]][names_idx[x]] << " ";
                                    }
                                    
                                    
                                }
                                if(is_quiet == false) {
                                    cout << '\n';
                                }
                                
                                m++;
                            }
                        }
                    }
                    break;
                }
                case('='): {
                    for(map<TableEntry, vector<uint32_t>>::iterator it = bst_index.begin(); it != bst_index.end(); it++) {
                        for(uint32_t y = 0; y < (*it).second.size(); y++) {
                            if(table[(*it).second[y]][idx] == entry) {
                                for(uint32_t x = 0; x < names_idx.size(); x++) {
                                    if(is_quiet == false) {
                                        cout << table[(*it).second[y]][names_idx[x]] << " ";
                                    }
                                    

                                }
                                if(is_quiet == false) {
                                    cout << '\n';
                                }
                                m++;
                            }
                        }
                    }
                    break;
                }
//                case('='): {
//                    for(auto it = bst_index.begin(); it != bst_index.end(); it++) {
//                        if(table[(*it).second[0]][idx] == entry) {
//                            for(uint32_t y = 0; y < (*it).second.size(); y++) {
//                                for(uint32_t x = 0; x < names_idx.size(); x++) {
//                                    cout << table[(*it).second[y]][names_idx[x]] << " ";
//
//                                }
//                                cout << '\n';
//                                m++;
//                            }
//                        }
//                    }
//                    break;
//                }
        }
    }
    else {
        for(uint32_t i = 0; i < static_cast<uint32_t>(table.size()); i++) {
            switch(op) {
                case('>'): {
                    compare_greater c(idx, entry);
                    if(c(table[i]) == true) {
                        for(uint32_t x = 0; x < names_idx.size(); x++) {
                            if(is_quiet == false) {
                                cout << table[i][names_idx[x]] << " ";
                            }
                        }
                            
    //                        cout << bst_index[i] << " ";
//                        }
                        m++;
                        if(is_quiet == false) {
                            cout << '\n';
                        }
                    }
                    break;
                        
                    //compare_greater(i, entry)
                }
                                        
                case('<'): {
                    compare_less l(idx, entry);
                    if(l(table[i]) == true) {
//                        if(is_quiet == false) {
                        for(uint32_t x = 0; x < names_idx.size(); x++) {
                            if(is_quiet == false) {
                                cout << table[i][names_idx[x]] << " ";
                            }
                        }
    //                        cout << bst_index[i] << " ";
//                        }
                        m++;
                        if(is_quiet == false) {
                            cout << '\n';
                        }
                    }
                    break;
                    //compare_less(i, entry)
                }
                    
                case('='): {
                    compare_equal e(idx, entry);
                    if(e(table[i]) == true) {
//                        if(is_quiet == false) {
                        for(uint32_t x = 0; x < names_idx.size(); x++) {
                            if(is_quiet == false) {
                                cout << table[i][names_idx[x]] << " ";
                            }
                            
                        }
    //                        cout << bst_index[i] << " ";
//                        }
                        m++;
                        if(is_quiet == false) {
                            cout << '\n';
                        }
                    }
                    break;
                    //compare_equal(i, entry)
                }
            }
        }
    }
    
    return m;
}

   



void Table::func_delete(std::string tablename) {
    
    //DELETE FROM <tablename> WHERE <colname> <OP> <value>
    std::string junk;
    std::string c_name;
    char op;
    
    cin >> junk >> c_name >> op;
    
    if(std::find(col_names.begin(), col_names.end(), c_name) == col_names.end()) {
        cout << "Error during DELETE: " << c_name << " does not name a column in " << tablename << '\n';
        getline(cin, c_name);
        return;
    }
    
    uint32_t before = static_cast<uint32_t>(table.size());
    
//    Table& t = db[tablename];
//    uint32_t rows = static_cast<uint32_t>(t.table.size());
    uint32_t i = 0;
    while(col_names[i] != c_name) {
        i++;
    }
//    uint32_t num_rows = 0;
//    comp_col_idx = i;
    TableEntry entry = type_helper(i);
    
    switch(op) {
        case('>'): {
            table.erase(remove_if(table.begin(), table.end(), compare_greater(i, entry)), table.end());
            break;
        }
                                
        case('<'): {
            table.erase(remove_if(table.begin(), table.end(), compare_less(i, entry)), table.end());
            break;
        }
            
        case('='): {
            table.erase(remove_if(table.begin(), table.end(), compare_equal(i, entry)), table.end());
            break;
        }
            
    }
    if(!bst_index.empty()) {
        bst_index.clear();
        for(uint32_t j = 0; j < table.size(); j++) {
            bst_index[table[j][bst_idx]].emplace_back(j);
        }
    }
    
    cout << "Deleted " << (before - table.size()) << " rows from " << tablename << '\n';
    
}

TableEntry Table::type_helper(uint32_t idx) {
    
    switch(col_types[idx]) {
        case EntryType::Int:
            int val_i;
            cin >> val_i;
            return TableEntry{val_i};
//            num_rows += t.func_delete_int(op, t, rows);
            
        case EntryType::Double:
            double val_d;
            cin >> val_d;
            return TableEntry{val_d};
//            num_rows += t.func_delete_double(op, t, rows);
            
        case EntryType::Bool:
            bool val_b;
            cin >> val_b;
            return TableEntry{val_b};
//            num_rows += t.func_delete_bool(op, t, rows);
            
        case EntryType::String:
            std::string val_s;
            cin >> val_s;
            return TableEntry{val_s};
//            num_rows += t.func_delete_string(op, t, rows);
            
    }
    exit(1);
}





//void Database::func_join(std::unordered_map<std::string, Table> db) {
void Database::func_join(std::string table1, std::string table2, std::unordered_map<std::string, Table> db) {
    
    // slow if no hash: temporarily create a hash and delete it as you call join

    std::string junk;
    std::string col1;
    std::string col2;
    uint32_t num;
//    std::unordered_map<TableEntry, std::vector<uint32_t>> temp_hash_1;
//    std::unordered_map<TableEntry, std::vector<uint32_t>> temp_hash_2;
    std::vector<pair<bool, uint32_t>> cols_to_print; // tablenum, col
    
    
    
    // JOIN <tablename1> AND <tablename2> WHERE <colname1> = <colname2> AND PRINT <N>
    
    cin >> col1 >> junk >> col2 >> junk >> junk >> num;
    
    
    Table& t1 = db[table1];
    Table& t2 = db[table2];
    
    if(std::find(t1.col_names.begin(), t1.col_names.end(), col1) == t1.col_names.end()) {
        cout << "Error during JOIN: " << col1 << " does not name a column in " << table1 << '\n';
        getline(cin, col1);
        return;
    }
    if(std::find(t2.col_names.begin(), t2.col_names.end(), col2) == t2.col_names.end()) {
        cout << "Error during JOIN: " << col2 << " does not name a column in " << table2 << '\n';
        getline(cin, col2);
        return;
    }
    
    std::unordered_map<TableEntry, std::vector<uint32_t>> temp_hash_1;
    std::unordered_map<TableEntry, std::vector<uint32_t>> temp_hash_2;

    cols_to_print.resize(num);
    
    uint32_t t1_col;
    uint32_t t2_col;

    uint32_t i = 0;
    while(t1.col_names[i] != col1) { //get index of col
        i++;
    }
    
    t1_col = i;

    uint32_t j = 0;
    while(t2.col_names[j] != col2) { //get index of col
        j++;
    }
    t2_col = j;
    
    //fill hashes
    // hash 1
    for(uint32_t i = 0; i < t1.table.size(); i++) {
        temp_hash_1[t1.table[i][t1_col]].emplace_back(i); // i = index of row for entry
    }
    
    //hash 2
    for(uint32_t i = 0; i < t2.table.size(); i++) {
        
        temp_hash_2[t2.table[i][t2_col]].emplace_back(i); // i = index of row for entry
    }
    
    //print cols
    std::string c_n;
    int table_num;
    for(uint32_t i = 0; i < num; i ++) {
        cin >> c_n >> table_num;
        cout << c_n << " ";
        uint32_t j = 0;
        if(table_num == 1) {
            while(t1.col_names[j] != c_n) { //get index of col
                j++;
            }
            cols_to_print[i] = {true, j};
        }
        if(table_num == 2) {
            while(t2.col_names[j] != c_n) { //get index of col
                j++;
            }
            cols_to_print[i] = {false, j};
        }
    }
    
    cout << '\n';
    
//    uint32_t print_col_idx = 0;
    uint32_t row_count = 0;
    
    //second try
    for(uint32_t i = 0; i < t1.table.size(); i++) {
        if(temp_hash_2.find(t1.table[i][t1_col]) != temp_hash_2.end()) {
            for(uint32_t x = 0; x < temp_hash_2[t1.table[i][t1_col]].size(); x++) {
                for(uint32_t j = 0; j < cols_to_print.size(); j++) {
                    if(cols_to_print[j].first == false) {
                        if(t1.is_quiet == false) {
                            cout << t2.table[temp_hash_2[t1.table[i][t1_col]][x]][cols_to_print[j].second] << " ";
                        }
                        
                    }
                    if(cols_to_print[j].first == true) {
                        if(t1.is_quiet == false) {
                            cout << t1.table[i][cols_to_print[j].second] << " ";
                        }
                    }
                    
                }
                if(t1.is_quiet == false) {
                    cout << '\n';
                }
                row_count++;
            }
            
            
        }
        
    }
    
    cout << "Printed " << row_count << " rows from joining " << table1 << " to " << table2 << '\n';
    
    temp_hash_2.clear();
    temp_hash_1.clear();
}



void Table::func_generate(std::string tablename) {
    //generate: vector of indeces where ties are true
    //bst = map
    //GENERATE FOR <tablename> <indextype> INDEX ON <colname>
    
    
    std::string junk;
    std::string type;
    std::string col;
    
    cin >> type >> junk >> junk >> col;
    
    if(std::find(col_names.begin(), col_names.end(), col) == col_names.end()) {
        cout << "Error during GENERATE: " << col << " does not name a column in " << tablename << '\n';
        return;
    }
    
    bst_index.clear();
    hash_index.clear();
    
    uint32_t c_idx;
//    cin >> junk >> junk >> col;
    uint32_t i;
    for(i = 0; i < col_names.size(); i++) {
        if(col_names[i] == col) {
            break;
        }
    }
    c_idx = i;
    bst_idx = c_idx;
    for(uint32_t j = 0; j < table.size(); j++) {
        if(type == "hash") {
            hash_index[table[j][c_idx]].emplace_back(j);
        }
        if(type == "bst") {
            bst_index[table[j][c_idx]].emplace_back(j);
        }
        
    }
        
    if(type == "hash") {
        cout << "Created hash index for table " << tablename << " on column " << col << '\n';
    }
    if(type == "bst") {
        cout << "Created bst index for table " << tablename << " on column " << col << '\n';
    }
    
}




    






