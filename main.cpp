#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

using namespace std;

void finalSum(string& query){
  vector<double> finalNum;
  vector<variant<double, char>> nums;
  double summary = 0;    
  char charSign = '+';

  for (size_t i = 0; i < query.size(); i++) {

    if (query[i] == '*') {
      nums.push_back(static_cast<char>('*'));
      if (isdigit(static_cast<unsigned char>(query[i + 1])))
        query.insert(query.begin() + (i+1), '+');
      i++;
    } else if (query[i] == '/') {
      nums.push_back(static_cast<char>('/'));
      if (isdigit(static_cast<unsigned char>(query[i + 1])))
        query.insert(query.begin() + (i+1), '+');
      i++;
    }

    if (query[i] == '+') {
      charSign = '+';
      i++;
    } else if (query[i] == '-') {
      charSign = '-';
      i++;
    }

    size_t start = i;
    string number;

    while (start < query.size() && (query[start] != '+' && query[start] != '-' && query[start] != '/' && query[start] != '*')) {
        number += query[start];
        start++;
      }

    if (charSign == '+') {
      nums.push_back(stod(number));
    } else if (charSign == '-') {
      nums.push_back(-(stod(number)));
    }
    i = start - 1;
  }

  for (size_t i = 0; i < nums.size(); i++) {
    if (holds_alternative<char>(nums[i]) && get<char>(nums[i]) == '*') {
      double num = get<double>(nums[i - 1]) * get<double>(nums[i + 1]);
      size_t start = i - 1;
      size_t count = 3;

      nums.erase(nums.begin() + start, nums.begin() + start + count);
      nums.insert(nums.begin() + start, num);
      i = start;
    }

    if (holds_alternative<char>(nums[i]) && get<char>(nums[i]) == '/') {
      double num = get<double>(nums[i - 1]) / get<double>(nums[i + 1]);
      size_t start = i - 1;
      size_t count = 3;

      nums.erase(nums.begin() + start, nums.begin() + start + count);
      nums.insert(nums.begin() + start, num);
      i = start;
    }
  }

  if (holds_alternative<double>(nums[0])) {
    finalNum.reserve(nums.size());
    for (const auto &i : nums) {
      finalNum.push_back(get<double>(i));
    }
  }

  for (size_t i = 0; i < finalNum.size(); i++) {
    summary += finalNum[i];
  }
  cout << summary << endl;
  cout << endl;

  for (auto &i : nums) {
    visit([](const auto &val) { cout << val << " "; }, i);
    }

}

void bracketSolving(string subQuery,string& query,int lastOpeningBracketIndex,int firstClosingBracketIndex){
  vector<double> subFinalNum;
  vector<variant<double,char>> subNums;
  double subSummary = 0;
  char subCharSign = '+';
  for (size_t i = 0; i < query.size(); i++) {

    if (subQuery[i] == '*') {
      subNums.push_back(static_cast<char>('*'));
      if ( i + 1 < subQuery.size() &&  isdigit(static_cast<unsigned char>(subQuery[i + 1])))
        subQuery.insert(subQuery.begin() + (i+1), '+');
      i++;
    } else if (subQuery[i] == '/') {
      subNums.push_back(static_cast<char>('/'));
      if (i+1 < subQuery.size() && isdigit(static_cast<unsigned char>(subQuery[i + 1])))
        subQuery.insert(subQuery.begin() + (i+1), '+');
      i++;
    }

    if (subQuery[i] == '+') {
      subCharSign = '+';
      i++;
    } else if (query[i] == '-') {
      subCharSign = '-';
      i++;
    }

    size_t start = i;
    string number;
    
    while (start < subQuery.size() && (subQuery[start] != '+' && subQuery[start] != '-' && subQuery[start] != '/' && subQuery[start] != '*')) {
        
        number += subQuery[start];
        start++;
      }

    if (subCharSign == '+') {
      subNums.push_back(stod(number));
    } else if (subCharSign == '-') {
      subNums.push_back(-(stod(number)));
    }
    i = start - 1;
  }

  for (size_t i = 0; i < subNums.size(); i++) {
    if (holds_alternative<char>(subNums[i]) && get<char>(subNums[i]) == '*') {
      double num = get<double>(subNums[i - 1]) * get<double>(subNums[i + 1]);
      size_t start = i - 1;
      size_t count = 3;

      subNums.erase(subNums.begin() + start, subNums.begin() + start + count);
      subNums.insert(subNums.begin() + start, num);
      i = start;
    }

    if (holds_alternative<char>(subNums[i]) && get<char>(subNums[i]) == '/') {
      double num = get<double>(subNums[i - 1]) / get<double>(subNums[i + 1]);
      size_t start = i - 1;
      size_t count = 3;

      subNums.erase(subNums.begin() + start, subNums.begin() + start + count);
      subNums.insert(subNums.begin() + start, num);
      i = start;
    }
  }

  if (holds_alternative<double>(subNums[0])) {
    subFinalNum.reserve(subNums.size());
    for (const auto &i : subNums) {
      subFinalNum.push_back(get<double>(i));
    }
  }

  for (size_t i = 0; i < subFinalNum.size(); i++) {
    subSummary += subFinalNum[i];
  }
  
  string strSubSummary;
  if(subSummary < 0){
    strSubSummary = to_string(subSummary);
  }else if(subSummary >= 0){
    strSubSummary = "+" + to_string( subSummary);
  }  

  //replacement
  
  if(query[lastOpeningBracketIndex-1] =='+' && strSubSummary[0] == '-')
  {
    query.replace(query.begin()+lastOpeningBracketIndex-1,query.begin()+firstClosingBracketIndex,strSubSummary);
  }
  if(query[lastOpeningBracketIndex-1] =='-' && strSubSummary[0] == '+')
  {
    strSubSummary[0] = '-'; 
    query.replace(query.begin()+lastOpeningBracketIndex-1,query.begin()+firstClosingBracketIndex,strSubSummary);
  }
  if(query[lastOpeningBracketIndex-1] =='+' && strSubSummary[0] == '+')
  {
    query.replace(query.begin()+lastOpeningBracketIndex-1,query.begin()+firstClosingBracketIndex,strSubSummary);
  }
  if(query[lastOpeningBracketIndex-1] =='-' && strSubSummary[0] == '-')
  {
    strSubSummary[0] = '+';
    query.replace(query.begin()+lastOpeningBracketIndex-1,query.begin()+firstClosingBracketIndex,strSubSummary);
  }
  if(query[lastOpeningBracketIndex-1] == '*' || query[lastOpeningBracketIndex-1] == '/')
  {
    query.replace(query.begin()+lastOpeningBracketIndex,query.begin()+firstClosingBracketIndex,strSubSummary);
  }
}

