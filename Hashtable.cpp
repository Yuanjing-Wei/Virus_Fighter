#include "Hashtable.h"
#include <iostream>
#include <ctime>
#include <unistd.h>

using namespace std;
Hashtable::Hashtable(){
  for(int i = 0; i < size; i++){
    Hashing[i] = new item;
    Hashing[i]->name = "empty";
    Hashing[i]->index = -1;
    Hashing[i]->next = nullptr;
  }
}

int Hashtable::hash(string key){
  int hash = 0;
  int index;

  for(int i = 0; i < key.size(); i++){
    hash = (hash + static_cast<int>(key[i])) * 4;

  }

  index = hash % size;

  return index;
}

void Hashtable::add(string name, int score){
   int index = hash(name);

   if(Hashing[index]->name == "empty"){
   Hashing[index]->name = name;
   Hashing[index]->index = score;
 } else{

   item* Ptr = Hashing[index];
   item* n = new item;
   n->name = name;
   n->index = score;
   n->next = nullptr;
      while(Ptr->next != nullptr){
        Ptr = Ptr->next;
      }
  Ptr->next = n;
 }
}

int Hashtable::NumberOfItemsInIndex(int index){
  int count = 0;

  if(Hashing[index]->name == "empty"){
    return count;
  } else{
    count++;
    item* Ptr = Hashing[index];
    while(Ptr->next != nullptr){
      count++;
      Ptr = Ptr->next;
    }
  }
  return count;
}

void Hashtable::PrintTable(){
  int num;
  for (int i = 0; i < size; i++){
    num = NumberOfItemsInIndex(i);
    cout << "# of items in bucket " << i << ": " << num << endl;
    item* Ptr = Hashing[i];
    if(Ptr->name == "empty"){
      cout << "This bucket is empty." << endl;
    } else{
      while(Ptr != nullptr){
        cout << Ptr->name << endl;
        cout << Ptr->index << endl;
        Ptr = Ptr->next;
      }
    }
  }
}

int Hashtable::FindIndex(string name){
  int index = hash(name);
  item* Ptr = Hashing[index];

  if(Ptr->name == "empty"){
    return -1;
  } else{
    while(Ptr != nullptr){
      if(Ptr->name == name){
        return Ptr->index;
      }
      Ptr = Ptr->next;
    }
    return -1;
  }

}

void Hashtable::RemoveItem(string name){
  int index = hash(name);

  item* PointertoDelete;
  item* Pointer1;
  item* Pointer2;

  // If bucket has no items
  if(Hashing[index]->name == "empty"){
    cout << "Cannot delete " << name << "." << " " << name <<  " was not found in hashtable" << endl;
  }
  // If bucket only has 1 item and it matches name matches name given.
  else if(Hashing[index]->name == name && Hashing[index]->next == NULL){
    Hashing[index]->name = "empty";
    Hashing[index]->index = -1;

      cout << name << " has been removed from the hashtable" << endl;
  }
  //First linked list element matches name we want to delete and the linked list array
  // contains more than one element
  else if(Hashing[index]->name == name){
    PointertoDelete = Hashing[index];
    Hashing[index] = Hashing[index]->next;
    delete PointertoDelete;

    cout << name << " has been removed from the hashtable" << endl;
  }
  // bucket contains multiple items and first name is not a match
  else{
    Pointer1 = Hashing[index]->next;
    Pointer2 = Hashing[index];

    while(Pointer1 != nullptr){
      if(Pointer1->name == name){
      //Debugging statements
//      cout << "Setting Pointer to Delete: " << endl;
        PointertoDelete = Pointer1;
//      cout << "Setting Pointer1" << endl;
        Pointer1 = Pointer1->next;
//      cout << "Setting Pointer2" << endl;
        Pointer2->next = Pointer1;
        delete PointertoDelete;

        cout << name << " has been removed from the hashtable" << endl;
        return;
      }

//     cout << "Incrementing P1" << endl;
      Pointer2 = Pointer1;
//     cout << "Incrementing P2" << endl;
      Pointer1 = Pointer1->next;
    }
        cout << "Cannot delete " << name << ". Key was not found in hashtable" << endl;

  }
}
