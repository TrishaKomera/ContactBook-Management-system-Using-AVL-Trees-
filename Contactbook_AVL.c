#include <stdio.h>
/*BT21CSE051_DSPD_II_Using_AVL_Trees*/
#include <stdlib.h>
#include<string.h>
//Assumtions: Name sorting is done assuming that all the charecters are in the either upper case or lower case.
typedef enum {FAILURE,SUCCESS}status_code;//enum for getting status
typedef enum {PERSONAL,PROFESSIONAL}contact_type;//for type in the contact_list
typedef struct calldetails_node
{
    struct calldetails_node* next;
    struct calldetails_node* prev;
    char date[9];
    int duration;
}calldetails;
//creating a history node
typedef struct personal_node
{
    struct personal_node* right;//right child
    struct personal_node* left;//left child
    char name[20];
    long long int phonenumber;
    char email_id[50];
    contact_type type;
    calldetails* history;
    int height;
}personal;//personal node

typedef struct professional_node
{
    struct professional_node* right;//right child
    struct professional_node* left;//left child
    char name[20];
    char email_id[50];
    long long int phonenumber;
    char company_name[50];
    long long int company_phonenumber;
    char address[100];
    contact_type type;
    calldetails* history;
    int height;
}professional;//professional node

typedef struct contact_list_tag
{
    personal* personal_list;
    professional* professional_list;
}contact_list;//contact book contains personal and professional list

void initialize_contact_list(contact_list* tptr)
{
    tptr->personal_list=NULL;
    tptr->professional_list=NULL;
}//Initializing the contact list to NULL for both personal and professional as they are not having any info stored in them

int max(int a,int b)
{
    int retval=a>b?a:b;
    return retval;
}//max of 2 integers

int personal_list_height(personal *tptr)
{
    int height=0;
    if(tptr==NULL)
    {
        height=0;
    }
    else
    {
        height=1+max(personal_list_height(tptr->left),personal_list_height(tptr->right));
    }
    return height;
}//Personal node height in recursion

int professional_list_height(professional *tptr)
{
    int height=0;
    if(tptr==NULL)
    {
        height=0;
    }
    else
    {
        height=1+max(professional_list_height(tptr->left),professional_list_height(tptr->right));
    }
    return height;
}//professional node height in recursion

int personal_balance_factor(personal *tptr)
{
    int retval=0;
    if(tptr==NULL)
    {
        retval=0;
    }
    else
    {
        retval=personal_list_height(tptr->left)-personal_list_height(tptr->right);
    }
    return retval;
}//Personal node balance factor in recursion-->checks for a node whether its balanced or not

int professional_balance_factor(professional *tptr)
{
    int retval=0;
    if(tptr==NULL)
    {
        retval=0;
    }
    else
    {
        retval=professional_list_height(tptr->left)-professional_list_height(tptr->right);
    }
    return retval;
}//Professional node balance factor in recursion-->checks for a node whether its balanced or not

status_code insert_contact_history(calldetails **history_list)
{
    calldetails *new_call_node=(calldetails*)malloc(sizeof(calldetails));
    calldetails *ptr=*history_list;
    status_code status=SUCCESS;
    if(new_call_node==NULL)
    {
        status==FAILURE;
    }
    else
    { 
        printf("\nEnter the date of the call: ");
        scanf("%s",new_call_node->date);
        printf("\nEnter the duration of the call in minutes: ");
        scanf("%d",&new_call_node->duration);
        if(ptr==NULL)
        {
            *history_list=new_call_node;
            new_call_node->next=NULL;
            new_call_node->prev=NULL;
        }
        else
        {
            while(ptr->next!=NULL)
            {
                ptr=ptr->next;
            }
            ptr->next=new_call_node;
            new_call_node->prev=ptr;
            new_call_node->next=NULL;
        }
    }
    return status;
}//Inserting the call details in the history list-->returns status to say malloc is successful or not

personal* personal_left_rotate(personal *x)
{
    personal *y = x->right;
    personal *t2 = y->left;
    y->left = x;
    x->right = t2;
    y->height = max(personal_list_height(y->left), personal_list_height(y->right)) + 1;
    x->height = max(personal_list_height(x->left), personal_list_height(x->right)) + 1;
    return y;
}//Left rotation for personal node

personal* personal_right_rotate(personal *y)
{
    personal *x = y->left;
    personal *t2 = x->right;
    x->right = y;
    y->left = t2;
    y->height = max(personal_list_height(y->left), personal_list_height(y->right)) + 1;
    x->height = max(personal_list_height(x->left), personal_list_height(x->right)) + 1;
    return x;
}//right rotation for personal node

professional* professional_left_rotate(professional *x)
{
    professional *y = x->right;
    professional *t2 = y->left;
    y->left = x;
    x->right = t2;
    y->height = max(professional_list_height(y->left), professional_list_height(y->right)) + 1;
    x->height = max(professional_list_height(x->left), professional_list_height(x->right)) + 1;
    return y;
}//professional node left rotation

professional* professional_right_rotate(professional *y)
{
    professional *x = y->left;
    professional *t2 = x->right;
    x->right = y;
    y->left = t2;
    y->height = max(professional_list_height(y->left),professional_list_height(y->right)) + 1;
    x->height = max(professional_list_height(x->left),professional_list_height(x->right)) + 1;
    return x;
}//professional node right rotation

