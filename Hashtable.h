
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


class Hashtable{
private:
  static const int size = 23;

  struct item{
    string name;
    int index;
    item* next = nullptr;
  };

  //Array of linked lists
  item* Hashing[size];
  int hash(string key);
  int NumberOfItemsInIndex(int index);
  void PrintTable(); // for debug


public:
  Hashtable();
  ~Hashtable() {for(int i = 0; i < size; i++) delete Hashing[i];}
  void add(string name, int score);
  //i.e Searching for key
  int FindIndex(string name);
  void RemoveItem(string name);
};



#endif // HASHTABLE_H
