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
    while (true)
    {
        try {
            
            getline(cin,query);

            if(query.empty()){
                throw runtime_error("It cannot be empty");
            }
            else if(!isdigit(query[0])){
                throw invalid_argument("It cannot start with symbol");
            }
            else if{
                for(size_t i = 0; i < query.size()-1;i++)[
                    if()
                ]
            }
            else{
                continue;
            }
        }
        catch(const exception& e) {
            cout << "Invalid input:" << e.what();
        

        }
    }
    
    


    // query.erase(remove(query.begin(),query.end(),' '),query.end());
    
    cout << query;

}