personal* insert_personal_node(personal* tptr, personal* nptr)
{
    if(tptr==NULL)
    {
        tptr = nptr;
    }
    else if(nptr->phonenumber>tptr->phonenumber)
    {
        tptr->right=insert_personal_node(tptr->right,nptr);
    }
    else if(nptr->phonenumber<tptr->phonenumber)
    {
        tptr->left=insert_personal_node(tptr->left,nptr);
    }
    tptr->height=max(personal_list_height(tptr->left),personal_list_height(tptr->right))+1;
    int balance_factor=personal_balance_factor(tptr);
    if(balance_factor>1 && nptr->phonenumber<tptr->left->phonenumber)
    {
        tptr=personal_right_rotate(tptr);
    }
    else if(balance_factor>1 && nptr->phonenumber>tptr->left->phonenumber)
    {
        tptr->left=personal_left_rotate(tptr->left);
    }
    else if(balance_factor<-1 && nptr->phonenumber>tptr->right->phonenumber)
    {
        tptr=personal_left_rotate(tptr);
    }
    else if(balance_factor<-1 && nptr->phonenumber<tptr->right->phonenumber)
    {
        tptr->right=personal_right_rotate(tptr->right);
    }
    return tptr;
}//inserting personal node in the tree of personal list as a recursion-->returns rootnode finally after completing all recursion calls

professional* insert_professional_node(professional* tptr, professional* nptr)
{
    if(tptr==NULL)
    {
        tptr = nptr;
    }
    else if(nptr->phonenumber>tptr->phonenumber)
    {
        tptr->right=insert_professional_node(tptr->right,nptr);
    }
    else if(nptr->phonenumber<tptr->phonenumber)
    {
        tptr->left=insert_professional_node(tptr->left,nptr);
    }
    tptr->height=max(professional_list_height(tptr->left),professional_list_height(tptr->right))+1;
    int balance_factor=professional_balance_factor(tptr);
    if(balance_factor>1 && nptr->phonenumber<tptr->left->phonenumber)
    {
        tptr=professional_right_rotate(tptr);
    }
    else if(balance_factor>1 && nptr->phonenumber>tptr->left->phonenumber)
    {
        tptr->left=professional_left_rotate(tptr->left);
    }
    else if(balance_factor<-1 && nptr->phonenumber>tptr->right->phonenumber)
    {
        tptr=professional_left_rotate(tptr);
    }
    else if(balance_factor<-1 && nptr->phonenumber<tptr->right->phonenumber)
    {
        tptr->right=professional_right_rotate(tptr->right);
    }
    return tptr;
}//inserting professional node in the tree of professional list as a recursion-->returns rootnode finally after completing all recursion calls

status_code insert_new_contact(contact_list* ptr)
{
    contact_list *tptr=ptr;
    int choice;
    status_code status=SUCCESS,status2;
    printf("\nEnter 1 for personal contact and 2 for professional contact\nEnter your choice:");
    scanf("%d",&choice);
    while(choice!=1 && choice!=2)
    {
        printf("\nEnter correct input\nEnter 1 for personal contact and 2 for professional contact\nEnter your choice:");
        scanf("%d",&choice);
    }
    if(choice==1)
    {
        personal* new_node=(personal*)malloc(sizeof(personal));
        if(new_node==NULL)
        {
            status=FAILURE;
        }
        else
        {
            printf("\nEnter name:");
            scanf("%s",new_node->name);
            printf("\nEnter phone number:");
            scanf("%lld",&new_node->phonenumber);
            printf("\nEnter email id:");
            scanf("%s",new_node->email_id);
            new_node->type=PERSONAL;
            new_node->history=NULL;
            choice=1;
            new_node->height=1;
            while(choice==1)
            {
                printf("\nEnter 1 to add history and 2 to skip adding history\nEnter your choice:");
                scanf("%d",&choice);
                while(choice!=1 && choice!=2)
                {
                    printf("\nEnter correct input\nEnter 1 to add history and 2 to skip adding history\nEnter your choice:");
                    scanf("%d",&choice);
                }
                if(choice==1)
                {
                    status2=insert_contact_history(&new_node->history);
                    if(status2==FAILURE)
                    {
                        printf("Error in inserting history\n");
                    }
                }
            }
            new_node->left=NULL;
            new_node->right=NULL;
            if(tptr->personal_list==NULL)
            {
                tptr->personal_list=new_node;
            }
            else
            {
                tptr->personal_list=insert_personal_node(tptr->personal_list,new_node);
            }
        }
    }
    else
    {
        professional* new_node=(professional*)malloc(sizeof(professional));
        if(new_node==NULL)
        {
            status=FAILURE;
        }
        else
        {
            printf("\nEnter name:");
            scanf("%s",new_node->name);
            printf("\nEnter phone number:");
            scanf("%lld",&new_node->phonenumber);
            printf("\nEnter email id:");
            scanf("%s",new_node->email_id);
            printf("\nEnter company name:");
            scanf("%s",new_node->company_name);
            printf("\nEnter company phone number:");
            scanf("%lld",&new_node->company_phonenumber);
            printf("\nEnter address:");
            scanf("%s",new_node->address);
            new_node->type=PROFESSIONAL;
            new_node->history=NULL;
            choice=1;
            new_node->height=1;
            while(choice==1)
            {
                printf("\nEnter 1 to add history and 2 to skip adding history\nEnter your choice:");
                scanf("%d",&choice);
                while(choice!=1 && choice!=2)
                {
                    printf("\nEnter correct input\nEnter 1 to add history and 2 to skip adding history\nEnter your choice:");
                    scanf("%d",&choice);
                }
                if(choice==1)
                {
                    status2=insert_contact_history(&new_node->history);
                    if(status2==FAILURE)
                    {
                        printf("Error in inserting history\n");
                    }
                }
            }
            new_node->left=NULL;
            new_node->right=NULL;
            if(tptr->professional_list==NULL)
            {
                tptr->professional_list=new_node;
            }
            else
            {
                tptr->professional_list=insert_professional_node(tptr->professional_list,new_node);
            }
        }
    }
    ptr=tptr;
    return status;
}//taking input to create add node in particular list --> return status malloc failure or success

