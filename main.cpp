// #include <bits/stdc++.h>
#include <iostream>
#include <vector>


using namespace std;

class Record{
public:
    int data;
    int pageID;
    int recordID;
    
    Record(int pid, int rid, int dataValue){
        pageID = pid;
        recordID = rid;
        data = dataValue;
    }
};


class Page{
public:
    Page *prev;
    Page *next;
    int numRecords;
    int freeSpace;
    int pageID;
    vector <Record *> directory;
    vector <int> data;
    
    Page(int emptySpace, int pageID){
        freeSpace = emptySpace;
        prev = nullptr;
        next = nullptr;
        numRecords = 0;
    }
};

class HeapFile{
private:
    int pageSize;
    int numPage;
    Page *head;
    
public:
    HeapFile(int input){
        pageSize = input;
        head = nullptr;
        numPage = 0;
    }
    
    void insert(int recordSize, int key){
        if(recordSize < 0){
            return;
        }
        
        // File is empty
        if(head == nullptr){
            int pid = numPage;
            Page *p = new Page(pageSize - 16, pid);
            head = p;
            numPage++;
            int rid = p->numRecords;
            (p -> numRecords)++;
            
            Record *r = new Record(pid, rid, key);
            p -> directory.push_back(r);
            p -> data.push_back(key);
            p -> freeSpace -= (recordSize + 4);
            return;
        }
        
        // File is not empty
        
        // Finding the correct Page
        Page *t = head;
        Page *l = head;
        while (t != NULL)
        {
            // Page has space for the record
            if (t->freeSpace >= (recordSize + 4))
            {
                int pid = t -> pageID;
                int rid = t -> numRecords;
                (t -> numRecords)++;
                
                Record *r = new Record(pid, rid, key);
                t -> directory.push_back(r);
                t -> data.push_back(key);
                t -> freeSpace -= (recordSize + 4);
                break;
            }

            // Page does not have enough space
            l = t;
            t = t->next;
        }
        
        // New page is required
        
        if (t == NULL){
            int pid = numPage;
            Page *p = new Page(pageSize - 16, pid);
            p->prev = l;
            l->next = p;
            numPage++;
            int rid = p->numRecords;
            (p -> numRecords)++;
            
            Record *r = new Record(pid, rid, key);
            p -> directory.push_back(r);
            p -> data.push_back(key);
            p -> freeSpace -= (recordSize + 4);
            return;
        }

        return;

    }
    
    void search(int key){
        Page *t = head;
        int page = 0;
        Record *ans = new Record(-1, -1, key);
        
        while (t != NULL)
        {
            int k = (int)t->data.size();
            for (int i = 0; i < k; i++)
            {
                if (t->data[i] == key)
                {
                    ans = t->directory[i];
                    break;
                }
            }
            page++;
            t = t->next;
        }
        
        cout << ans->pageID << " " << ans->recordID << endl;
        
    }
    
    void status(){
        cout << numPage;
        
        Page *t = head;
        while (t != NULL)
        {
            cout << " " << t->numRecords;

            t = t->next;
        }
        cout << endl;

        return;
    }
};


int main() {
    int totalPageSize;
    cin >> totalPageSize;
    
    HeapFile instance(totalPageSize);
    
    int operation;
    
    while(cin >> operation){
        switch (operation) {
            case 1:{
                int s, key;
                cin >> s >> key;
                instance.insert(s, key);
                break;
            }
                
            case 2:{
                instance.status();
                break;
            }
                
            case 3:{
                int key;
                cin >> key;
                instance.search(key);
                break;
            }
                
            case 4:
                return 0;
                
            default:
                break;
        }
        
        
        
    }
    
    return 0;
}
