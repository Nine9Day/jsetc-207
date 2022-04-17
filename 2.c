#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>

struct address_book
{
    char name[20];
    char sex[5];
    int phone[50];
    struct address_book* next;
};
typedef struct address_book Address;
typedef Address* Alink;


void display_link(Alink);


void menu(Alink head)
{
    printf("***********************************************************\n");
    printf("***********************************************************\n");
    printf("******     1.Add one             2.Add multiple       *****\n");
    printf("******     3.delete              4.amend              *****\n");
    printf("******     5.search              6.exit               *****\n");
    printf("******         please do some operation:              *****\n");
    printf("***********************************************************\n");
    printf("***********************************************************\n");
}

void create_link(Alink* head)
{
    *head=(Alink)malloc(sizeof(Address));
    (*head)->next=NULL;
}




void create_newnode(Alink* newnode)
{
    *newnode=(Alink)malloc(sizeof(Address));
    printf("please input name:\n");
    scanf("%s",(*newnode)->name);
    printf("please input sex:\n");
    scanf("%s",(*newnode)->sex);
    printf("please input phone number:\n");
    scanf("%ls",(*newnode)->phone);
    
}




void insert_tail(Alink head,Alink newnode)
{
    Alink p=NULL;
    p=head;
    while(p->next!=NULL)
    {
        p=p->next;
    }
    p->next=newnode;
    newnode->next=NULL;
}




void delete_node(Alink head,int loc)
{
    int i;
    Alink p=NULL;
    Alink q=NULL;
    p=q=head;
    if(NULL==head->next)
    {
        printf("no such node");
    }
    for(i=0;i<loc;i++)
    {
        q=p;
        p=p->next;
    }
    if(p==NULL)
    {
        printf("no such node\n");
    }
    q->next=p->next;
    free(p);
    p = NULL;
}




void display_link(Alink head)
{
    Alink p=NULL;
    // Alink q=NULL;
    // q=head;
    p=head->next;
    // if(q->next==NULL)
    // {
    //     printf("no imformation\n");
    // }
    while(p!=NULL)
    {
        printf("===========================================================\n");
        printf("name:%s    ",p->name);
        printf("sex:%s     ",p->sex);
        printf("phone number:%ls\n",p->phone);
        printf("===========================================================\n");
        p=p->next;
    }
}





void clear_node(Alink* head)
{
    Alink p=NULL,q=NULL;
    p=(*head)->next;
    q=*head;
    while(p!=NULL)
    {
        p=p->next;
        q=q->next;
        free(q);
        q=*head;
        q->next=p;
    }
}
void release_link(Alink* head)
{
    clear_node(head);
    free(*head);
}




struct address_book search_node(Alink head)
{
    int c;
    char name[50];
    char sex[20];
    Alink p=NULL;
    p=head;
    printf("1.According to the name lookup\n");
    printf("2.According to the sex lookup\n");
    printf("Please select 1or2: ");
    scanf("%d",&c);
    if(c==1)
    {
        printf("Please enter the name you want to find:");
        scanf("%s",name);
        while(p!=NULL)
        {
            if(strcmp(p->name,name)==0)
            {
                printf("name:%s    ",name);
                printf("sex:%s     ",p->sex);
                printf("phone number:%ls\n",p->phone);
                return *p;
            }
            p=p->next;
        }
        if(p==NULL)
        {
            printf("no such name\n");
        }
    }


    if(c==2)
    {
        printf("Please enter the sex you want to find:");
        scanf("%s",sex);
        while(p!=NULL&&p->sex!=sex)
        {
            if(strcmp(p->sex,sex)==0)
            {
                printf("name:%s    ",p->name);
                printf("sex:%s     ",sex);
                printf("phone number:%ls\n",p->phone);
                return *p;
            }
            p=p->next;
        }
        if(p==NULL)
        {
            printf("no such name\n");
        }

    }
}