void display_history(calldetails *history_list)
{
    calldetails *ptr=history_list;
    while(ptr!=NULL)
    {
        printf("\nDate:%s\n",ptr->date);
        printf("Duration:%d\n\n",ptr->duration);
        ptr=ptr->next;
    }
}//display history list

void personal_node_display(personal *ptr)
{
    printf("\n");
    printf("Name:%s\n",ptr->name);
    printf("Phone number:%lld\n",ptr->phonenumber);
    printf("Email id:%s\n",ptr->email_id);
    printf("Type=Personal\n");
    display_history(ptr->history);
    printf("\n");
}//displaying personal node

void professional_node_display(professional *ptr)
{
    printf("\n");
    printf("Name:%s\n",ptr->name);
    printf("Phone number:%lld\n",ptr->phonenumber);
    printf("Email id:%s\n",ptr->email_id);
    printf("Company name:%s\n",ptr->company_name);
    printf("Company phone number:%lld\n",ptr->company_phonenumber);
    printf("Address:%s\n",ptr->address);
    printf("Type=Professional\n");
    display_history(ptr->history);
    printf("\n");
}//displaying professional node

void personal_list_in_order(personal* ptr)
{
    if(ptr!=NULL)
    {
        personal_list_in_order(ptr->left);
        personal_node_display(ptr);
        personal_list_in_order(ptr->right);
    }
}//displaying personal list in ascending order

void professional_list_in_order(professional* ptr)
{
    if(ptr!=NULL)
    {
        professional_list_in_order(ptr->left);
        professional_node_display(ptr);
        professional_list_in_order(ptr->right);
    }
}//diaplaying professional list in ascending order

void personal_list_reverse_in_order(personal* ptr)
{
    if(ptr!=NULL)
    {
        personal_list_reverse_in_order(ptr->right);
        personal_node_display(ptr);
        personal_list_reverse_in_order(ptr->left);
    }
}//displaying personal list in descending order

void professional_list_reverse_in_order(professional* ptr)
{
    if(ptr!=NULL)
    {
        professional_list_reverse_in_order(ptr->right);
        professional_node_display(ptr);
        professional_list_reverse_in_order(ptr->left);
    }
}//displaying professional list in descending order

personal* personal_list_search_based_on_phonenumber(personal* ptr,long long int number)
{
    personal* retval;
    if(ptr==NULL)
    {
        retval=NULL;
    }
    else if(ptr->phonenumber == number)
    {
        retval=ptr;
    }
    else if(ptr->phonenumber>number)
    {
        retval=personal_list_search_based_on_phonenumber(ptr->left,number);
    }
    else if(ptr->phonenumber<number)
    {
        retval=personal_list_search_based_on_phonenumber(ptr->right,number);
    }
    return retval;
}//searching personal list  on phonenumber in recursion-->returns NULL if not found

professional* professional_list_search_based_on_phonenumber(professional* ptr,long long int number)
{
    professional* retval;
    if(ptr==NULL)
    {
        retval=NULL;
    }
    else if(ptr->phonenumber == number)
    {
        retval=ptr;
    }
    else if(ptr->phonenumber>number)
    {
        retval=professional_list_search_based_on_phonenumber(ptr->left,number);
    }
    else if(ptr->phonenumber<number)
    {
        retval=professional_list_search_based_on_phonenumber(ptr->right,number);
    }
    return retval;
}//Professional search on phonenumber in recursion-->returns NULL if not found

void personal_list_search_based_on_name(personal* ptr, char* name, int* count)
{
    if(ptr!=NULL)
    {
        if(strcmp(ptr->name,name)==0)
        {
            (*count)++;
            personal_node_display(ptr);
        }
        personal_list_search_based_on_name(ptr->left,name,count);
        personal_list_search_based_on_name(ptr->right,name,count);
    }
}//personal search on name in recursion-->displays all the contacts matched and count will be there if 0 that means no match found

void professional_list_search_based_on_name(professional* ptr, char* name, int* count)
{
    if(ptr!=NULL)
    {
        if(strcmp(ptr->name,name)==0)
        {
            (*count)++;
            professional_node_display(ptr);
        }
        professional_list_search_based_on_name(ptr->left,name,count);
        professional_list_search_based_on_name(ptr->right,name,count);
    }
}//professional search on name in recursion-->displays all the contacts matched and count will be there if 0 that means no match found

int personal_contact_edit(personal* ptr,long long int number)
{
    int retval;
    personal* req_node=personal_list_search_based_on_phonenumber(ptr,number);
    if(req_node==NULL)
    {
        retval=0;
    }
    else
    {
        int choice;
        printf("\nEnter 1 to modify the name of the contact : ");
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("\nEnter the new name : ");
            scanf("%s",req_node->name);
        }
        printf("\nEnter 1 to modify email id : ");
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("\nEnter the new email id : ");
            scanf("%s",req_node->email_id);
        }
        retval=1;
    }
    return retval;
}//personal contact editing --> returns 1 if present and 0 if not found

