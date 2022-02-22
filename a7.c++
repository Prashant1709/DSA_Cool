#include <bits/stdc++.h>
using namespace std;
struct tree
{
    int data;
    tree *left;
    tree *right;
};
struct tree *create(int d)
{
    struct tree *root = new tree;
    root->data = d;
    root->left = NULL;
    root->right = NULL;
    return root;
}
bool helper(struct tree *root1, struct tree *root2)
{
    if (root1 == NULL and root2 == NULL)
        return true;
    if (root1 and root2 and root1->data == root2->data)
        return (helper(root1->left, root2->right) and helper(root1->right, root2->left));
    return false;
}
bool chksym(struct tree *root)
{
    return helper(root, root);
}
int main()
{
    int val=0;
    struct tree *root = NULL;
    cout<<"Enter root node\n";
    cin>>val;
    root = create(val);
    cout << "Enter left node\n";
    cin >> val;
    root->left = create(val);
    cout << "Enter right node\n";
    cin >> val;
    root->right = create(val);
    cout << "Enter left sub-node\n";
    cin >> val;
    root->left->right = create(val);
    cout << "Enter right sub-node\n";
    cin >> val;
    root->left->left = create(val);
    cout << "Enter left sub-sub-node\n";
    cin >> val;
    root->right->left = create(val);
    cout << "Enter right sub-sub-node\n";
    cin >> val;
    root->right->right = create(val);
    if (chksym(root))
    {
        cout << "Mirror Image" << endl;
    }
    else
    {
        cout << "Not Mirror" << endl;
    }
    return 0;
}