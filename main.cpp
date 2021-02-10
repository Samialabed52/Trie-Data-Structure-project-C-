#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int ARRAY_SIZE = 127;

struct TrieNode
{
    bool end_word;
    char letter;
    TrieNode *children[ARRAY_SIZE];
    TrieNode()
    {
        end_word = false;
        for(int i {0}; i < ARRAY_SIZE; i++)
            children[i] = NULL;
    }
};

void insert(TrieNode *root, string key)
{
    TrieNode *point = root;
    for(size_t i {0}; i < key.size(); i++)
    {
        int val = key[i];
        if(point->children[val] == NULL)
        {
            point->children[val] = new TrieNode;
            point->children[val]->letter = key[i];
        }
        point = point->children[val];
    }
    point->end_word = true;
}

bool search(TrieNode *root, string key)
{
    TrieNode *point = root;
    for(size_t i {0}; i < key.size(); i++)
    {
        int val = key[i];
        if(point->children[val] == NULL)
        {
            return false;
            break;
        }
        point = point->children[val];
    }
    if(point->end_word == true)
        return true;
    else
        return false;
}

void autocomplete(TrieNode *root, string key)
{
    TrieNode *point = root;
    string check{};
    for(size_t i {0}; i < key.size(); i++)
    {
        int val = key[i];
        if(point->children[val] != NULL)
        {
            check += point->children[val]-> letter;
            point = point->children[val];
        }
    }
    if(point->end_word == true)
    {
        cout << check << endl;
    } 
    for(int i {0}; i < ARRAY_SIZE; i++)
    {
        if(point->children[i] != NULL)
        {
            string new_check = check + point->children[i]->letter;
            autocomplete(root, new_check);
        }
    }
}

void complete(TrieNode *root)
{
    TrieNode *point = root;
    string key;
    cout << "Please type search queries: " << endl;
    cin >> key;
    
    cout << "Your options are: " << endl;
    autocomplete(point, key);
}

int ender {0};

void autocorrect(TrieNode *root, string key)
{
    TrieNode *point = root;
    string check {};
    if(ender == 3)
    {
        ender == 0;
        return;
    }
    for(size_t i {0}; i < key.size(); i++)
    {
        int val = key[i];
        if(point->children[val] != NULL)
        {
            check += point->children[val]->letter;
            point = point->children[val];
        }
    }
    if(ender == 0 && point->end_word == true)
    {
        cout << check << endl;
        ender++;
    }
    for(int i {0}; i < ARRAY_SIZE; i++)
    {
        if(point->children[i] != NULL)
        {
            string new_check = check + point->children[i]->letter;
            if(search(root, new_check) == true)
            {
                if(ender != 3)
                {
                    cout << new_check << endl;
                    ender++;
                    autocorrect(root, new_check);
                }
            }
            else
            {
                if(ender != 3)
                    autocorrect(root, new_check);
            }
        }
    }
}

void corrector(TrieNode *root)
{
    TrieNode *point = root;
    string key;
    cout << "\nPlease type search queries: " << endl;
    cin >> key;
    
    if(search(point, key) == true)
        cout << "Good choice!" << endl;
    else
    {        
        cout << "Do you mean: " << endl;
        autocorrect(point, key);
        while(ender != 3)
        {
            string check{};
            for(size_t i {0}; i < key.size()/2; i++)
            {
                int val = key[i];
                if(point->children[val] != NULL)
                {
                    check += point->children[val]->letter;
                    point = point->children[val];
                }
            }
            autocorrect(root, check);
        }
    }
}

int main()
{
    TrieNode *root = new TrieNode();
    string line;
    ifstream Dictionary("Dictionary.txt");
    if(!Dictionary)
    {
        return 1;
    }
    while(getline(Dictionary, line))
    {
        insert(root, line);
    }
    Dictionary.close();    
    complete(root);
    corrector(root);    
    return 0;
}