int professional_contact_edit(professional* ptr,long long int number)
{
    int retval;
    professional* req_node=professional_list_search_based_on_phonenumber(ptr,number);
    if(req_node==NULL)
    {
        retval=0;
    }
    else
    {
        int choice;
        printf("\nEnter 1 to modify the name of the contact : ");
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("\nEnter the new name : ");
            scanf("%s",req_node->name);
        }
        printf("\nEnter 1 to modify email id : ");
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("\nEnter the new email id : ");
            scanf("%s",req_node->email_id);
        }
        printf("\nEnter 1 to modify company name : ");
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("\nEnter the new company name : ");
            scanf("%s",req_node->company_name);
        }
        printf("\nEnter 1 to modify company phone number : ");
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("\nEnter the new company phone number : ");
            scanf("%lld",&req_node->company_phonenumber);
        }
        printf("\nEnter 1 to modify address : ");
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("\nEnter the new address : ");
            scanf("%s",req_node->address);
        }
        retval=1;
    }
    return retval;
}//professional node editing -->returns 1 if present and 0 if not found

personal* personal_min_value_node(personal *ptr)
{
    personal* retval=ptr;
    while(retval->left!=NULL)
    {
        retval=retval->left;
    }
    return retval;
}//to get the mininimum node based on key-->returns the node

professional* professional_min_value_node(professional *ptr)
{
    professional* retval=ptr;
    while(retval->left!=NULL)
    {
        retval=retval->left;
    }
    return retval;
}//to get the mininimum node based on key-->returns the node

personal* personal_delete_node(personal* tptr,long long int number)
{
    int flag=0;
    personal* retval,*temp;
    if(tptr==NULL)
    {
        retval=NULL;
        flag=1;
    }
    else if(tptr->phonenumber>number)
    {
        tptr->left=personal_delete_node(tptr->left,number);
    }
    else if(tptr->phonenumber<number)
    {
        tptr->right=personal_delete_node(tptr->right,number);
    }
    else
    {
       if(tptr->left == NULL)
       {
           temp=tptr->right;
           free(tptr);
           retval=temp;
           flag=1;
       }
       else if(tptr->right == NULL)
       {
           temp=tptr->left;
           free(tptr);
           retval=temp;
           flag=1;
       }
       else
       {
           temp=personal_min_value_node(tptr->right);
           tptr->phonenumber=temp->phonenumber;
           tptr->left=personal_delete_node(tptr->left,temp->phonenumber);
       }
    }
    if(tptr==NULL&&flag==0)
    {
        retval=tptr;
        flag=1;
    }
    if(flag==0)
    {
        tptr->height=max(personal_list_height(tptr->left),personal_list_height(tptr->right))+1;
        int balance_factor=personal_balance_factor(tptr);
        if((balance_factor==2)&&(personal_balance_factor(tptr->left)>=0))
        {
            retval=personal_right_rotate(tptr);
        }
        else if((balance_factor==2)&&(personal_balance_factor(tptr->left)==-1))
        {
            tptr->left=personal_left_rotate(tptr->left);
            retval=personal_right_rotate(tptr);
        }
        else if((balance_factor==-2)&&(personal_balance_factor(tptr->right)<=0))
        {
            retval=personal_left_rotate(tptr);
        }
        else if((balance_factor==-2)&&(personal_balance_factor(tptr->right)==1))
        {
            tptr->right=personal_right_rotate(tptr->right);
            retval=personal_left_rotate(tptr);
        }
        else
        {
            retval=tptr;
        }
    }
    return retval;
}//personal node delete on recursion -->returns the root after deletion if present

professional* professional_delete_node(professional* tptr,long long int number)
{
    int flag=0;
    professional* retval,*temp;
    if(tptr==NULL)
    {
        retval=NULL;
        flag=1;
    }
    else if(tptr->phonenumber>number)
    {
        tptr->left=professional_delete_node(tptr->left,number);
    }
    else if(tptr->phonenumber<number)
    {
        tptr->right=professional_delete_node(tptr->right,number);
    }
    else
    {
       if(tptr->left == NULL)
       {
           temp=tptr->right;
           free(tptr);
           retval=temp;
           flag=1;
       }
       else if(tptr->right == NULL)
       {
           temp=tptr->left;
           free(tptr);
           retval=temp;
           flag=1;
       }
       else
       {
           temp=professional_min_value_node(tptr->right);
           tptr->phonenumber=temp->phonenumber;
           tptr->left=professional_delete_node(tptr->left,temp->phonenumber);
       }
    }
    if(tptr==NULL&&flag==0)
    {
        retval=tptr;
        flag=1;
    }
    if(flag==0)
    {
        tptr->height=max(professional_list_height(tptr->left),professional_list_height(tptr->right))+1;
        int balance_factor=professional_balance_factor(tptr);
        if((balance_factor==2)&&(professional_balance_factor(tptr->left)>=0))
        {
            retval=professional_right_rotate(tptr);
        }
        else if((balance_factor==2)&&(professional_balance_factor(tptr->left)==-1))
        {
            tptr->left=professional_left_rotate(tptr->left);
            retval=professional_right_rotate(tptr);
        }
        else if((balance_factor==-2)&&(professional_balance_factor(tptr->right)<=0))
        {
            retval=professional_left_rotate(tptr);
        }
        else if((balance_factor==-2)&&(professional_balance_factor(tptr->right)==1))
        {
            tptr->right=professional_right_rotate(tptr->right);
            retval=professional_left_rotate(tptr);
        }
        else
        {
            retval=tptr;
        }
    }
    return retval;
}//Professional node delete on recursion -->returns the root after deletion if present

void personal_range_search(personal* ptr,long long int low_number,long long int high_number)
{
    if((ptr!=NULL)&&(ptr->phonenumber>=low_number)&&(ptr->phonenumber<=high_number))
    {
        personal_node_display(ptr);
    }
    if((ptr!=NULL))
    {
        if(ptr->right!=NULL)
        {
            personal_range_search(ptr->right,low_number,high_number);
        }
        if(ptr->left!=NULL)
        {
            personal_range_search(ptr->left,low_number,high_number);
        }
    }
}//personal range search on recursion -->displays contact if present in range

