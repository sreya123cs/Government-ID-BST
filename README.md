# Government Identification Database Using BST

## 1. Aim

To implement a Binary Search Tree (BST) for organizing government identification numbers and compare the performance of BST Search with Linear Search.

## 2. Problem Statement

A government database stores the following identification numbers:

A102, A25, A7, B100, B12, A120, B3, A45

The objectives are:

- Implement a BST to organize the identification numbers.
- Display the inorder traversal.
- Analyse the resulting BST structure.
- Compare BST Search and Linear Search.
- Record the number of comparisons.
- Analyse the effect of key length and insertion order on BST height and search performance.
- Compare the observed results with theoretical complexities.
- Suggest a suitable approach for maintaining efficient searches as the database grows.

## 3. Input Data

The identification numbers are inserted into the BST in the following order:

A102, A25, A7, B100, B12, A120, B3, A45

## 4. BST Structure

```text
             A102
                \
                A25
               /   \
            A120    A7
                   /  \
                 A45  B100
                         \
                         B12
                           \
                           B3
```

The height of the BST is **6 levels**.

## 5. Inorder Traversal

```text
A102 A120 A25 A45 A7 B100 B12 B3
```

## 6. BST Search vs Linear Search

| ID | BST Comparisons | Linear Comparisons | Result |
|:---:|:---:|:---:|:---:|
| A102 | 1 | 1 | Found |
| A25 | 2 | 2 | Found |
| A7 | 3 | 3 | Found |
| B100 | 4 | 4 | Found |
| B12 | 5 | 5 | Found |
| A120 | 3 | 6 | Found |
| B3 | 6 | 7 | Found |
| A45 | 4 | 8 | Found |
| C99 | 6 | 8 | Not Found |

## 7. Complexity Analysis

### BST Search

- Best Case: O(1)
- Average Case: O(log n)
- Worst Case: O(n)

### Linear Search

- Best Case: O(1)
- Average Case: O(n)
- Worst Case: O(n)

### BST Insertion

- Average Case: O(log n)
- Worst Case: O(n)

### Inorder Traversal

- Time Complexity: O(n)

### Space Complexity

- BST storage: O(n)

## 8. Effect of Insertion Order

The insertion order affects the height of a normal BST.

A favourable insertion order can produce a more balanced tree and provide faster searches.

An unfavourable insertion order can produce a skewed tree. In the worst case, the height can become O(n), causing BST search to approach the performance of Linear Search.

For the given insertion order, the resulting BST has a height of 6 levels.

## 9. Effect of Key Length

The identification numbers have different lengths, such as A7, A25, A45, A102, A120, B3, B12 and B100.

The BST uses lexicographic comparison through `strcmp()`.

Key length does not directly determine the height of the BST. However, comparing longer identification strings may require more character comparisons.

## 10. Suitable Approach for a Growing Database

For a growing database, a balanced search tree is more suitable than Linear Search.

A self-balancing BST such as an AVL Tree or Red-Black Tree can maintain a balanced structure and provide O(log n) search performance.

## 11. Conclusion

The experiment shows that BST Search can require fewer comparisons than Linear Search for several identification numbers.

The performance of a normal BST depends on its structure and insertion order. If the tree becomes skewed, its search performance can degrade to O(n).

Therefore, for a growing government identification database, maintaining a balanced BST is a suitable approach for efficient searching.

## 12. Files Included

- `government_id_bst.c` – C source code
- `input.txt` – Input data
- `output.txt` – Program execution output
- `trace_table.md` – Trace tables
- `complexity_analysis.md` – Complexity analysis
- `comparison_table.md` – BST vs Linear Search comparison
- `README.md` – Project documentation