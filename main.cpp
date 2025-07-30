#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){

    cout << "This is an advanced calculator.\n";
    cout << "Here you can enter a big query.\n";
    cout << "Enter your query: ";
    cout << endl;

    string query;
    string notBanned[] = {"1","2","3","4","5","6","7","8","9","0","+","-","*","/"};

    while (true)
    {
        try {
            
            getline(cin,query);

            if(query.empty()){
                throw runtime_error("It cannot be empty\nEnter your query again:");
            }
            else if(!isdigit(query[0])){
                throw invalid_argument("It cannot start with symbol\nEnter your query again:");
            }
            else{
                for(string& a : notBanned){
                    if(!query.find(a) == string::npos){
                        throw invalid_argument("query must not have alphabetic elements\nEnter your query again:");
                    }
                }
            }
            break;

            
        }
        catch(const exception& e) {
            cout << "Invalid input: " << e.what();
        }
    }
    
    query.erase(remove(query.begin(), query.end(), ' '), query.end());
    
    
    
    cout << query;

}