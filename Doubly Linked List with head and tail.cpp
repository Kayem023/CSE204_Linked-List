#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode * searchItem(int item);
int deleteLast();

struct listNode
{
    int item;
    struct listNode * next;
    struct listNode * prev;
};

struct listNode * list;

struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
    tail = 0;
}

int insertFirst(int item) //insert at the beginning
{
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;

    if(list==0) //inserting the first item
    {
        newNode->next = 0;
        newNode->prev = 0;
        list = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = list;
        list->prev = newNode;
        newNode->prev = 0;
        list = newNode;
    }
    return SUCCESS_VALUE ;
}



int deleteAfter(int item)
{
    struct listNode *temp;
    struct listNode *temp2;
    temp=searchItem(item);
    if(!temp)
    {
        return NULL_VALUE;
    }
    else{
        if(temp==tail){
            return NULL_VALUE;
        }
        else if(temp==tail->prev)
        {
            temp2=tail;
            temp->next=0;
            tail=temp;
            free(temp2);
            return SUCCESS_VALUE;
        }
        else{
            temp2=temp->next;
            temp->next=temp2->next;
            temp2->next->prev=temp;
            free(temp2);
            return SUCCESS_VALUE;
        }
    }
}
int deleteLast()
{
    struct listNode *temp;
    if(tail)
    {
        int m=tail->item;
        if(list==tail)
        {
            free(list);
            list=0;
            tail=0;
        }else{
            temp=tail;
            temp->prev->next=0;
            tail=temp->prev;
            free(temp);
        }
        return m;
    }
    return NULL_VALUE;
}


struct listNode * searchItem(int item)
{
    struct listNode * temp ;
    temp = list ; //start at the beginning
    while (temp != 0)
    {
        if (temp->item == item) return temp ;
        temp = temp->next ; //move to next node
    }
    return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printListForward()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

void printListBackward()
{
    //will print the list backward starting from the tail position
    struct listNode* temp;
    temp=tail;
    while(temp!=0)
    {
        printf("%d<-",temp->item);
        temp=temp->prev;
    }
    printf("\n");

}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete last item. 3. Search item. \n");
        printf("4. Print forward. 5. Print backward. 6. exit.\n");
        printf("7. DeleteAfter.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertFirst(item);
        }
        else if(ch==2)
        {
            int item = deleteLast();
            if(item!=NULL_VALUE) printf("Deleted: %d\n", item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            printListForward();
        }
        else if(ch==5)
        {
            printListBackward();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==7)
        {
            int k;
            scanf("%d",&k);
            deleteAfter(k);
        }
    }

}
