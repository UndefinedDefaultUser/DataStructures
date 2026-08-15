#pragma once
#include <vector>
#include <utility>
#include <algorithm>
#include <bit>

namespace RMQ {

    template <typename t, typename calculatorFuc> class sparseTable {

        calculatorFuc func;

        std::vector<t> table;

        int n;
        int maxLog;

        int log2(int num) {
            return max(((int)std::bit_width((uint32_t)num)) - 1, 0);
        }

        t getTableVal(int idx, int power) {
            return table[idx * maxLog + power];
        }

        void setTableVal(int idx, int power, t val) {
            table[idx * maxLog + power] = val;
        }

    public:

        static_assert(std::is_invocable_r_v<t, calculatorFuc, t, t>,
            "calculatorFuc must be callable as t(t, t)");

        sparseTable(const std::vector<t>& items, calculatorFuc calculator) :func(calculator) {

            if (n == 0)
                return;
            n = items.size();

            maxLog = log2(n) + 1;

            table = std::vector<t>(n * maxLog);

            for (int i = 0; i < n; i++) {
                setTableVal(i, 0, items[i]);
            }

            for (int power = 1; power < maxLog; power++) {
                for (int i = 0; i + (1 << power) - 1 < n; i++) {
                    setTableVal(
                        i, power,
                        func(getTableVal(i, power - 1),
                            getTableVal(i + (1 << (power - 1)), power - 1)));
                }
            }
        }

        t query(int left, int right) {

            right = std::clamp(right, 0, n - 1);

            left = std::clamp(left, 0, right);

            int len = right - left + 1;

            int log2Len = log2(len);

            return func(getTableVal(left, log2Len),
                getTableVal(right - (1 << (log2Len)) + 1, log2Len));
        }
    };
}