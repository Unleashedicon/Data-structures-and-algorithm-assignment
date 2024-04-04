#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into BST
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return createNode(key);
    
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    
    return root;
}

// Function to delete a node from BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;
    
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct Node* temp = root->right;
        while (temp && temp->left != NULL)
            temp = temp->left;
        
        // Copy the inorder successor's content to this node
        root->key = temp->key;
        
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Function to find the height of BST
int height(struct Node* root) {
    if (root == NULL)
        return -1;
    else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
}

// Function to print the level of a given data in BST
int levelOfNode(struct Node* root, int data, int level) {
    if (root == NULL)
        return -1;
    
    if (root->key == data) {
        printf("Level of node with data %d: %d\n", data, level);
        printf("Height of node with data %d: %d\n", data, height(root));
        return level;
    }

    int downlevel = levelOfNode(root->left, data, level + 1);
    if (downlevel != -1)
        return downlevel;
    
    downlevel = levelOfNode(root->right, data, level + 1);
    return downlevel;
}

// Function to print the inorder traversal of BST
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

int main() {
    // Create the BST represented by the given array
    int array[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int arraySize = sizeof(array) / sizeof(array[0]);
    struct Node* root = NULL;
    for (int i = 0; i < arraySize; i++)
        root = insert(root, array[i]);
    
    printf("BST created from the given array: ");
    inorderTraversal(root);
    printf("\n");
    
    // Delete a node from BST
    int dataToDelete;
    printf("Enter the data you want to delete from the BST: ");
    scanf("%d", &dataToDelete);
    root = deleteNode(root, dataToDelete);
    printf("BST after deleting node with data %d: ", dataToDelete);
    inorderTraversal(root);
    printf("\n");

    // Print the height of BST
    printf("Height of the BST: %d\n", height(root));
    
    // Input data from user
    int dataToFind;
    printf("Enter the data you want to find the level and height of: ");
    scanf("%d", &dataToFind);
    
    // Print the level and height of the input node
    levelOfNode(root, dataToFind, 0);
    
    return 0;
}
