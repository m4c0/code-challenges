int getHeight(struct node* root) {
    if (root == NULL) return 0;
    
    int left = 0;
    if (root->left != NULL) left = 1 + getHeight(root->left);

    int right = 0;
    if (root->right != NULL) right = 1 + getHeight(root->right);
    
    return left > right ? left : right;
}

