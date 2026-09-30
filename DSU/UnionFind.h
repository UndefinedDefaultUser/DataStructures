#pragma once
#include <vector>

namespace DSU {
	class UnionFind {
		std::vector<size_t> items;
		std::vector<size_t> ranks;

	public:
		UnionFind() {}

		UnionFind(size_t n) { resize(n); }

		void resize(size_t n) {
			items.resize(n);
			ranks.resize(n);
			reset();
		}

		size_t find(size_t idx) {
			if (idx >= items.size())
				return -1;

			if (items[idx] == idx)
				return idx;

			items[idx] = find(items[idx]);
			return items[idx];
		}

		bool unionItem(size_t a, size_t b) {

			if (a >= items.size() || b >= items.size() )
				return 0;

			int pa = find(a);
			int pb = find(b);

			if (pa == pb)
				return 0;

			if (ranks[pa] > ranks[pb]) {
				items[pb] = pa;
			}
			else if (ranks[pa] < ranks[pb]) {
				items[pa] = pb;
			}
			else {
				items[pa] = pb;
				ranks[pb]++;
			}

			return 1;
		}

		void reset() {
			for (size_t i = 0; i < items.size(); i++) {
				items[i] = i;
				ranks[i] = 0;
			}
		}
	};
}