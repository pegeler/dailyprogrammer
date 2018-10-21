#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cstring>
using namespace std;

bool funnel(string a, string b) 
{
  int b_len = b.size();
  if (a.size() != b_len + 1) return false;
  
  int i=0, j=0;
  bool skipped = false;
  
  while (j < b_len)
  {
    if (a[i] != b[j]) { 
      if (skipped) return false;
      skipped = true;
      i++;
    }
    else i++, j++;
  }
  
  return true;
}

set<string>* get_wordlist(string filename)
{
  string word;
  ifstream file(filename);
  
  set<string>* wordlist = new set<string>;
  
  while(file >> word)
  {
    wordlist->insert(word);
  }
  
  return wordlist;

}

void print_word_set(set<string>* words)
{

  bool first = true;
  
  cout << "[";
  for (auto i = words->cbegin(); i != words->cend(); i++)
  {
    if (first) first = false; 
    else cout << ", ";
    
    cout << *i;
  }
  cout << "]" << endl;

}

set<string>* bonus(string x, set<string>* words)
{

  int x_len = x.size();
  set<string>* result = new set<string>;
  char buf[x_len];
  
  buf[x_len - 1] = 0;
  
  for (int i=0; i < x_len; i++)
  {
    int j=0, k=0;
    while(j < x_len)
    {
      if (j == i) j++;
      buf[k++] = x[j++];
    }
    
    string candidate = buf;
    
    if (words->find(candidate) != words->end()) result->insert(candidate); 
    
  }

  return result;
}

int bonus2(set<string>* words) 
{
  int n=0;
  for (auto i = words->cbegin(); i != words->cend(); i++)
  {
    if (i->size() >= 5) {
      set<string>* result = bonus(*i, words);
    
      if (result->size() == 5) {
        cout << "bonus(" << *i << ") => "; print_word_set(result);
        n++;
      }
      
    }
  }
  
  return n;
}

int main(int argc, char *argv[])
{ 
  // FUNNEL ------------------------------------------------
  if (!strcmp(argv[0],"funnel"))
  {
    if (argc != 3) {
      cout << "Sorry, you must have two arguments." << endl; 
      return 1;
    }
    
    cout << 
      "funnel(" << argv[1] << ", " << argv[2] << ") => " <<
      funnel(argv[1], argv[2]) << endl;
  }
  
  // BONUS ------------------------------------------------
  else if (!strcmp(argv[0],"bonus"))
  {
    if (argc != 2) {
      cout << "Sorry, you must have one argument." << endl; 
      return 2;
    }
    
    auto wordlist = get_wordlist("../../enable1.txt");
    //auto wordlist = get_wordlist("enable1_subset.txt");
    
    cout << "bonus(" << argv[1] <<") => ";
      print_word_set(bonus(argv[1], wordlist));
  } 
  
  // BONUS2 ------------------------------------------------
  else if (!strcmp(argv[0],"bonus2"))
  {
    if (argc != 1) {
      cout << "Sorry, this takes no arguments." << endl; 
      return 3;
    }
    
    auto wordlist = get_wordlist("../../enable1.txt");
    int n = bonus2(wordlist);
    
    cout << "The total number of words are: " << n << endl;

  } 
  
  // INCORRECT INPUT -----------------------------------------
  else return 4;
  
  return 0;
}
