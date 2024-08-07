#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
unsigned char myarr[] = {
    0xcb,
    0x5a,
    0xff,
    0xff,
    0xff,
    0xff,
    0xbf,
    0xae,
    0x1c,
    0x24,
    0xde,
    0x03,
    0xdf,
    0x0b,
    0xdf,
    0x0b,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0xff,
    0x03,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0xff,
    0x03,
    0xff,
    0x03,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x1f,
    0x0c,
    0x3f,
    0x14,
    0x5f,
    0x14,
    0x5f,
    0x1c,
    0x7f,
    0x1c,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
    0x24,
    0x7f,
};

unsigned char myarr1[] = "kadgk";
unsigned char myarr2[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa};
// 定义一个结构体
// struct test1
// {
//     int num;
//     unsigned char arr[];
// };

// 定义一个结构体
struct test
{
    int num;
    unsigned char *arr;
    struct test *next;
};

// 遍历链表
void printfLink(struct test *head)
{
    struct test *p;
    p = head;
    while (p != NULL)
    {
        printf("数组个数 = %4d ----", p->num);
        for (int i = 0; i < p->num; i++)
        {
            printf("%02x ", p->arr[i]);
        }
        printf("\n");
        p = p->next;
    }
    printf("\n");
}

// 创建不被释放的头节点
struct test *creat_head_node()
{
    struct test *newnode = (struct test *)malloc(sizeof(struct test));
    if (newnode == NULL)
    {
        printf("creat ListNode error\n");
        return NULL;
    }
    newnode->num = 1;
    newnode->arr = (unsigned char *)malloc(1 * sizeof(unsigned char));
    newnode->next = NULL;
    newnode->arr[0] = 0xaa;
    if (newnode->arr == NULL)
    {
        printf("内存分配失败\n");
        free(newnode);
        return NULL;
    }
    int struct_size = sizeof(newnode->num) + sizeof(newnode->next) + sizeof(unsigned char) * 1 + sizeof(newnode->next);
    printf("创建头节点，开辟了%d字节空间\n", struct_size);
    return newnode;
}

/*
 创建节点
 参数的num：为里面arr数组的元素个数
*/
struct test *creat_link_arr(int arr_num)
{
    struct test *newnode = (struct test *)malloc(sizeof(struct test));
    if (newnode == NULL)
    {
        printf("BuySListNode error\n");
        return NULL;
    }
    newnode->num = arr_num;
    newnode->next = NULL;
    newnode->arr = (unsigned char *)malloc((arr_num + 1) * sizeof(unsigned char));
    if (newnode->arr == NULL)
    {
        printf("内存分配失败\n");
        free(newnode);
        return NULL;
    }
    int struct_size = sizeof(newnode->num) + sizeof(newnode->next) + sizeof(unsigned char) * arr_num + sizeof(newnode->next);
    printf("创建了一个节点，开辟了%d字节空间\n", struct_size);
    return newnode;
}

// 释放内存---清空链表---保留头节点
void free_link_list(struct test *head)
{
    struct test *current = head->next; // 保留头节点
    head->next = NULL;                 // 必须要赋值为NULL不然遍历会出错
    struct test *temp;

    while (current != NULL)
    {
        temp = current;
        current = current->next;
        printf("arr的元素个数为 %d\n", strlen(temp->arr));
        int arr_num = strlen(temp->arr);
        int struct_size = sizeof(temp->num) + sizeof(temp->next) + sizeof(unsigned char) * strlen(temp->arr) + sizeof(temp->next);

        free(temp->arr);
        temp->arr = NULL;

        int arr_size = 1;
        int node_size = 1;

        if (NULL == temp->arr)
        {
            arr_size = 0;
        }

        free(temp);
        temp = NULL;
        if (NULL == temp)
        {
            node_size = 0;
        }
        printf("删除节点,原数据结构体占空间大小为 %d 个字节,数组元素个数为 %d ,占 %d 个字节空间,释放数值后剩余 %d 个字节空间,删除节点后剩余 %d 个字节空间\n",
               struct_size, arr_num, sizeof(unsigned char) * arr_num, arr_size, node_size);
    }
    temp = NULL;
}

/*
 给节点赋值
 *head： 头节点
 num：   结构体里面对应数组的个数
*/
void insert_from_tail(struct test *head, int num)
{
    struct test *p = head;
    struct test *newnode = creat_link_arr(num);
    memcpy(newnode->arr, myarr, num);
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = newnode;
}

