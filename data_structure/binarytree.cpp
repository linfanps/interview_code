#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cassert>
using namespace std;

typedef struct treenode {
    int item;
    struct treenode *left, *right;
}treenode, *treelink;
treelink create_treelink(int item)
{
    treelink tl = (treelink)malloc(sizeof(treenode));
    assert(tl);
    tl->item = item;
    tl->left = tl->right = NULL;
    return tl;
}
//题6，根据前序和中序遍历结果构造二叉树
treelink create_tree_by_order(int VLR[], int LVR[], int n)
{
    assert(VLR && LVR);
    if (n == 0) return NULL;
    int value = VLR[0];
    int k;
    for (k = 0; k < n; k++) {
        if (LVR[k] == value) {
            break;
        }
    }

    treelink root = create_treelink(value);
    root->left = create_tree_by_order(VLR+1, LVR, k);
    root->right = create_tree_by_order(VLR+k+1, LVR+k+1, n-k-1);

    return root;
}
//递归前序中序后序遍历二叉树
void pre_order(treelink root)
{
    if (!root) return ;
    printf("%d ", root->item);
    pre_order(root->left);
    pre_order(root->right);
}
void in_order(treelink root)
{
    if (!root) return ;
    in_order(root->left);
    printf("%d ", root->item);
    in_order(root->right);
}
void post_order(treelink root)
{
    if (!root) return ;
    post_order(root->left);
    post_order(root->right);
    printf("%d ", root->item);
}
void travel_tree(treelink root)
{
    printf("travel by recursive\n");
    printf("pre order: ");
    pre_order(root);
    printf("\n");
    printf("in order: ");
    in_order(root);
    printf("\n");
    printf("post order: ");
    post_order(root);
    printf("\n");
}
//非递归方式前序后序遍历二叉树
void pre_order_v2(treelink root)
{
    if (!root) return ;
    stack<treelink> st;
    treelink temp;
    st.push(root);
    while (!st.empty()) {
        temp = st.top();
        st.pop();
        printf("%d ", temp->item);
        if (temp->right) st.push(temp->right);
        if (temp->left) st.push(temp->left);
    }

}
void post_order_v2(treelink root)
{
    if (!root) return ;
    treelink temp;
    stack<treelink> st1,st2;
    st1.push(root);
    while (!st1.empty()) {
        temp = st1.top();
        st1.pop();
        if (temp->left) st1.push(temp->left);
        if (temp->right) st1.push(temp->right);
        st2.push(temp);
    }

    while (!st2.empty()) {
        temp = st2.top();
        printf("%d ", temp->item);
        st2.pop();
    }
}
//题23 层序遍历二叉树
void layer_order(treelink root)
{
    if(!root) return ;
    treelink temp;
    queue<treelink> qt;
    qt.push(root);
    while (!qt.empty()) {
       temp = qt.front();
       qt.pop();
       printf("%d ", temp->item);
       if (temp->left) qt.push(temp->left);
       if (temp->right) qt.push(temp->right);
    }
}
void travel_tree_v2(treelink root)
{
    printf("travel v2:\n");
    printf("pre order: ");
    pre_order_v2(root);
    printf("\n");
    printf("post order: ");
    post_order_v2(root);
    printf("\n");
    printf("layer order: ");
    layer_order(root);
    printf("\n");
}

//题39 树的高度
int tree_depth(treelink root)
{
    if (!root) return 0;
    int l_depth = tree_depth(root->left);
    int r_depth = tree_depth(root->right);

    return (l_depth > r_depth) ? l_depth + 1 : r_depth + 1;
}
//题25 输入一棵二叉树和一个整数，打印出二叉树结点值为输入整数的所有路径，从树的根结点开始一直到叶结点所经历结点形成一条路径
void find_a_path_of_sum(treelink root, int sum, vector<int> &vt)
{
    assert(root);
    vt.push_back(root->item);
    if (root->left == NULL && root->right == NULL && sum == root->item) {
        vector<int>::iterator iter;
        printf ("one path:");
        for (iter = vt.begin(); iter != vt.end(); iter++) {
            printf("%d ", *iter);
        }
        printf("\n");
    } else if (root->right == NULL && root->left == NULL) {
        ;
    } else {
        if (root->left)
            find_a_path_of_sum(root->left, sum-root->item, vt);
        if(root->right)
            find_a_path_of_sum(root->right, sum-root->item, vt);
    }
    vt.pop_back();
}
// 题50：输入一棵二叉树和两个树结点，给出它们最低的公共祖先
bool find_treelink(treelink root, treelink t, vector<treelink> &vt)
{
    if (root == NULL) return false;
    vt.push_back(root);
    if (root == t) {
        return true;
    }
    bool find = false;
    if (!find)
        find = find_treelink(root->left, t, vt);
    if (!find)
        find = find_treelink(root->right, t, vt);
    if (!find)
        vt.pop_back();
    return find;
}
treelink find_common_parent(treelink root, treelink t1, treelink t2)
{
    vector<treelink> path1, path2;
    assert(find_treelink(root, t1, path1) && find_treelink(root, t2, path2));
    vector<treelink>::iterator iter1 = path1.begin();
    vector<treelink>::iterator iter2 = path2.begin();
    treelink parent = NULL;
    while(iter1 != path1.end() && iter2 != path2.end() && *iter1  == *iter2) {
        parent = *iter1;
        iter1++; 
        iter2++;
    }
    if (parent == NULL)
        printf("not found\n");
    else
        printf("commom parent is %d\n", parent->item);
    return parent;
}
int main() 
{
    /*题6 构建二叉树*/
    int pre_order[] = {1, 2, 4, 7,15, 3, 5, 6, 8};
    int in_order[] = {4, 7, 2, 15, 1, 5, 3, 8, 6};
    
    treelink root = create_tree_by_order(pre_order, in_order, sizeof(pre_order)/sizeof(int));
    travel_tree(root);
    travel_tree_v2(root);

    int depth = tree_depth(root);
    printf("tree depth is %d\n", depth);
    printf("find a path sum is 18\n");
    vector<int> vt;
    find_a_path_of_sum(root, 18, vt);
    find_common_parent(root, root->left, root->right);
    return 0;
}

