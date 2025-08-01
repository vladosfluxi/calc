#include <iostream>
#include <string>
#include <algorithm>
#include <variant>
#include <vector>
#include <cmath>
using namespace std;

int main(){

    cout << "This is an advanced calculator.\n";
    cout << "Here you can enter a big query.\n";
    cout << "Enter your query: ";
    cout << endl;

    string query;
    string allowed = "0123456789+-*/";

    while (true) {
        try {
            getline(cin, query);
            
            query.erase(remove_if(query.begin(), query.end(), 
                      [](unsigned char ch){ return isspace(ch); }), 
            query.end()); 
            if (query.empty()) {
                throw runtime_error("It cannot be empty");
            }
            else if (!(isdigit(static_cast<unsigned char>(query[0])) || query[0] == '-' || query[0] == '+' )) {
                throw invalid_argument("It cannot start with symbol");
            }
            
            else {
                for (char c : query) {
                    if (allowed.find(c) == string::npos) { 
                        throw invalid_argument("Query must not contain alphabetic or invalid characters");
                    }
                }

                for(int i = 0; i < query.size();i++){
                    if((query[i] == '+' || query[i] == '-' || query[i] == '*' || query[i] == '/' ) && (query[i+1] == '+' || query[i+1] == '-' || query[i+1] == '*' || query[i+1] == '/') ){
                    throw invalid_argument("The character in query must not appear after another one");
                }
                }

            }

            break; // valid input
        }
        catch (const exception& e) {
            cout << "Invalid input: " << e.what() << "\nEnter your query again: ";
        }
    }
    
    // for(int i = 0; i < query.size();i++){
    //     if((query[i] == '+' || query[i] == '-' || query[i] == '*' || query[i] == '/' ) && (query[i+1] == '+' || query[i+1] == '-' || query[i+1] == '*' || query[i+1] == '/') ){
    //         cout << 
    //     }
    // }


    

    // vector<variant<double ,string>> vec;
    // double summary = 0;

    // for(int i = 0;i < query.size()-1;i+=4){
    //     for(int j = i;j < i+2;j++){
    //         double sentense = stoi(string{1,query[j]});
    //         switch(query[j+1]){
    //             case '+':
    //                 sentense + stoi(string(1,query[j+2]));
    //                 break;
    //             case '-':
    //                 sentense - stoi(string(1,query[j+2]));
    //                 break;
    //             case '*':
    //                 sentense - stoi(string(1,query[j+2]));
    //                 break;
    //             case '/':
    //                 sentense - stoi(string(1,query[j+2]));
    //                 break;
    //         }
    //         vec.push_back(sentense);
    //         vec.push_back(string(1,query[(j-i)/2])); 
    //         break;
    //     }
        
    // }




    // for(size_t i = 0; i < query.size();i+){
    //     char op;
    //     for(int j = i;)
    // }
    // for(auto &item : vec){
    //     visit([](auto &&value){
    //         cout << value << " ";
    //     },item);
    // }


    //1 +2 -3 +4 -5+6
    cout << query;

}