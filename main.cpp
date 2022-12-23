//
//  IDENTIFIER  = C0F4DFE8B340D81183C208F70F9D2D797908754D
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include "getopt.h"
#include "xcode_redirect.hpp"
#include "silly.hpp"

using namespace std;

bool quiet_mode;

void printHelp() {
    //implement
    cout << "Accetable commands: CREATE, REMOVE, INSERT, PRINT, DELETE, JOIN, GENERATE, QUIT" << '\n';
    exit(0);
}

void getMode(int argc, char * argv[]) {
    
//        bool modeSpecified = false;
        opterr = false;
        int choice;
        int option_index = 0;
        option long_options[] = {
            {"help", no_argument, nullptr, 'h'},
            {"quiet", no_argument, nullptr, 'q'},
            { nullptr, 0,                 nullptr, '\0' }
        };
    
        while ((choice = getopt_long(argc, argv, "hq", long_options, &option_index)) != -1) {
            switch (choice) {
            
            case 'q':
                    //implement
                    quiet_mode = true;
                    break;
            case 'h':
                printHelp();
//                    modeSpecified = true;
                exit(0);
            
    
            default:
                cerr << "Unknown command line option" << endl;
                exit(1);
            } // switch
        } // while
    
}


int main(int argc, char *argv[]) {
//int main() {
    std::ios_base::sync_with_stdio(false);
    cin >> std::boolalpha;
    cout << std::boolalpha;
    cin.tie(NULL);
    
    xcode_redirect(argc, argv);
    getMode(argc, argv);
    Database d;
    if(quiet_mode == true) {
        d.on = true;
    }
    else {
        d.on = false;
    }
    d.execute();
    
    

    
    return 0;
    
}