void professional_range_search(professional* ptr,long long int low_number,long long int high_number)
{
    if((ptr!=NULL)&&(ptr->phonenumber>=low_number)&&(ptr->phonenumber<=high_number))
    {
        professional_node_display(ptr);
    }
    if((ptr!=NULL))
    {
        if(ptr->right!=NULL)
        {
            professional_range_search(ptr->right,low_number,high_number);
        }
        if(ptr->left!=NULL)
        {
            professional_range_search(ptr->left,low_number,high_number);
        }
    }
}//professional range search on recursion -->displays contact if present in range

void free_contact_history(calldetails **history_list)
{
    calldetails *ptr=*history_list;
    calldetails *fptr;
    while(ptr!=NULL)
    {
        fptr=ptr;
        ptr=ptr->next;
        free(fptr);
    }
    *history_list=NULL;
}//free function for contact history as we allocated space from heap

void personal_free_tree(personal *ptr)
{
    if(ptr!=NULL)
    {
        if(ptr->right!=NULL)
        {
            personal_free_tree(ptr->right);
        }
        if(ptr->left!=NULL)
        {
            personal_free_tree(ptr->left);
        }
        free_contact_history(&(ptr->history));
        free(ptr);
    }
    ptr=NULL;
}//free function for personal tree as we allocated space from heap

void professional_free_tree(professional *ptr)
{
    if(ptr!=NULL)
    {
        if(ptr->right!=NULL)
        {
            professional_free_tree(ptr->right);
        }
        if(ptr->left!=NULL)
        {
            professional_free_tree(ptr->left);
        }
        free_contact_history(&(ptr->history));
        free(ptr);
    }
    ptr=NULL;
}//free function for professional tree as we allocated space from heap

void free_total_trees(contact_list* ptr)
{
    personal* per_ptr=ptr->personal_list;
    professional* pro_ptr=ptr->professional_list;
    if(per_ptr!=NULL)
    {
        personal_free_tree(per_ptr);
    }
    if(pro_ptr!=NULL)
    {
        professional_free_tree(pro_ptr);
    }
    ptr->personal_list=NULL;
    ptr->professional_list=NULL;
}//free fn to free complete allocated space

personal* personal_insert_based_on_name(personal* ptr, personal* new_node)
{
    if(ptr==NULL)
    {
        ptr=new_node;
    }
    else if((strcmp(new_node->name,ptr->name)<0)||((strcmp(new_node->name,ptr->name)==0)&&new_node->phonenumber<ptr->phonenumber))
    {
        ptr->left=personal_insert_based_on_name(ptr->left,new_node);
    }
    else if((strcmp(new_node->name,ptr->name)>0)||((strcmp(new_node->name,ptr->name)==0)&&new_node->phonenumber>ptr->phonenumber))
    {
        ptr->right=personal_insert_based_on_name(ptr->right,new_node);
    }
    ptr->height=max(personal_list_height(ptr->left),personal_list_height(ptr->right))+1;
    int balance_factor=personal_balance_factor(ptr);
    if(balance_factor>1 && strcmp(new_node->name,ptr->name)<0)
    {
        ptr=personal_right_rotate(ptr);
    }
    else if(balance_factor>1 && strcmp(new_node->name,ptr->name)==0 && new_node->phonenumber<ptr->phonenumber)
    {
        ptr=personal_right_rotate(ptr);
    }
    else if(balance_factor<-1 && strcmp(new_node->name,ptr->name)>0)
    {
        ptr=personal_left_rotate(ptr);
    }
    else if(balance_factor<-1 && strcmp(new_node->name,ptr->name)==0 && new_node->phonenumber>ptr->phonenumber)
    {
        ptr=personal_left_rotate(ptr);
    }
    else if(balance_factor>1 && strcmp(new_node->name,ptr->name)>0)
    {
        ptr->left=personal_left_rotate(ptr->left);
        ptr=personal_right_rotate(ptr);
    }
    else if(balance_factor>1 && strcmp(new_node->name,ptr->name)==0 && new_node->phonenumber>ptr->phonenumber)
    {
        ptr->left=personal_left_rotate(ptr->left);
        ptr=personal_right_rotate(ptr);
    }
    else if(balance_factor<-1 && strcmp(new_node->name,ptr->name)<0)
    {
        ptr->right=personal_right_rotate(ptr->right);
        ptr=personal_left_rotate(ptr);
    }
    else if(balance_factor<-1 && strcmp(new_node->name,ptr->name)==0 && new_node->phonenumber<ptr->phonenumber)
    {
        ptr->right=personal_right_rotate(ptr->right);
        ptr=personal_left_rotate(ptr);
    }
    return ptr;
}//personal inserting new node based on name