//main function
int main() {

  cout << "This is an advanced calculator.\n";
  cout << "Here you can enter a big query.\n";
  cout << "Enter your query: ";

  string query;
  string allowed = "0123456789+-*/().";

  // input validation
  while (true) {
    try {
      getline(cin, query);

      query.erase(remove_if(query.begin(), query.end(),
                            [](unsigned char ch) { return isspace(ch); }),
                  query.end());

      if (query.empty()) throw invalid_argument("It cannot be empty");
      

      else if (!(isdigit(static_cast<unsigned char>(query[0])) || query[0] == '-' || query[0] == '+' || query[0] == '(')) {
        throw invalid_argument("It cannot start with different that +|-|/|*|( ");
      }

      else {
        for (char c : query) {
          if (allowed.find(c) == string::npos) {
            throw invalid_argument(
                "Query must not contain alphabetic or invalid characters");
          }
        }

        for (size_t i = 0; i < query.size(); i++) {
          if ((query[i] == '-' || query[i] == '+') && (query[i + 1] == '/' || query[i + 1] == '*' || query[i + 1] == '+' || query[i + 1] == '-'))
            throw invalid_argument("You cannot sum/substract chars");
          if ((query[i] == '/' || query[i] == '*') && (query[i + 1] == '/' || query[i + 1] == '*')) throw invalid_argument("You cannot multiply/divide chars");
        }

        for (size_t i = 0; i < query.size(); i++) {
          if ((query[i] == '/' || query[i] == '*') && query[i + 1] == '0')
            throw invalid_argument("Cannot multiply/divide by zero");
        }
      }
      break;
    } catch (const exception &e) {
      cout << "Invalid input: " << e.what() << "\nEnter your query again: ";
    }
  }
  // if first character is not - then it will be plus
  if (query[0] != '-') query.insert(query.begin(), '+');
  
  for(int i = 0;i < (int)query.size();i++){
    if(query[i] == '(' && query[i+1] == '('){
      query.insert(query.begin()+i+1,'+');
      i=0;
    }
    if(query[i] ==')' && query[i+1] =='('){
      query.insert(query.begin()+i+1,'*');
      i=0;
    }
    if(query[i] == '(' && isdigit((int)query[i+1])){
      query.insert(query.begin()+i+1,'+');
      i=0;
    }
  }

  // this is if in the query there are brackets;
  bool bracketFound = true;
  int br = 0;
  while(bracketFound){
    for(char a : query){
      if(a == ')' || a == '('){
        string subQuery;
        br++;
        int lastOpeningBracketIndex = 0;
        int firstClosingBracketIndex = 0;
        for(int i = (int)query.size()-1; i >= 0;i--){
          if(query[i] == '(') {
            lastOpeningBracketIndex = i;
            break;
            
          } 
        }
        for(int i = lastOpeningBracketIndex; i < (int)query.size();i++){
          if(query[i] == ')'){
            firstClosingBracketIndex = i;
            break;
          }
        }
        for(int i = lastOpeningBracketIndex+1;i  < firstClosingBracketIndex;i++){
          subQuery.push_back(query[i]);
        }
        bracketSolving(subQuery, query, lastOpeningBracketIndex, firstClosingBracketIndex);
      }
    }
    if(br < 1){
      bracketFound = false;
    }else{
      br = 0;
    }
  }
      
  finalSum(query);
}
