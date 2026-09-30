# DataStructures

个人学习用的 C++ 数据结构实现，header-only，直接 `#include` 头文件即可使用。

## 数据结构列表

| 数据结构 | 头文件 | 说明 |
|---------|--------|------|
| 树状数组 (BIT) | `BIT/BIT.h` | 支持单点更新、区间查询 |
| 稀疏表 (Sparse Table) | `RMQ/SparseTable.h` | 静态 RMQ，O(1) 查询 |
| 二维稀疏表 | `RMQ/SparseTable2D.h` | 二维静态 RMQ |
| 钩子二叉堆 | `HookBinaryHeap/HookBinaryHeap.h` | 支持自定义回调、索引更新、删除 |