professional* professional_insert_based_on_name(professional* ptr,professional* new_node)
{
    if(ptr==NULL)
    {
        ptr=new_node;
    }
    else if((strcmp(new_node->name,ptr->name)<0)||((strcmp(new_node->name,ptr->name)==0)&&new_node->phonenumber<ptr->phonenumber))
    {
        ptr->left=professional_insert_based_on_name(ptr->left,new_node);
    }
    else if((strcmp(new_node->name,ptr->name)>0)||((strcmp(new_node->name,ptr->name)==0)&&new_node->phonenumber>ptr->phonenumber))
    {
        ptr->right=professional_insert_based_on_name(ptr->right,new_node);
    }
    ptr->height=max(professional_list_height(ptr->left),professional_list_height(ptr->right))+1;
    int balance_factor=professional_balance_factor(ptr);
    if(balance_factor>1 && strcmp(new_node->name,ptr->name)<0)
    {
        ptr=professional_right_rotate(ptr);
    }
    else if(balance_factor>1 && strcmp(new_node->name,ptr->name)==0 && new_node->phonenumber<ptr->phonenumber)
    {
        ptr=professional_right_rotate(ptr);
    }
    else if(balance_factor<-1 && strcmp(new_node->name,ptr->name)>0)
    {
        ptr=professional_left_rotate(ptr);
    }
    else if(balance_factor<-1 && strcmp(new_node->name,ptr->name)==0 && new_node->phonenumber>ptr->phonenumber)
    {
        ptr=professional_left_rotate(ptr);
    }
    else if(balance_factor>1 && strcmp(new_node->name,ptr->name)>0)
    {
        ptr->left=professional_left_rotate(ptr->left);
        ptr=professional_right_rotate(ptr);
    }
    else if(balance_factor>1 && strcmp(new_node->name,ptr->name)==0 && new_node->phonenumber>ptr->phonenumber)
    {
        ptr->left=professional_left_rotate(ptr->left);
        ptr=professional_right_rotate(ptr);
    }
    else if(balance_factor<-1 && strcmp(new_node->name,ptr->name)<0)
    {
        ptr->right=professional_right_rotate(ptr->right);
        ptr=professional_left_rotate(ptr);
    }
    else if(balance_factor<-1 && strcmp(new_node->name,ptr->name)==0 && new_node->phonenumber<ptr->phonenumber)
    {
        ptr->right=professional_right_rotate(ptr->right);
        ptr=professional_left_rotate(ptr);
    }
    return ptr;
}//professional inserting new node based on name

personal* personal_create_and_copy_with_name(personal* ptr,personal* retval)
{
    personal* new_node=(personal*)malloc(sizeof(personal));
    strcpy(new_node->name,ptr->name);
    new_node->phonenumber=ptr->phonenumber;
    strcpy(new_node->email_id,ptr->email_id);
    new_node->left=NULL;
    new_node->right=NULL;
    new_node->height=1;
    if(ptr->history!=NULL)
    {
        calldetails* new_historty_node=(calldetails*)malloc(sizeof(calldetails));
        new_historty_node->next=NULL;
        new_historty_node->duration=ptr->history->duration;
        strcpy(new_historty_node->date,ptr->history->date);
        new_node->history=new_historty_node;
        calldetails* history_ptr=ptr->history;
        history_ptr=history_ptr->next;
        while(history_ptr!=NULL)
        {
            calldetails* new_history_node=(calldetails*)malloc(sizeof(calldetails));
            new_history_node->next=NULL;
            new_history_node->duration=history_ptr->duration;
            strcpy(new_history_node->date,history_ptr->date);
            new_historty_node->next=new_history_node;
            new_historty_node=new_history_node;
            history_ptr=history_ptr->next;
        }
    }
    else
    {
        new_node->history=NULL;
    }
    retval=personal_insert_based_on_name(retval,new_node);
    return retval;
}//creating new personal node by copying details

professional* professional_create_and_copy_with_name(professional* ptr,professional* retval)
{
    professional* new_node=(professional*)malloc(sizeof(professional));
    strcpy(new_node->name,ptr->name);
    new_node->phonenumber=ptr->phonenumber;
    strcpy(new_node->email_id,ptr->email_id);
    new_node->left=NULL;
    new_node->right=NULL;
    new_node->height=1;
    if(ptr->history!=NULL)
    {
        calldetails* new_historty_node=(calldetails*)malloc(sizeof(calldetails));
        new_historty_node->next=NULL;
        new_historty_node->duration=ptr->history->duration;
        strcpy(new_historty_node->date,ptr->history->date);
        new_node->history=new_historty_node;
        calldetails* history_ptr=ptr->history;
        history_ptr=history_ptr->next;
        while(history_ptr!=NULL)
        {
            calldetails* new_history_node=(calldetails*)malloc(sizeof(calldetails));
            new_history_node->next=NULL;
            new_history_node->duration=history_ptr->duration;
            strcpy(new_history_node->date,history_ptr->date);
            new_historty_node->next=new_history_node;
            new_historty_node=new_history_node;
            history_ptr=history_ptr->next;
        }
    }
    else
    {
        new_node->history=NULL;
    }
    retval=professional_insert_based_on_name(retval,new_node);
    return retval;
}//creating new Professional node by copying details

personal* create_personal_new_tree_based_on_name(personal* tptr,personal* retval)
{
    if(tptr!=NULL)
    {
        retval=personal_create_and_copy_with_name(tptr,retval);
        retval=create_personal_new_tree_based_on_name(tptr->left,retval);
        retval=create_personal_new_tree_based_on_name(tptr->right,retval);
    }
    return retval;
}//creating new tree based on name sort

professional* create_professional_new_tree_based_on_name(professional* tptr,professional* retval)
{
    if(tptr!=NULL)
    {
        retval=professional_create_and_copy_with_name(tptr,retval);
        retval=create_professional_new_tree_based_on_name(tptr->left,retval);
        retval=create_professional_new_tree_based_on_name(tptr->right,retval);
    }
    return retval;
}// creating new tree based on name sort

