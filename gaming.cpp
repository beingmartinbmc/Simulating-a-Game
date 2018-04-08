#include<cstring>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;

typedef struct Node
{
    char data[100];
    struct Node *next;
    struct Node *prev;
}*nodeptr,node;

void insertion(struct Node** start, char value[])
{
    if (*start == NULL)
    {
        nodeptr new_node = new Node;
        strcpy(new_node->data,value);
        new_node->next = new_node->prev = new_node;
        *start = new_node;
        return;
    }
    nodeptr last = (*start)->prev;
    nodeptr new_node = new Node;
    strcpy(new_node->data,value);
    new_node->next = *start;
    (*start)->prev = new_node;
    new_node->prev = last;
    last->next = new_node;
}
void deleteNode(struct Node **start, char key[])
{
    if (*start == NULL)
        return;
   struct Node *curr = *start, *prev_1 = NULL;
    while (strcmp(curr->data,key)!=0)
    {
        prev_1 = curr;
        curr = curr -> next;
    }
    if (curr -> next == *start && prev_1 == NULL)
    {
        (*start) = NULL;
        free(curr);
        return;
    }
    if (curr == *start)
    {
        prev_1 = (*start) -> prev;
        *start = (*start) -> next;
        prev_1 -> next = *start;
        (*start) -> prev = prev_1;
        free(curr);
    }
    else if (curr->next == *start)
    {
        prev_1 -> next = *start;
        (*start) -> prev = prev_1;
        free(curr);
    }
    else
    {
        struct Node *temp = curr -> next;
        prev_1 -> next = temp;
        temp -> prev = prev_1;
        free(curr);
    }
}
void display(struct Node* start)
{
    nodeptr temp = start;
    while (temp->next != start)
    {
        cout<<temp->data<<'\n';
        temp = temp->next;
    }
    cout<<temp->data<<'\n';
}
bool isPrime(int n)
{
    if (n <= 1)  return false;
    if (n <= 3)  return true;
    if (n%2 == 0 || n%3 == 0) return false;

    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
           return false;

    return true;
}
int main()
{
    cout<<"Enter number of names for the game"<<'\n';
    int n;
    cin>>n;
    string Array[n+1];
    cout<<"Enter the names"<<'\n';
    for(int c=0;c<n;c++)
        cin>>Array[c];
    string array1[n+1];
    string array2[n+1];
    int p=0,q=0;
    for(int i=0;i<n;i++){
        if(isPrime(i)||i==1){
            array1[p++]=Array[i];
        }
        else{
            array2[q++]=Array[i];
        }
    }
    nodeptr start = NULL;
    nodeptr start1= NULL;
    nodeptr start2= NULL;
    for(int a=0;a<n;a++){
        char *s2 = new char[Array[a].size()+1];
        strcpy(s2,Array[a].c_str());
        insertion(&start,s2);
    }
    for(int a=0;a<p+1;a++){
        char *s2 = new char[array1[a].size()+1];
        strcpy(s2,array1[a].c_str());
        insertion(&start1,s2);
    }
    for(int a=0;a<q+1;a++){
        char *s2 = new char[array2[a].size()+1];
        strcpy(s2,array2[a].c_str());
        insertion(&start2,s2);
    }
    printf("---------------------------------------------------------------------------\n");
    printf("Prime[%d]\n",p);
    display(start1);
    printf("NonPrime[%d]\n",q);
    display(start2);
    int m=floor(q/2)-1;
    printf("-----------------------------------------------------------------------------------\n\n");
    cout<<"Game Started:"<<'\n';
    for(int i=0;i<q-1;i++){
        string b=array2[m];
        cout<<"Starter is "<<b<<'\n';
        char *starter=new char[array1[m].size()+1];
        strcpy(starter,array1[m].c_str());
        deleteNode(&start1,starter);
        display(start1);
        printf("\n");
        m=(m+1)%q;
    }
    cout<<"Empty"<<endl;
    return 0;
}
