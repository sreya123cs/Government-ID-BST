/* ============================================================
   GOVERNMENT IDENTIFICATION DATABASE - BST IMPLEMENTATION
   ------------------------------------------------------------
   a) Build BST + inorder traversal
   b) Compare BST Search vs Linear Search (comparison counts)
   c) Analyse effect of insertion order / key length on height
      and search performance
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IDS 100
#define ID_LEN  20

struct Node
{
    char id[ID_LEN];
    struct Node *left;
    struct Node *right;
    int inorderIndex;  /* used only for the 2D "/  \" tree diagram */
    int depthLevel;    /* used only for the 2D "/  \" tree diagram */
};

/* ---------- Node creation ---------- */
struct Node* createNode(char id[])
{
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newNode->id, id);
    newNode->left  = NULL;
    newNode->right = NULL;
    newNode->inorderIndex = -1;
    newNode->depthLevel   = -1;
    return newNode;
}

/* ---------- Insert into BST ---------- */
struct Node* insert(struct Node *root, char id[])
{
    if (root == NULL)
    {
        return createNode(id);
    }

    if (strcmp(id, root->id) < 0)
    {
        root->left = insert(root->left, id);
    }
    else if (strcmp(id, root->id) > 0)
    {
        root->right = insert(root->right, id);
    }
    /* if equal, ID already exists -> ignore duplicate */

    return root;
}

/* ---------- Inorder traversal (gives sorted order) ---------- */
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s ", root->id);
        inorder(root->right);
    }
}

