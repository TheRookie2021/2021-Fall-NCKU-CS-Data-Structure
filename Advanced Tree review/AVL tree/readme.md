## 關於AVL
- 一種BST
- imbalanced case: LL, LR, RR, RL
- LL: right rotation
- LR: left rotation on child, then right rotation on imbalanced parent
- RR: left rotation
- RL: right rotation on child, then left rotation on imbalanced parent
## 關於C++
- 不同形式的Tree 操作方式
    - without class
    - class:
        - only node struct (the root is not in the class): https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
        - the whole tree and the related function: http://www.hamedkiani.com/coding-interview/a-class-implementation-of-binary-search-tree-in-c, https://stackoverflow.com/questions/1864032/in-cpp-file-defining-methods-with-class-foo-void-method-instead-of
        
    - if i declare root of a tree in a class, how can i manipulate that tree?
        - pass by value?
        - pass by reference?