int main()
{
    contact_list contacts;
    initialize_contact_list(&contacts);
    int select,flag=0;
    long long int number;
    while(flag==0)
    {
        printf("\nEnter 1 to insert a new contact.\nEnter 2 to edit a contact\nEnter 3 to delete a contact\nEnter 4 to search for a contact\nEnter 5 to sort the contacts based on number\nEnter 6 to display contacts\nEnter 7 to do range search\nEnter 8 to sort based on names\nEnter 0 to exit\nEnter your choice:");
        scanf("%d",&select);
        if(select==1)
        {
            status_code sc=insert_new_contact(&contacts);
            if(sc==SUCCESS)
            {
                printf("Contact inserted successfully\n");
            }
            else
            {
                printf("Malloc failed so contact could not be inserted\n");
            }
        }
        else if(select==2)
        {
            printf("\nEnter the phone number to edit the contact : ");
            scanf("%lld",&number);
            printf("\nEnter 1 to edit the contact from personal contacts\nEnter 2 to edit the contact from professional contacts\nEnter your choice:");
            int choice;
            scanf("%d",&choice);
            while(choice!=1&&choice!=2)
            {
                printf("\nEnter 1 to edit the contact from personal contacts\nEnter 2 to edit the contact from professional contacts\nEnter your choice:");
                scanf("%d",&choice);
            }
            if(choice==1)
            {
                int choice=personal_contact_edit(contacts.personal_list,number);
                if(choice==1)
                {
                    printf("Contact edited in personal list successfully\n");
                }
                else
                {
                    printf("Contact not found in the personal contacts\n");
                    printf("Contact could not be edited\n");
                }
            }
            else
            {
                int choice=professional_contact_edit(contacts.professional_list,number);
                if(choice==1)
                {
                    printf("Contact edited in professional list successfully\n");
                }
                else
                {
                    printf("Contact not found in the professional contacts\n");
                    printf("Contact could not be edited\n");
                }
            }
        }
        else if(select==3)
        {
            printf("\nEnter the phone number to delete the contact : ");
            scanf("%lld",&number);
            int choice;
            printf("\nEnter 1 to check from personal contact list\nEnter 2 to check from professional contact list\nEnter your choice:");
            scanf("%d",&choice);
            while(choice!=1&&choice!=2)
            {
                printf("\nEnter the correct input\nEnter 1 to check from personal contact list\nEnter 2 to check from professional contact list\nEnter your choice:");
                scanf("%d",&choice);
            }
            if(choice==1)
            {
                contacts.personal_list=personal_delete_node(contacts.personal_list,number);
                printf("If contact present then contact deleted from personal list successfully\n");
            }
            else
            {
                contacts.professional_list=professional_delete_node(contacts.professional_list,number);
                printf("If contact present then contact deleted from professional list successfully\n");
            }
        }
        else if(select==4)
        {
            int choice;
            printf("\nEnter 1 to check from personal contact list\nEnter 2 to check from professional contact list\nEnter your choice:");
            scanf("%d",&choice);
            while(choice!=1&&choice!=2)
            {
                printf("\nEnter the correct input\nEnter 1 to check from personal contact list\nEnter 2 to check from professional contact list\nEnter your choice:");
                scanf("%d",&choice);
            }
            if(choice==1)
            {
                if(contacts.personal_list!=NULL)
                {
                    printf("\nEnter 1 to check based on number\nEnter 2 to check based on name\nEnter your choice:");
                    scanf("%d",&choice);
                    while(choice!=1&&choice!=2)
                    {
                        printf("\nEnter the correct input\nEnter 1 to check based on number\nEnter 2 to check based on name\nEnter your choice:");
                        scanf("%d",&choice);
                    }
                    if(choice==1)
                    {
                        printf("\nEnter the phone number to search the contact : ");
                        scanf("%lld",&number);
                        personal * temp;
                        temp=personal_list_search_based_on_phonenumber(contacts.personal_list,number);
                        if(temp==NULL)
                        {
                            printf("Contact doesn't exist in personal contact list\n");
                        }
                        else
                        {
                            personal_node_display(temp);
                            printf("Contact found in personal contact list\n");
                        }
                    }
                    else
                    {
                        char name[100];
                        printf("\nEnter the name to search the contact : ");
                        scanf("%s",name);
                        int count=0;
                        personal_list_search_based_on_name(contacts.personal_list,name,&count);
                        if(count==0)
                        {
                            printf("Contact doesn't exist in personal contact list\n");
                        }
                        else
                        {
                            printf("Contact found in personal contact list\n");
                        }
                    }
                }
                else
                {
                    printf("\nPersonal contact list is empty\n");
                }
            }
            else
            {
                if(contacts.professional_list!=NULL)
                {
                    printf("\nEnter 1 to check based on number\nEnter 2 to check based on name\nEnter your choice:");
                    scanf("%d",&choice);
                    while(choice!=1&&choice!=2)
                    {
                        printf("\nEnter the correct input\nEnter 1 to check based on number\nEnter 2 to check based on name\nEnter your choice:");
                        scanf("%d",&choice);
                    }
                    if(choice==1)
                    {
                        printf("\nEnter the phone number to search the contact : ");
                        scanf("%lld",&number);
                        professional * temp;
                        temp=professional_list_search_based_on_phonenumber(contacts.professional_list,number);
                        if(temp==NULL)
                        {
                            printf("Contact doesn't exist in professional contact list\n");
                        }
                        else
                        {
                            professional_node_display(temp);
                            printf("Contact found in professional contact list\n");
                        }
                    }
                    else
                    {
                        char name[100];
                        printf("\nEnter the name to search the contact : ");
                        scanf("%s",name);
                        int count=0;
                        professional_list_search_based_on_name(contacts.professional_list,name,&count);
                        if(count==0)
                        {
                            printf("Contact doesn't exist in professional contact list\n");
                        }
                        else
                        {
                            printf("Contact found in professional contact list\n");
                        }
                    }
                }
            }
        }
        else if(select==5)
        {
            contact_list sort;
            initialize_contact_list(&sort);
            int choice=1;
            while(choice!=2)
            {
                printf("\nEnter 1 to add contact\nEnter 2 to stop adding contacts\nEnter your choice:");
                scanf("%d",&choice);
                if(choice==1)
                {
                    status_code sc=insert_new_contact(&sort);
                    if(sc==SUCCESS)
                    {
                        printf("Contact inserted successfully\n");
                    }
                    else
                    {
                        printf("Malloc failed so contact could not be inserted\n");
                    }
                }
                else if(select==2)
                {
                    printf("Stopped adding contacts\n");
                }
                else
                {
                    printf("\nEnter the correct input\n");
                }
            }
            printf("\nEnter 1 to sort in ascending order\nEnter 2 to sort in descending order\nEnter your choice:");
            scanf("%d",&choice);
            while(choice!=1&&choice!=2)
            {
                printf("\nEnter the correct input\nEnter 1 to sort in ascending order\nEnter 2 to sort in descending order\nEnter your choice:");
                scanf("%d",&choice);
            }
            if(choice==1)
            {
                printf("\nEnter 1 to display personal contact list\nEnter 2 to display professional contact list\nEnter 3 to display both\nEnter your choice:");
                scanf("%d",&select);
                while(select!=1&&select!=2&&select!=3)
                {
                    printf("\nEnter the correct input\nEnter 1 to display personal contact list\nEnter 2 to display professional contact list\nEnter your choice:");
                    scanf("%d",&select);
                }
                if(select==1)
                {
                    printf("The contacts in personal list are:\n");
                    personal_list_in_order(sort.personal_list);
                }
                else if(select==2)
                {
                    printf("The contacts in professional list are:\n");
                    professional_list_in_order(sort.professional_list);
                }
                else
                {
                    printf("The contacts in both lists are:\n");
                    personal_list_in_order(sort.personal_list);
                    professional_list_in_order(sort.professional_list);
                }
            }
            else
            {
                printf("\nEnter 1 to display personal contact list\nEnter 2 to display professional contact list\nEnter 3 to display both\nEnter your choice:");
                scanf("%d",&select);
                while(select!=1&&select!=2&&select!=3)
                {
                    printf("\nEnter the correct input\nEnter 1 to display personal contact list\nEnter 2 to display professional contact list\nEnter your choice:");
                    scanf("%d",&select);
                }
                if(select==1)
                {
                    printf("The contacts in personal list are:\n");
                    personal_list_reverse_in_order(sort.personal_list);
                }
                else if(select==2)
                {
                    printf("The contacts in professional list are:\n");
                    professional_list_reverse_in_order(sort.professional_list);
                }
                else
                {
                    printf("The contacts in both lists are:\n");
                    personal_list_reverse_in_order(sort.personal_list);
                    professional_list_reverse_in_order(sort.professional_list);
                }
            }
            free_total_trees(&sort);
        }
        else if(select==6)
        {
            printf("\nEnter 1 to display personal contact list\nEnter 2 to display professional contact list\nEnter 3 to display both\nEnter your choice:");
            scanf("%d",&select);
            while(select!=1&&select!=2&&select!=3)
            {
                printf("\nEnter the correct input\nEnter 1 to display personal contact list\nEnter 2 to display professional contact list\nEnter your choice:");
                scanf("%d",&select);
            }
            if(select==1)
            {
                if(contacts.personal_list==NULL)
                {
                    printf("\nPersonal contact list is empty\n");
                }
                else
                {
                    printf("The contacts in personal list are:\n");
                    personal_list_in_order(contacts.personal_list);
                }
            }
            else if(select==2)
            {
                if(contacts.professional_list==NULL)
                {
                    printf("\nProfessional contact list is empty\n");
                }
                else
                {
                    printf("The contacts in professional list are:\n");
                    professional_list_in_order(contacts.professional_list);
                }
            }
            else
            {
                if(contacts.personal_list==NULL)
                {
                    printf("\nPersonal contact list is empty\n");
                }
                else
                {
                    printf("The contacts in personal list are:\n");
                    personal_list_in_order(contacts.personal_list);
                }
                if(contacts.professional_list==NULL)
                {
                    printf("\nProfessional contact list is empty\n");
                }
                else
                {
                    printf("The contacts in professional list are:\n");
                    professional_list_in_order(contacts.professional_list);
                }
            }
        }
        else if(select==7)
        {
            long long int low_number,high_number;
            printf("\nEnter the low number:");
            scanf("%lld",&low_number);
            printf("\nEnter the high number:");
            scanf("%lld",&high_number);
            printf("The contacts in personal list in the range are:\n");
            personal_range_search(contacts.personal_list,low_number,high_number);
            printf("The contacts in professional list in the range are:\n");
            professional_range_search(contacts.professional_list,low_number,high_number);
        }
        else if(select==8)
        {
            contact_list sortname;
            initialize_contact_list(&sortname);
            sortname.personal_list=create_personal_new_tree_based_on_name(contacts.personal_list,sortname.personal_list);
            sortname.professional_list=create_professional_new_tree_based_on_name(contacts.professional_list,sortname.professional_list);
            if(sortname.personal_list==NULL)
            {
                printf("\nPersonal contact list is empty\n");
            }
            else
            {
                printf("The personal contact list sorted based on name is:\n");
                personal_list_in_order(sortname.personal_list);
            }
            if(sortname.professional_list==NULL)
            {
                printf("\nProfessional contact list is empty\n");
            }
            else
            {
                printf("The professional contact list sorted based on name is:\n");
                professional_list_in_order(sortname.professional_list);
            }
            free_total_trees(&sortname);
        }
        else if(select==0)
        {
            free_total_trees(&contacts);
            printf("Program Exited\n");
            flag=1;
        }
        else
        {
            printf("\nEnter the correct input\n");
        }
        printf("\n\n");
    }
}
