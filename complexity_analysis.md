# Complexity Analysis - Government Identification BST

## 1. BST Search Complexity

| Case | Time Complexity | Explanation |
|:---|:---:|:---|
| Best Case | O(1) | The required ID is found at the root. |
| Average Case | O(log n) | The tree is reasonably balanced, so only a small number of levels are searched. |
| Worst Case | O(n) | If the BST becomes skewed, the search may visit every node. |

## 2. Linear Search Complexity

| Case | Time Complexity | Explanation |
|:---|:---:|:---|
| Best Case | O(1) | The required ID is the first element. |
| Average Case | O(n) | About half of the elements may need to be checked. |
| Worst Case | O(n) | All elements may need to be checked. |

## 3. BST Insertion Complexity

| Case | Time Complexity | Explanation |
|:---|:---:|:---|
| Best Case | O(1) | The tree is empty and the first element becomes the root. |
| Average Case | O(log n) | In a reasonably balanced BST, insertion follows the tree height. |
| Worst Case | O(n) | A skewed BST may require traversing all existing nodes. |

## 4. Inorder Traversal Complexity

| Operation | Time Complexity |
|:---|:---:|
| Inorder Traversal | O(n) |

Inorder traversal visits every node exactly once.

## 5. Space Complexity

| Operation | Space Complexity |
|:---|:---:|
| BST Storage | O(n) |
| Recursive Traversal | O(n) in the worst case |

The BST requires O(n) space to store n identification numbers.

## 6. Effect of Insertion Order

The insertion order affects the height of a normal BST.

If the identification numbers are inserted in an order that produces a balanced tree, the height is approximately O(log n), giving efficient search.

If the identification numbers are inserted in an unfavourable order, the tree can become skewed. In that case, the height can become O(n), making BST search similar to linear search.

For the given insertion order:

```text
A102, A25, A7, B100, B12, A120, B3, A45