#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

struct Node
{
    char letter;
    Node *next;
};
bool Judge(char letter)
{
    return letter=='a'||letter=='e'||letter=='i'||letter=='o'||letter=='u';
}
Node *AddNode(Node *head, Node *p)
{
    if(head == NULL)
    {
        return p;
    }
    Node *current = head;
    while(current->next)
        current = current->next;
    current->next = p;
    p->next = head;
    return head;
}
void DeleteList(Node *head)
{
    while(head)
    {
        Node *current = head;
        head = head -> next;
        delete current;
    }
}
int main()
{
    //int n;
    //cin >> n;
    //while(n--)
    //{
        string word;
        int m;
        cin >> word >> m;
        Node *head = new Node;
        int num = 0;
        for(int i = 0; i < word.length(); i++)
        {
            if(Judge(word[i]))
            {
                Node *p = new Node;
                p->letter = word[i];
                head = AddNode(head, p);
                num++;
            }
        }
        while(m--)
            head = head->next;
        for(int i = 0; i < word.length(); i++)
        {
            if(!Judge(word[i]))
                cout << word[i];
            else
            {
                cout << head->letter;
                head = head->next;
            }
        }
        //DeleteList(head);
    //}
    return 0;
}