#include <iostream>
#include <map>
#include <cstdio>
#include <cassert>
#include <cstdlib>

using namespace std;

typedef struct linknode {
    int value;
    struct linknode *next;
} linknode, *linklist;
//add a linknode to linklist
linklist add_item_to_list(linklist head, int value) 
{

    linklist p = (linklist)malloc(sizeof(linknode));
    assert(p);
    p->value = value;
    if (head) {
        p->next = head;
    } else {
        p->next = NULL;
    }
    head = p;
    return head;
}
linklist create_list(int num)
{
    linklist head = NULL;
    int i;
    for (i = 1; i <= num; i++) {
        linklist p = (linklist)malloc(sizeof(linknode));
        assert(p);
        p->value = i;
        if (head) {
            p->next = head;
        } else {
            p->next = NULL;
        }
        head = p;
    }
    return head;
}

linklist create_list_by_input() 
{
    int value;
    linklist head = NULL;
    while(scanf("%d", &value) && value != -1) {
        linklist p = (linklist)malloc(sizeof(linknode));
        assert(p);
        p->value = value;
        if (head) {
            p->next = head;
        } else {
            p->next = NULL;
        }
        head = p;
    }
    return head;
}

linklist create_list_by_add(linklist h1, linklist h2)
{
    if (!h1 && !h2) {
        return NULL;
    } else if (!h1) {
        return h2;
    } else if (!h2) {
        return h1;
    }
    
    linklist head = NULL;
    int flag = 0;
    while(h1 || h2) {
        int value = flag;
        if (h1) {
            value += h1->value;
            h1 = h1->next;
        }
        if (h2) {
            value += h2->value;
            h2 = h2->next;
        }

        if (value /10) {
            flag = 1;
            value %= 10;
        } else {
            flag = 0;
        }
        head = add_item_to_list(head, value);
    }

    if (flag) {
        head = add_item_to_list(head, 1);
    }
   
   return head;
}
void display_list(linklist head)
{
    printf("--");
    linklist p;
    for (p = head; p; p=p->next) {
        printf("%d--", p->value);
    }
    printf("\n");
}

linklist reverse_linklist(linklist h) 
{
    linklist new_head = NULL;
    if (!h || !h->next) {
        return h;
    }
    new_head = reverse_linklist(h->next);
    h->next->next = h;
    h->next = NULL;
    return new_head;
}
//remove the duplicates records in the linklist
void remove_duplicates(linklist head)
{
    map<int, int> hash;
    linklist pre = NULL , cur = head;
    
    while(cur){
        int value = cur->value;
        if (hash.find(value) != hash.end()) {
            pre->next = cur->next;
            free(cur);
            cur = pre->next;
        } else {
            pre = cur;
            cur = cur->next;
            hash.insert(pair<int, int>(value, 1));
        }
    }
}
//1-2-3-4-5-6 to 1-3-5-6-4-2
linklist assembly_linklist(linklist h)
{
    if (!h) return NULL;
    linklist list1 = NULL, list2 = NULL;
    linklist cur = h, last;
    
    while(cur) {
        last = cur->next;
        cur->next = NULL;
        if (list1) {
            list1->next = cur;
        }
        list1 = cur;
        
        cur = last;
        if (cur) {
            last = cur->next;
            cur->next = NULL;
            if (list2) {
                cur->next = list2;
            } 
            list2 = cur;
        }

        cur = last;
    }

    if (list2) {
        list1->next = list2;
    }
    //display_list(list1);
    //display_list(list2);
    return h;

}
int main(int argc, char **argv)
{
    //linklist head = create_list(10);
    //display_list(head);
    //printf("after reverse\n");
    //linklist new_head = reverse_linklist(head);
    //display_list(new_head);
    //printf("after remove_duplicates\n");
    //remove_duplicates(new_head); 
    //display_list(new_head);

    /*
    linklist head1 = create_list_by_input();
    display_list(head1);
    linklist head2 = create_list_by_input();
    display_list(head2);
    linklist head3 = create_list_by_add(head1, head2);
    display_list(head3);
    */

    linklist head = create_list(9);
    display_list(head);
    linklist h = assembly_linklist(head);
    display_list(h);
    return 0;
}

