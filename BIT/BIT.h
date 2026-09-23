#pragma once
#include <vector>
namespace fenwick {
    class BIT {

        std::vector<int64_t> tree;

        int lowbit(int num) { return num & (~num + 1); }

    public:
        BIT(size_t size) : tree(std::vector<int64_t>(size + 1, 0)) {};

        //query [l,r] sum
        int64_t query(int l, int r) { return query(r) - query(l - 1); }

        //query [0,r) sum
        int64_t query(int r) {
            int64_t sum = 0;
            for (int i = r; i > 0; i -= lowbit(i)) {
                sum += tree[i];
            }
            return sum;
        }

        void add(int idx, int64_t val) {
            for (int i = idx; i < tree.size(); i += lowbit(i)) {
                tree[i] += val;
            }
        }
    };
}