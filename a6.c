#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

int search(int arr[], int start, int end, int key);
struct node *newNode(int data);

struct node *buildTree(int in[], int pre[], int inStart, int inEnd)
{
    static int preIndex = 0;
    if (inStart > inEnd)
        return NULL;
    struct node *tNode = newNode(pre[preIndex++]);
    if (inStart == inEnd)
        return tNode;
    int inIndex = search(in, inStart, inEnd, tNode->data);
    tNode->left = buildTree(in, pre, inStart, inIndex - 1);
    tNode->right = buildTree(in, pre, inIndex + 1, inEnd);
    return tNode;
}

int search(int arr[], int start, int end, int key)
{
    int i;
    for (i = start; i <= end; i++)
    {
        if (arr[i] == key)
            return i;
    }
}

struct node *newNode(int data)
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

void printPreOrder(struct node *node)
{
    if (node == NULL)
        return;
    printf("%d ", node->data);
    printPreOrder(node->left);
    printPreOrder(node->right);
}
void printInOrder(struct node *node)
{
    if (node == NULL)
        return;
    printInOrder(node->left);
    printf("%d ", node->data);
    printInOrder(node->right);
}

void printPostOrder(struct node *node)
{
    if (node == NULL)
        return;
    printPostOrder(node->left);
    printPostOrder(node->right);
    printf("%d ", node->data);
}

int main()
{
    int n;
    printf("Enter number of nodes in binary tree:\n");
    scanf("%d", &n);
    int inord[10000];
    int preord[10000];
    printf("Enter values for Binary tree in Preorder format:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &preord[i]);
    }
    printf("Enter values for Binary tree in Inorder format:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &inord[i]);
    }
    struct node *root = buildTree(inord, preord, 0, n - 1);
    printf("\nA binary tree with the following properties is created:-\n");
    printf("Preorder traversal of the constructed tree is:\n");
    printPreOrder(root);
    printf("\nInorder traversal of the constructed tree is:\n");
    printInOrder(root);
    printf("\nPostorder traversal of the constructed tree is:\n");
    printPostOrder(root);
    return 0;
}