/*
 给节点赋值
 *head： 头节点
 num：   结构体里面对应数组的个数
*/
void insert_from_tail1(struct test *head, int num, unsigned char arr[])
{
    struct test *p = head;
    struct test *newnode = creat_link_arr(num);
    memcpy(newnode->arr, arr, num);
    newnode->arr[num] = '\0'; // 在数组末尾加一个结束的标志==='\0'
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = newnode;
}

// 读取节点内容
void read_node_oldest(struct test *head)
{
    struct test *p;
    struct test *temp;
    p = head->next;
    while (p != NULL)
    {
        printf("arr的元素个数为 %04d\n", strlen(p->arr));
        int arr_num = strlen(p->arr);
        int struct_size = sizeof(p->num) + sizeof(p->next) + sizeof(unsigned char) * strlen(p->arr) + sizeof(temp->next);

        printf("读取的数据为：\n");
        for (int i = 0; i < p->num; i++)
        {
            printf("%02x ", p->arr[i]);
        }

        temp = p;
        head->next = p->next;

        free(temp->arr);
        temp->arr = NULL;
        int arr_size = 1;
        int node_size = 1;

        if (NULL == temp->arr)
        {
            arr_size = 0;
        }
        free(temp);
        temp = NULL;
        printf("\n");
        p = head->next;
        if (NULL == temp)
        {
            node_size = 0;
        }
        printf("删除节点,原数据结构体占空间大小为 %d 个字节,数组元素个数为 %d ,占 %d 个字节空间,释放数值后剩余 %d 个字节空间,删除节点后剩余 %d 个字节空间\n",
               struct_size, arr_num, sizeof(unsigned char) * arr_num, arr_size, node_size);
        printf("\n");
    }
}

// 删除链表尾部
void delete_link_list_form_behind(struct test *head)
{
    if (head->next == NULL)
    {
        return;
    }
    else
    {
        // 尾部节点
        struct test *tail = head;
        // 尾部前一个节点
        struct test *prev_tail = NULL;
        while (tail->next != NULL)
        {
            prev_tail = tail;
            tail = tail->next;
        }

        printf("arr的元素个数为 %d\n", strlen(tail->arr));
        int arr_num = strlen(tail->arr);
        int struct_size = sizeof(tail->num) + sizeof(tail->next) + sizeof(unsigned char) * strlen(tail->arr) + sizeof(tail->next);

        // 释放尾节点的数据空间
        free(tail->arr);
        tail->arr = NULL;
        int arr_size = 1;
        int node_size = 1;

        if (NULL == tail->arr)
        {
            arr_size = 0;
        }

        // 释放尾节点
        free(tail);
        tail = NULL;
        // 把尾节点的next指向空
        prev_tail->next = NULL;
        if (NULL == tail)
        {
            node_size = 0;
        }
        printf("删除节点,原数据结构体占空间大小为 %d 个字节,数组元素个数为 %d ,占 %d 个字节空间,释放数值后剩余 %d 个字节空间,删除节点后剩余 %d 个字节空间\n",
               struct_size, arr_num, sizeof(unsigned char) * arr_num, arr_size, node_size);
    }
}

// 统计链表节点个数
int get_link_list_node_num(struct test *head)
{
    int cnt = 0;
    struct test *p = head;
    while (p != NULL)
    {
        p = p->next;
        cnt++;
    }
    return cnt;
}

int main()
{
    struct test *head = creat_head_node();

    // insert_from_tail(head, 10);
    // insert_from_tail(head, 20);
    int myarr2_num = sizeof(myarr2) / sizeof(myarr2[0]);
    insert_from_tail1(head, myarr2_num, myarr2);
    insert_from_tail1(head, 10, myarr);
    insert_from_tail1(head, 20, myarr);
    insert_from_tail1(head, 30, myarr);
    insert_from_tail1(head, 40, myarr);
    insert_from_tail1(head, 100, myarr);
    printfLink(head);

    // delete_link_list_form_behind(head);
    // printfLink(head);

    // int num = get_link_list_node_num(head);
    // printf("链表的节点个数为 = %d\n", num);

    // free_link_list(head);
    read_node_oldest(head);
    printfLink(head);
    return 0;
}