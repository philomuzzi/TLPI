#include <thread.h>

extern "C" {
    #include "tlpi_hdr.h"
}

struct Point {
    char *key;
    void *value;
};

struct Node {
    Node *left;
    Node *right;
    Point *point;
};

typedef Node* tree

void initialize(tree)
{
    tree = malloc(sizeof(Node));
    memset(tree, 0, sizeof(Node));
}

int add(tree, char *key, void *value)
{
    if (tree == NULL)
        return -1;

    if (tree->left == NULL && tree->right == NULL)
    {
        if (tree->point == NULL)
        {

        }
    }
}

int main(int argc, char const *argv[])
{
    return 0;
}