void amend_node(Alink head,int loc)
{
    int b;
    char ch;

    end:
    printf("please input amend loc:");
    scanf("%d",&loc);
    Alink p=NULL;
    p=head;
    for(int i=0;i<loc;i++)
    {
        p=p->next;
    }
    printf("Please enter the modification content:1.name,2.sex,3.phone number:\n");
    scanf("%d",&b);
    switch (b)
    {
    case 1:
        printf("Please enter the name you want to replace:\n");
        scanf("%s",p->name);
        display_link(head);
        // printf("Return to menu:'Y'or'N'\n");
        // scanf("%c",&ch);

        // if(ch=='Y')
        // {
        //     goto end;
        // }
        break;
    case 2:
        printf("Please enter the sex you want to replace:\n");
        scanf("%s",p->sex);
        display_link(head);
        // printf("Return to menu:'Y'or'N'\n");
        // scanf("%c",&ch);
        // if(ch=='Y')
        // {
        //     goto end;
        // }
        break;
    case 3:
        printf("Please enter the phone number you want to replace:\n");
        scanf("%ls",p->phone);
        display_link(head);
        // printf("Return to menu:'Y'or'N'\n");
        // scanf("%c",&ch);
        // if(ch=='Y')
        // {
        //     goto end;
        // }
        break;
    default:printf("error\n");
        break;
    }
}


// void read_data(Alink head, Alink newnode,char* str)
// {
//     Alink p = NULL;
//     p = head;
//     int fd;
//     int fr;
//     if(fd = open(str ,O_RDWR | O_CREAT , 0655)<0);
//     {
//         perror("open fail");
//         exit(1);
//     }
//     while(p->next !=NULL)
//     {
//         if((fr = read(fd,p,sizeof(Address)))<0);
//         {
//             perror("read error!!");
//             exit(1);
//         }
//     }
// }
// void write_data(Alink head, Alink newnode,char* str)
// {
//     Alink p = NULL;
//     p = head;
//     int fd;
//     int fw;
//     if(fd = open(str ,O_WRONLY | O_CREAT, 0655)<0);
//     {
//         perror("open fail");
//         exit(1);
//     }
//     while(p->next!=NULL)
//     {
//         if((fw = write(fd,p,sizeof(Address)))<0);
//         {
//             perror("write error");
//             exit(1);
//         }

//     }
// }

void write_file(Alink head, char *str)
{
    int fd;
    fd = open(str, O_RDWR | O_CREAT, 0655);
    if(fd == -1)
    {
        perror("open error!");
        exit(-1);
    }

    Alink p = head->next;
    while(p != NULL)
    {
        write(fd, p, sizeof(Address));

        p = p->next;
    }

    close(fd);

}

void read_file(Alink head, char *str)
{
    int fd;
    fd = open(str, O_RDWR | O_CREAT, 0655);

    while(1)
    {
        Alink new_node = (Alink)malloc(sizeof(Address));

        int n = read(fd, new_node, sizeof(Address));
        if(n == 0)
        {
            free(new_node);
            new_node = NULL;
            break;
        }

        new_node->next = head->next;
        head->next = new_node;
    }
}

// void display(Alink head)
// {
//     Alink p = head->next;
//     while(p != NULL)
//     {
//         printf("%s")

//         p = p->next;
//     }
// }

int main(int argc,char** argv)
{
    if(argc != 2)
    {
        printf("Please input file name:\n");
        return 0;
    }
    int a;
    int j;
    int loc;
    int q;
    int n;
    Alink head=NULL;
    Alink newnode=NULL;
    create_link(&head);
    read_file(head, argv[1]);
    do
    {
        menu(head);
        display_link(head);
        printf("Perform the following operations:");
        scanf("%d",&a);
        switch (a)
        {
            case 1://增加一个新结点
            create_newnode(&newnode);
            insert_tail(head,newnode);
            // read_data(head,newnode, argv[1]);
            // write_data(head,newnode, argv[1]);
            break;


            case 2://增加多个新结点
            printf("add the number of:");
            scanf("%d",&j);
            for(int i=0;i<j;i++)
            {
                create_newnode(&newnode);
                insert_tail(head,newnode);
            }
            // display_link(head);
            break;


            case 3://删除
            // display_link(head);
            printf("please input delete loc:");
            scanf("%d",&loc);
            delete_node(head,loc);
            // display_link(head);
            break;


            case 4://修改
            // display_link(head);
            amend_node(head,loc);
            // display_link(head);
            break;


            case 5://查找
            search_node(head);
            break;


            // case 6://显示列表
            // display_link(head);
            case 6:
                if(a==6)
            {
                goto end;
            }
            break;

            
            default:printf("error\n");
            break;
        }
    }while(1);
    end:
    write_file(head, argv[1]);
    clear_node(&head);
    release_link(&head);

    return 0;
}