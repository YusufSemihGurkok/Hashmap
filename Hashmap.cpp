#include <iostream>
const int tablesize = 10;
using namespace std;

struct TableEntry {
   int key, value;
   TableEntry *next;
   TableEntry(int k, int v) {
      key = k;
      value = v;
      next = NULL;
   }
};

class HashMapTable {
public:
   TableEntry **table;

   HashMapTable() {
      table = new TableEntry*[tablesize];
      for (int i = 0; i < tablesize; i++)
         table[i] = NULL;
   }

   int HashFunc(int key) {
      return key % tablesize;
   }

   void Insert(int k, int v) {
      int hash_v = HashFunc(k);
      TableEntry* prev = NULL;
      TableEntry* entry = table[hash_v];
      while (entry != NULL) {
         prev = entry;
         entry = entry->next;
      }
      if (entry == NULL) {
         entry = new TableEntry(k, v);
         if (prev == NULL) {
            table[hash_v] = entry;
         } else {
            prev->next = entry;
         }
      } else {
         entry->value = v;
      }
   }

   void Remove(int k) {
      int hash_v = HashFunc(k);
      TableEntry* entry = table[hash_v];
      TableEntry* prev = NULL;
      if (entry == NULL || entry->key != k) {
         cout << "No Element found at key " << k << endl;
         return;
      }
      while (entry->next != NULL) {
         prev = entry;
         entry = entry->next;
      }
      if (prev != NULL) {
         prev->next = entry->next;
      }
      delete entry;
      cout << "Element Deleted" << endl;
   }

   void SearchKey(int k) {
      int hash_v = HashFunc(k);
      bool flag = false;
      TableEntry* entry = table[hash_v];
      if (entry != NULL) {
         while (entry != NULL) {
            if (entry->key == k) {
               flag = true;
            }
            if (flag) {
               cout << "Element found at key " << k << ": ";
               cout << entry->value << endl;
            }
            entry = entry->next;
         }
      }
      if (!flag)
         cout << "No Element found at key " << k << endl;
   }

   ~HashMapTable() {
      delete[] table;
   }
};

int main() {
   HashMapTable hash;
   int k, v;
   int choice;
   while (true) {
      cout << "1. Insert element" << endl;
      cout << "2. Search element(enter key)" << endl;
      cout << "3. Delete element(enter key)" << endl;
      cout << "4. Exit" << endl;
      cout << "Enter your choice: ";
      cin >> choice;
      switch (choice) {
         case 1:
            cout << "Enter key: ";
            cin >> k;
            cout << "Enter value: ";
            cin >> v;
            hash.Insert(k, v);
            break;
         case 2:
            cout << "Enter key: ";
            cin >> k;
            hash.SearchKey(k);
            break;
         case 3:
            cout << "Enter key: ";
            cin >> k;
            hash.Remove(k);
            break;
         case 4:
            exit(0);
         default:
            cout << "\nEnter correct option\n";
      }
   }
   return 0;
}
