# BST Search vs Linear Search Comparison

## 1. Search Comparison Results

| No. | Identification ID | BST Comparisons | Linear Comparisons | More Efficient |
|:---:|:------------------:|:---------------:|:------------------:|:--------------:|
| 1 | A102 | 1 | 1 | Same |
| 2 | A25 | 2 | 2 | Same |
| 3 | A7 | 3 | 3 | Same |
| 4 | B100 | 4 | 4 | Same |
| 5 | B12 | 5 | 5 | Same |
| 6 | A120 | 3 | 6 | BST |
| 7 | B3 | 6 | 7 | BST |
| 8 | A45 | 4 | 8 | BST |
| 9 | C99 | 6 | 8 | BST |

---

## 2. Performance Analysis

| Search Method | Best Case | Average Case | Worst Case |
|:-------------|:---------:|:------------:|:----------:|
| BST Search | O(1) | O(log n) | O(n) |
| Linear Search | O(1) | O(n) | O(n) |

---

## 3. Observed Comparison

| Identification ID | BST | Linear Search | Difference |
|:-----------------:|----:|--------------:|----------:|
| A102 | 1 | 1 | 0 |
| A25 | 2 | 2 | 0 |
| A7 | 3 | 3 | 0 |
| B100 | 4 | 4 | 0 |
| B12 | 5 | 5 | 0 |
| A120 | 3 | 6 | 3 |
| B3 | 6 | 7 | 1 |
| A45 | 4 | 8 | 4 |
| C99 | 6 | 8 | 2 |

---

## 4. Analysis

The results show that BST search requires fewer comparisons than linear search for A120, B3, A45 and C99.

For A102, A25, A7, B100 and B12, both methods require the same number of comparisons for the given data.

The BST performs efficiently because the search follows only one path from the root instead of checking every element sequentially.

However, the performance of a normal BST depends on its structure. If the tree becomes skewed because of an unfavourable insertion order, its search performance can become O(n).

---

## 5. Conclusion

For the given identification numbers, the BST provides better search performance for several of the selected IDs compared with linear search.

For a growing database, a balanced BST is a more suitable approach because it can provide approximately O(log n) search time on average.