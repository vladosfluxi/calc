#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <variant>
#include <vector>
using namespace std;

int main() {

  cout << "This is an advanced calculator.\n";
  cout << "Here you can enter a big query.\n";
  cout << "Enter your query: ";

  string query;
  string allowed = "0123456789+-*/()";

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
            throw invalid_argument("You cannot sum/substract chars ");
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
  // if f
  if (query[0] != '-') query.insert(query.begin(), '+');

  vector<double> finalNum;
  vector<variant<double, char>> nums;
  double summary = 0;
  char charSign2;

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
      charSign2 = '+';
      i++;
    } else if (query[i] == '-') {
      charSign2 = '-';
      i++;
    }

    size_t start = i;
    string number;

    while (start < query.size() && (query[start] != '+' && query[start] != '-' && query[start] != '/' && query[start] != '*')) {
        number += query[start];
        start++;
      }

    if (charSign2 == '+') {
      nums.push_back(stod(number));
    } else if (charSign2 == '-') {
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