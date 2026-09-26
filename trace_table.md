| Step | ID Inserted | Comparison Path              | Position      |
| ---: | ----------- | ---------------------------- | ------------- |
|    1 | A102        | —                            | Root          |
|    2 | A25         | A102                         | Right of A102 |
|    3 | A7          | A102 → A25                   | Right of A25  |
|    4 | B100        | A102 → A25 → A7              | Right of A7   |
|    5 | B12         | A102 → A25 → A7 → B100       | Right of B100 |
|    6 | A120        | A102 → A25                   | Left of A25   |
|    7 | B3          | A102 → A25 → A7 → B100 → B12 | Right of B12  |
|    8 | A45         | A102 → A25 → A7              | Left of A7    |


## BST Search vs Linear Search Trace Table

|| No. | Search ID | BST Search Path                   | BST Comparisons | Linear Comparisons | Result    |
| --: | :-------: | --------------------------------- | --------------: | -----------------: | --------- |
|   1 |    A102   | A102                              |               1 |                  1 | Found     |
|   2 |    A120   | A102 → A25 → A120                 |               3 |                  6 | Found     |
|   3 |     B3    | A102 → A25 → A7 → B100 → B12 → B3 |               6 |                  7 | Found     |
|   4 |    A45    | A102 → A25 → A7 → A45             |               4 |                  8 | Found     |
|   5 |    C99    | A102 → A25 → A7 → B100 → B12 → B3 |               6 |                  8 | Not Found |
