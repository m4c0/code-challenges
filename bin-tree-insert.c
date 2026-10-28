struct node* insert( struct node* root, int data ) {
    if (root == NULL) {
        root = malloc(sizeof(struct node));
        root->data = data;
        root->left = root->right = NULL;
    } else if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}
