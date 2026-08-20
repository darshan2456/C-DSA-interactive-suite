#include "bst.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int deletionStrategy = 1;
#define SUCCESSOR 1
#define PREDECESSOR 2
#define BST_ASCII_MAX_HEIGHT 6

static int bst_max_int(int a, int b)
{
    return (a > b) ? a : b;
}

static int bst_value_width(const bstNode* root)
{
    if (root == NULL)
        return 1;

    char buffer[32];
    int width = snprintf(buffer, sizeof(buffer), "%d", root->data);
    if (width < 1)
        width = 1;

    return bst_max_int(width,
                       bst_max_int(bst_value_width(root->left), bst_value_width(root->right)));
}

static void bst_fill_row(char* row, int width)
{
    memset(row, ' ', (size_t)width);
    row[width] = '\0';
}

static void bst_place_text(char* row, int width, int center, const char* text)
{
    int text_width = (int)strlen(text);
    int start = center - (text_width / 2);

    if (start < 0)
        start = 0;
    if (start + text_width > width)
        start = width - text_width;

    for (int i = 0; i < text_width && start + i < width; i++)
        row[start + i] = text[i];
}

static void bst_render_ascii(const bstNode* node, int level, int left, int right, char** rows,
                             int row_count, int width)
{
    if (node == NULL || level * 2 >= row_count || left > right)
        return;

    int center = (left + right) / 2;
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d", node->data);
    bst_place_text(rows[level * 2], width, center, buffer);

    int connector_row = level * 2 + 1;
    if (connector_row < row_count)
    {
        if (node->left != NULL)
        {
            int left_center = (left + center - 1) / 2;
            int slash_position = (center + left_center) / 2;
            if (slash_position >= 0 && slash_position < width)
                rows[connector_row][slash_position] = '/';
        }
        if (node->right != NULL)
        {
            int right_center = (center + 1 + right) / 2;
            int slash_position = (center + right_center) / 2;
            if (slash_position >= 0 && slash_position < width)
                rows[connector_row][slash_position] = '\\';
        }
    }

    bst_render_ascii(node->left, level + 1, left, center - 1, rows, row_count, width);
    bst_render_ascii(node->right, level + 1, center + 1, right, rows, row_count, width);
}

void bst_print_ascii(const bstNode* root)
{
    if (root == NULL)
    {
        printf("Tree is empty\n");
        return;
    }

    int height = tree_height(root);
    if (height > BST_ASCII_MAX_HEIGHT)
    {
        printf("Tree is too tall to render as ASCII (max supported height: %d)\n",
               BST_ASCII_MAX_HEIGHT);
        return;
    }

    int value_width = bst_value_width(root) + 2;
    int row_count = (height * 2) - 1;
    int width = (1 << height) * value_width;

    char** rows = malloc((size_t)row_count * sizeof(char*));
    if (rows == NULL)
    {
        printf("Tree is too large to render\n");
        return;
    }

    for (int i = 0; i < row_count; i++)
    {
        rows[i] = malloc((size_t)width + 1);
        if (rows[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(rows[j]);
            free(rows);
            printf("Tree is too large to render\n");
            return;
        }
        bst_fill_row(rows[i], width);
    }

    bst_render_ascii(root, 0, 0, width - 1, rows, row_count, width);

    for (int i = 0; i < row_count; i++)
    {
        printf("%s\n", rows[i]);
        free(rows[i]);
    }
    free(rows);
}

// insert function returns -1 on malloc failure, 0 when value already exists in the tree and 1 on
// successful insertion

int bst_insert(bstNode** head_ref, int value)
{
    if (head_ref == NULL)
        return -1;

    if ((*head_ref) == NULL)
    {
        bstNode* node = malloc(sizeof(bstNode));
        if (node == NULL)
            return -1;
        node->data = value;
        node->left = NULL;
        node->right = NULL;
        *head_ref = node;
        return 1;
    }
    if ((*head_ref)->data == value)
    {
        return 0;
    }
    if ((*head_ref)->data > value)
    {
        if ((*head_ref)->left == NULL)
        {
            bstNode* node = malloc(sizeof(bstNode));
            if (node == NULL)
                return -1;
            node->data = value;
            node->left = NULL;
            node->right = NULL;
            (*head_ref)->left = node;
            return 1;
        }
        else
        {
            return bst_insert(&(*head_ref)->left, value);
        }
    }
    else if ((*head_ref)->data < value)
    {
        if ((*head_ref)->right == NULL)
        {
            bstNode* node = malloc(sizeof(bstNode));
            if (node == NULL)
                return -1;
            node->data = value;
            node->left = NULL;
            node->right = NULL;
            (*head_ref)->right = node;
            return 1;
        }
        else
        {
            return bst_insert(&(*head_ref)->right, value);
        }
    }
    return -1;
}

void bst_inorder(const bstNode* head)
{
    if (head == NULL)
    {
        return;
    }
    bst_inorder(head->left);
    printf("%d,", head->data);
    bst_inorder(head->right);
}

void bst_preorder(const bstNode* head)
{
    if (head == NULL)
    {
        return;
    }
    printf("%d,", head->data);
    bst_preorder(head->left);
    bst_preorder(head->right);
}

void bst_postorder(const bstNode* head)
{
    if (head == NULL)
    {
        return;
    }
    bst_postorder(head->left);
    bst_postorder(head->right);
    printf("%d,", head->data);
}

void printLevel(bstNode* head, int level)
{
    if (!head)
        return;

    if (level == 1)
        printf("%d ", head->data);
    else
    {
        printLevel(head->left, level - 1);
        printLevel(head->right, level - 1);
    }
}

void bst_level_order(struct bstNode* head)
{
    if (!head)
        return;

    int h = tree_height(head);

    for (int i = 1; i <= h; i++)
    {
        printf("Level %d: ", i);
        printLevel(head, i);
        printf("\n");
    }
}

int countnodes(const bstNode* head)
{
    if (head == NULL)
        return 0;
    return countnodes(head->left) + countnodes(head->right) + 1;
}

int tree_height(const bstNode* root)
{
    if (root == NULL)
        return 0;
    int left_height = tree_height(root->left) + 1;
    int right_height = tree_height(root->right) + 1;

    if (left_height > right_height)
        return left_height;
    else
        return right_height;
}

void destroy_bst(bstNode* head)
{
    if (head == NULL)
    {
        return;
    }
    destroy_bst(head->left);
    destroy_bst(head->right);
    free(head);
}

bstNode* bst_delete(bstNode* root, int value)
{
    if (root == NULL)
        return NULL;

    if (value < root->data)
    {
        root->left = bst_delete(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = bst_delete(root->right, value);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        else if (root->left == NULL)
        {
            bstNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            bstNode* temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            if (deletionStrategy == SUCCESSOR)
            {
                bstNode* successor = root->right;
                while (successor->left != NULL)
                    successor = successor->left;
                root->data = successor->data;
                root->right = bst_delete(root->right, successor->data);
            }
            else if (deletionStrategy == PREDECESSOR)
            {
                bstNode* predecessor = root->left;
                while (predecessor->right != NULL)
                    predecessor = predecessor->right;
                root->data = predecessor->data;
                root->left = bst_delete(root->left, predecessor->data);
            }
        }
    }
    return root;
}