/* ---------- Height of BST (root counted as level 1) ---------- */
int height(struct Node *root)
{
    int leftHeight, rightHeight;

    if (root == NULL)
    {
        return 0;
    }

    leftHeight  = height(root->left);
    rightHeight = height(root->right);

    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

/* ---------- Depth (level) at which a given key is found (1-indexed) ---------- */
int depthOf(struct Node *root, char key[], int level)
{
    if (root == NULL)
    {
        return -1;
    }
    if (strcmp(key, root->id) == 0)
    {
        return level;
    }
    if (strcmp(key, root->id) < 0)
    {
        return depthOf(root->left, key, level + 1);
    }
    return depthOf(root->right, key, level + 1);
}

/* ---------- BST Search (counts comparisons) ---------- */
int bstSearch(struct Node *root, char key[], int *comparisons)
{
    while (root != NULL)
    {
        (*comparisons)++;

        if (strcmp(key, root->id) == 0)
        {
            return 1;
        }
        else if (strcmp(key, root->id) < 0)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return 0;
}

/* ---------- Linear Search (counts comparisons) ---------- */
int linearSearch(char ids[][ID_LEN], int n, char key[], int *comparisons)
{
    int i;
    for (i = 0; i < n; i++)
    {
        (*comparisons)++;
        if (strcmp(ids[i], key) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/* ============================================================
   VISUAL TREE PRINTER (plain ASCII only - safe on every terminal)
   Uses "/" for a LEFT branch and "\" for a RIGHT branch, with
   "|" to continue a vertical line down past a sibling, e.g.:

   ROOT: A102
    \--R: A25
        |--L: A120
        \--R: A7
            |--L: A45
            \--R: B100
                \--R: B12
                    \--R: B3
   ============================================================ */
void printTree(struct Node *node, char *prefix, int isRoot, int isLeftChild, const char *branchLabel)
{
    if (node == NULL)
    {
        return;
    }

    /* Print current node's line.
       "/" always marks a LEFT child, "\" always marks a RIGHT child. */
    if (isRoot)
    {
        printf("ROOT: %s\n", node->id);
    }
    else
    {
        printf("%s%s--%s: %s\n",
               prefix,
               isLeftChild ? "/" : "\\",
               branchLabel,
               node->id);
    }

    /* Build the prefix that children of this node will use.
       If this node was a LEFT child, keep a "|" running down so the
       viewer can see it connects back up to a branch that still has
       a sibling (the right side) above/beside it; a RIGHT child (or
       the root) needs no such continuation line. */
    char newPrefix[256];
    if (isRoot)
    {
        strcpy(newPrefix, "    ");
    }
    else
    {
        snprintf(newPrefix, sizeof(newPrefix), "%s%s",
                 prefix,
                 isLeftChild ? "|   " : "    ");
    }

    int hasLeft  = (node->left  != NULL);
    int hasRight = (node->right != NULL);

    if (hasLeft)
    {
        printTree(node->left, newPrefix, 0, 1, "L");
    }
    if (hasRight)
    {
        printTree(node->right, newPrefix, 0, 0, "R");
    }
}

/* ============================================================
   TOP-DOWN "/  \" TREE DIAGRAM (properly centered, textbook style)
   ------------------------------------------------------------
   This uses the classic recursive tree-layout algorithm: each
   subtree is rendered as its own little block of text lines,
   and a parent is drawn centered exactly above the midpoint of
   its own children, joined to them with underscores and a
   '/' or '\'. Left and right blocks are then merged side by
   side. This avoids the "staircase drift" you get from simply
   spacing nodes by their inorder position.
   ============================================================ */
#define MAX_LINES 30
#define MAX_WIDTH 200

typedef struct
{
    char lines[MAX_LINES][MAX_WIDTH];
    int  numLines;
    int  width;
    int  rootPos;   /* column, within the first line, of this node's own label */
} Box;

static void fillSpaces(char *buf, int *pos, int count)
{
    int i;
    for (i = 0; i < count; i++) buf[(*pos)++] = ' ';
}
static void fillChar(char *buf, int *pos, char c, int count)
{
    int i;
    for (i = 0; i < count; i++) buf[(*pos)++] = c;
}
static void fillStr(char *buf, int *pos, const char *s)
{
    while (*s) buf[(*pos)++] = *s++;
}

/* Recursively build the drawn "box" for the subtree rooted at node */
Box* buildBox(struct Node *node)
{
    Box *box = (Box*)malloc(sizeof(Box));
    memset(box, 0, sizeof(Box));

    if (node == NULL)
    {
        return box;   /* empty box: numLines = width = rootPos = 0 */
    }

    int u = (int)strlen(node->id);

    /* Case 1: leaf node */
    if (node->left == NULL && node->right == NULL)
    {
        strcpy(box->lines[0], node->id);
        box->numLines = 1;
        box->width    = u;
        box->rootPos  = u / 2;
        return box;
    }

    /* Case 2: only a left child */
    if (node->right == NULL)
    {
        Box *L = buildBox(node->left);
        int n = L->width, x = L->rootPos, p = L->numLines;
        int pos = 0, i;
        char first[MAX_WIDTH] = {0}, second[MAX_WIDTH] = {0};

        fillSpaces(first, &pos, x + 1);
        fillChar(first, &pos, '_', n - x - 1);
        fillStr(first, &pos, node->id);
        first[pos] = '\0';

        pos = 0;
        fillSpaces(second, &pos, x);
        second[pos++] = '/';
        fillSpaces(second, &pos, n - x - 1 + u);
        second[pos] = '\0';

        strcpy(box->lines[0], first);
        strcpy(box->lines[1], second);
        for (i = 0; i < p; i++)
        {
            int len;
            strcpy(box->lines[2 + i], L->lines[i]);
            len = (int)strlen(box->lines[2 + i]);
            fillSpaces(box->lines[2 + i], &len, u);
            box->lines[2 + i][len] = '\0';
        }
        box->numLines = p + 2;
        box->width    = n + u;
        box->rootPos  = n + u / 2;
        free(L);
        return box;
    }

    /* Case 3: only a right child */
    if (node->left == NULL)
    {
        Box *R = buildBox(node->right);
        int m = R->width, y = R->rootPos, q = R->numLines;
        int pos = 0, i;
        char first[MAX_WIDTH] = {0}, second[MAX_WIDTH] = {0};

        fillStr(first, &pos, node->id);
        fillChar(first, &pos, '_', y);
        fillSpaces(first, &pos, m - y);
        first[pos] = '\0';

        pos = 0;
        fillSpaces(second, &pos, u + y);
        second[pos++] = '\\';
        fillSpaces(second, &pos, m - y - 1);
        second[pos] = '\0';

        strcpy(box->lines[0], first);
        strcpy(box->lines[1], second);
        for (i = 0; i < q; i++)
        {
            char tmp[MAX_WIDTH] = {0};
            int p2 = 0;
            fillSpaces(tmp, &p2, u);
            fillStr(tmp, &p2, R->lines[i]);
            tmp[p2] = '\0';
            strcpy(box->lines[2 + i], tmp);
        }
        box->numLines = q + 2;
        box->width    = m + u;
        box->rootPos  = u / 2;
        free(R);
        return box;
    }

    /* Case 4: two children */
    {
        Box *L = buildBox(node->left);
        Box *R = buildBox(node->right);
        int n = L->width, x = L->rootPos, p = L->numLines;
        int m = R->width, y = R->rootPos, q = R->numLines;
        int pos = 0, i, maxLines;
        char first[MAX_WIDTH] = {0}, second[MAX_WIDTH] = {0};

        fillSpaces(first, &pos, x + 1);
        fillChar(first, &pos, '_', n - x - 1);
        fillStr(first, &pos, node->id);
        fillChar(first, &pos, '_', y);
        fillSpaces(first, &pos, m - y);
        first[pos] = '\0';

        pos = 0;
        fillSpaces(second, &pos, x);
        second[pos++] = '/';
        fillSpaces(second, &pos, n - x - 1 + u + y);
        second[pos++] = '\\';
        fillSpaces(second, &pos, m - y - 1);
        second[pos] = '\0';

        strcpy(box->lines[0], first);
        strcpy(box->lines[1], second);

        maxLines = (p > q) ? p : q;
        for (i = 0; i < maxLines; i++)
        {
            char tmp[MAX_WIDTH] = {0};
            int p2 = 0;
            const char *lline = (i < p) ? L->lines[i] : "";
            const char *rline = (i < q) ? R->lines[i] : "";
            fillStr(tmp, &p2, lline);
            fillSpaces(tmp, &p2, n - (int)strlen(lline));
            fillSpaces(tmp, &p2, u);
            fillStr(tmp, &p2, rline);
            tmp[p2] = '\0';
            strcpy(box->lines[2 + i], tmp);
        }
        box->numLines = maxLines + 2;
        box->width    = n + m + u;
        box->rootPos  = n + u / 2;
        free(L);
        free(R);
        return box;
    }
}

/* Builds and prints the full centered top-down diagram for the given tree */
void printTree2D(struct Node *root)
{
    Box *box = buildBox(root);
    int i;
    for (i = 0; i < box->numLines; i++)
    {
        /* trim trailing spaces so lines don't look ragged */
        char *line = box->lines[i];
        int len = (int)strlen(line);
        while (len > 0 && line[len - 1] == ' ') len--;
        line[len] = '\0';
        printf("%s\n", line);
    }
    free(box);
}

/* ============================================================
   MAIN PROGRAM
   ============================================================ */
int main()
{
    struct Node *root = NULL;

    /* Insertion order exactly as given in the question */
    char ids[][ID_LEN] =
    {
        "A102", "A25", "A7", "B100", "B12", "A120", "B3", "A45"
    };
    int n = 8;
    int i;
    char key[ID_LEN];
    int bstComparisons, linearComparisons;

    printf("============================================\n");
    printf("   GOVERNMENT IDENTIFICATION DATABASE (BST)\n");
    printf("============================================\n\n");

    /* Build the BST */
    for (i = 0; i < n; i++)
    {
        root = insert(root, ids[i]);
    }

    /* Insertion order */
    printf("Insertion Order:\n");
    for (i = 0; i < n; i++) printf("%s ", ids[i]);
    printf("\n\n");

    /* a) Inorder traversal */
    printf("a) Inorder Traversal of BST (sorted order):\n");
    inorder(root);
    printf("\n\n");

    printf("BST Height (levels): %d\n\n", height(root));

    printf("Tree Structure (indented view):\n\n");
    printTree(root, "", 1, 0, "");
    printf("\n");

    printf("Tree Structure (top-down \"/  \\\" view):\n\n");
    printTree2D(root);
    printf("\n");

    /* b) Compare BST search vs linear search for EVERY ID */
    printf("============================================\n");
    printf("b) BST SEARCH vs LINEAR SEARCH COMPARISON\n");
    printf("============================================\n\n");
    printf("%-10s %-8s %-14s %-16s\n", "ID", "Depth", "BST Compares", "Linear Compares");
    printf("------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        bstComparisons = 0;
        linearComparisons = 0;
        bstSearch(root, ids[i], &bstComparisons);
        linearSearch(ids, n, ids[i], &linearComparisons);
        printf("%-10s %-8d %-14d %-16d\n",
               ids[i], depthOf(root, ids[i], 1), bstComparisons, linearComparisons);
    }

    /* Also test a key that does NOT exist */
    strcpy(key, "C99");
    bstComparisons = 0;
    linearComparisons = 0;
    bstSearch(root, key, &bstComparisons);
    linearSearch(ids, n, key, &linearComparisons);
    printf("%-10s %-8s %-14d %-16d   (not found)\n", key, "-", bstComparisons, linearComparisons);

    /* Interactive search (kept from original spec) */
    printf("\n--------------------------------------------\n");
    printf("Enter an ID to search (or press Ctrl+D to skip): ");
    if (scanf("%19s", key) == 1)
    {
        bstComparisons = 0;
        linearComparisons = 0;

        int foundBst = bstSearch(root, key, &bstComparisons);
        int foundLin = linearSearch(ids, n, key, &linearComparisons);

        printf("\nBST Search Result   : %s %s (Comparisons: %d)\n",
               key, foundBst ? "Found" : "Not Found", bstComparisons);
        printf("Linear Search Result: %s %s (Comparisons: %d)\n",
               key, foundLin ? "Found" : "Not Found", linearComparisons);

        printf("\n--- Performance Verdict ---\n");
        if (bstComparisons < linearComparisons)
            printf("BST Search performed better for this key.\n");
        else if (linearComparisons < bstComparisons)
            printf("Linear Search performed better for this key.\n");
        else
            printf("Both methods used the same number of comparisons.\n");
    }

    return 0;
}