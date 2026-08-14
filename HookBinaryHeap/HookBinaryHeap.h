#pragma once
#include <vector>
#include <utility>

namespace HookBinaryHeap
{

    struct NoOp
    {
        template <typename T>
        void operator()(T, int) const {}
    };

    template <typename t, typename compFunc, typename onSwapBeforeFunc,
              typename onPopBeforeFunc>
    class heap
    {

        [[no_unique_address]] compFunc comp;

        [[no_unique_address]] onSwapBeforeFunc onSwapBefore;

        [[no_unique_address]] onPopBeforeFunc onPopBefore;

        void check_down(int idx, int n)
        {

            if (idx > (n - 2) / 2 || idx < 0)
                return;

            while (true)
            {

                int newIdx = idx;

                int child = idx * 2 + 1;

                if (child < n && comp(items[child], items[newIdx]))
                    newIdx = child;

                child = idx * 2 + 2;

                if (child < n && comp(items[child], items[newIdx]))
                    newIdx = child;

                if (idx != newIdx)
                {
                    onSwapBefore(items[newIdx], idx);
                    onSwapBefore(items[idx], newIdx);
                    std::swap(items[newIdx], items[idx]);
                    idx = newIdx;
                }
                else
                    return;
            }
        }

        void check_down(int idx)
        {
            check_down(idx, size());
        }

        void check_up(int idx)
        {

            if (idx >= size() || idx <= 0)
                return;

            while (true)
            {
                int pIdx = (idx - 1) / 2;

                if (pIdx >= 0 && pIdx != idx && comp(items[idx], items[pIdx]))
                {
                    onSwapBefore(items[pIdx], idx);

                    onSwapBefore(items[idx], pIdx);

                    std::swap(items[pIdx], items[idx]);

                    idx = pIdx;
                }
                else
                    return;
            }
        }

        std::vector<t> items;

    public:
        heap(compFunc comp, onSwapBeforeFunc onSwapBefore, onPopBeforeFunc onPopBefore)
            : comp(comp), onSwapBefore(onSwapBefore), onPopBefore(onPopBefore) {}

        void insert(t val)
        {

            items.push_back(val);

            onSwapBefore(val, size() - 1);

            check_up(size() - 1);
        }

        void pop() { del(0); }

        void del(int idx)
        {

            if (idx < 0 || idx >= size())
                return;

            onSwapBefore(items[size() - 1], idx);

            onPopBefore(items[idx], idx);

            std::swap(items[idx], items[size() - 1]);

            items.resize(size() - 1);

            int pIdx = ((idx - 1)) / 2;

            if (pIdx < size() && comp(items[idx], items[pIdx]))
                check_up(idx);
            else
                check_down(idx);
        }

        void update(int idx, t newT)
        {
            if (idx < 0 || idx >= size())
                return;

            items[idx] = newT;

            int pIdx = ((idx - 1)) / 2;

            if (pIdx < size() && comp(items[idx], items[pIdx]))
                check_up(idx);
            else
                check_down(idx);
        }

        t top() const { return items[0]; }

        int size() const { return items.size(); }
    };

    struct heapMaker
    {

        template <typename T, typename Comp, typename OnSwapBefore = NoOp,
                  typename OnPopBefore = NoOp>
        static heap<T, Comp, OnSwapBefore, OnPopBefore> make_heap(Comp comp, OnSwapBefore onSwapBefore = {},
                                                                  OnPopBefore onPopBefore = {})
        {
            return heap<T, Comp, OnSwapBefore, OnPopBefore>(comp, onSwapBefore, onPopBefore);
        }
    };
}