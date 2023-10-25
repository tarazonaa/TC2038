#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

vector<int> suffixes(string s) {
  vector<pair<int, string>> sufijos;
  for (int i = 0; i < s.size(); ++i) {
    sufijos.push_back(make_pair(i, s.substr(i)));
  }
  sort(sufijos.begin(), sufijos.end(),
       [](pair<int, string> a, pair<int, string> b) {
         return a.second < b.second;
       });
  vector<int> res;
  for (int i = 0; i < sufijos.size(); ++i) {
    res.push_back(sufijos[i].first);
  }
  return res;
}
int main() {
  string s;
  cout << "Dame un string: ";
  cin >> s;
  cout << "El string es: " << s << endl;
  vector<int> sufijos = suffixes(s);
  cout << "El suffix array es: " << endl;
  for (int i = 0; i < sufijos.size(); ++i) {
    cout << sufijos[i] << " ";
  }
}
