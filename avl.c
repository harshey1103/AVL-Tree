#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_INPUT_LENGTH 50

struct Node {
  int key;
  struct Node * left;
  struct Node * right;
  int height;
};

int height(struct Node * node) {
  if (node == NULL)
    return 0;
  return node -> height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

struct Node * newNode(int key) {
  struct Node * node = (struct Node * ) malloc(sizeof(struct Node));
  node -> key = key;
  node -> left = NULL;
  node -> right = NULL;
  node -> height = 1;
  return node;
}

int getBalance(struct Node * node) {
  if (node == NULL)
    return 0;
  return height(node -> left) - height(node -> right);
}

struct Node * rightRotate(struct Node * y) {
  struct Node * x = y -> left;
  struct Node * T2 = x -> right;

  x -> right = y;
  y -> left = T2;

  y -> height = max(height(y -> left), height(y -> right)) + 1;
  x -> height = max(height(x -> left), height(x -> right)) + 1;

  return x;
}

struct Node * leftRotate(struct Node * x) {
  struct Node * y = x -> right;
  struct Node * T2 = y -> left;

  y -> left = x;
  x -> right = T2;

  x -> height = max(height(x -> left), height(x -> right)) + 1;
  y -> height = max(height(y -> left), height(y -> right)) + 1;

  return y;
}

struct Node * insert(struct Node * node, int key) {
  if (node == NULL)
    return newNode(key);

  if (key < node -> key)
    node -> left = insert(node -> left, key);
  else if (key > node -> key)
    node -> right = insert(node -> right, key);
  else
    return node;

  node -> height = 1 + max(height(node -> left), height(node -> right));

  int balance = getBalance(node);

  if (balance > 1 && key < node -> left -> key)
    return rightRotate(node);

  if (balance < -1 && key > node -> right -> key)
    return leftRotate(node);

  if (balance > 1 && key > node -> left -> key) {
    node -> left = leftRotate(node -> left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node -> right -> key) {
    node -> right = rightRotate(node -> right);
    return leftRotate(node);
  }

  return node;
}

struct Node * minValueNode(struct Node * node) {
  struct Node * current = node;
  while (current -> left != NULL)
    current = current -> left;
  return current;
}

struct Node * deleteNode(struct Node * root, int key) {
  if (root == NULL)
    return root;

  if (key < root -> key)
    root -> left = deleteNode(root -> left, key);
  else if (key > root -> key)
    root -> right = deleteNode(root -> right, key);
  else {
    if ((root -> left == NULL) || (root -> right == NULL)) {
      struct Node * temp = root -> left ? root -> left : root -> right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *
        root = * temp;
      free(temp);
    } else {
      struct Node * temp = minValueNode(root -> right);
      root -> key = temp -> key;
      root -> right = deleteNode(root -> right, temp -> key);
    }
  }

  if (root == NULL)
    return root;

  root -> height = 1 + max(height(root -> left), height(root -> right));

  int balance = getBalance(root);

  if (balance > 1 && getBalance(root -> left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root -> left) < 0) {
    root -> left = leftRotate(root -> left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root -> right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root -> right) > 0) {
    root -> right = rightRotate(root -> right);
    return leftRotate(root);
  }

  return root;
}

void inOrder(struct Node * root) {
  if (root != NULL) {
    inOrder(root -> left);
    printf("%d ", root -> key);
    inOrder(root -> right);
  }
}

void preOrder(struct Node * root) {
  if (root != NULL) {
    printf("%d ", root -> key);
    preOrder(root -> left);
    preOrder(root -> right);
  }
}

bool contains(struct Node * root, int key) {
  if (root == NULL)
    return false;
  if (root -> key == key)
    return true;
  if (root -> key > key)
    return contains(root -> left, key);
  return contains(root -> right, key);
}

int main() {
  struct Node * root = NULL;
  char input[MAX_INPUT_LENGTH];

  while (1) {
    fgets(input, sizeof(input), stdin);

    // Remove the newline character from input
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "exit") == 0) {
      break; // Exit the shell if user enters "exit"
    } else if (strncmp(input, "insert", 6) == 0) {
      char * num = input + 7;
      int key = atoi(num);
      root = insert(root, key);
    } else if (strncmp(input, "delete", 6) == 0) {
      char * num = input + 7;
      int key = atoi(num);
      root = deleteNode(root, key);
    } else if (strncmp(input, "contains", 8) == 0) {
      char * num = input + 9;
      int key = atoi(num);
      (contains(root, key))? printf("yes\n") : printf("no\n");
    } else if (strncmp(input, "in order", 8) == 0) {
      inOrder(root); printf("\n");
    }
  }
  
  preOrder(root); printf("\n");

  return 0;
}