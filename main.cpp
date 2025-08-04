#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

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

                for(int i = 0; i < query.size();i++){
                    if((query[i] == '/' || query[i] == '*') && query[i + 1] == '0' ) throw invalid_argument("Cannot multiply/divide by zero");
                }
            }

            break; 
        }
        catch (const exception& e) {
            cout << "Invalid input: " << e.what() << "\nEnter your query again: ";
        }
    }
    
        

    if(query[0] != '-') query.insert(query.begin(),'+');

    vector<double> nums;
    double summary = 0;
    

    for(size_t i = 0; i < query.size();i++){
        char charSign = '+';
        if(query[i]=='+'){
            charSign='+';
            i++;
        }else if(query[i]=='-'){
            charSign='-';i++;
        }
                
        size_t start = i;
        string bigNum;

        while(start < query.size() && (query[start] != '+' && query[start]!='-')){
            bigNum.push_back(query[start]);           
            start++;
            

        }
        i = start-1;

        if(charSign == '+'){
            nums.push_back(stod(bigNum));

        }else{
           nums.push_back(-(stod(bigNum)));
        }
    }

    for(double i : nums){
        summary += i;
    }

    cout << summary << endl;

     
    

}