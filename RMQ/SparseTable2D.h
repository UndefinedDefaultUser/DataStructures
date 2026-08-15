#pragma once
#include <vector>
#include <utility>
#include <algorithm>
#include <bit>

namespace RMQ {

	struct vector2D {
		int x;
		int y;

		vector2D(int x, int y) : x(x), y(y) {}
	};

	template <typename t, typename calculatorFuc>
	class sparseTable2D {
		calculatorFuc func;

		std::vector<t> table;

		int n;
		int maxLogN;
		int m;
		int maxLogM;

		int log2(int num) {
			return std::max(((int)std::bit_width((uint32_t)num)) - 1, 0);
		}

		t getTableVal(int y, int yPower, int x, int xPower) {
			return table[((y * maxLogN + yPower) * m + x) * maxLogM + xPower];
		}

		void setTableVal(int y, int yPower, int x, int xPower, t val) {
			table[((y * maxLogN + yPower) * m + x) * maxLogM + xPower] = val;
		}


	public:

		static_assert(std::is_invocable_r_v<t, calculatorFuc, t, t>,
			"calculatorFuc must be callable as t(t, t)");

		sparseTable2D(const std::vector<std::vector<t>>& matrix, calculatorFuc calculator):func(calculator) {

			n = matrix.size();

			if (n == 0)
				return;

			maxLogN = log2(n) + 1;
			m = matrix[n - 1].size();
			maxLogM = log2(m) + 1;

			table = std::vector<t>(n * maxLogN * m * maxLogM);

			for (int y = 0; y < n; y++) {

				auto& items = matrix[y];

				for (int x = 0; x < m; x++) {
					setTableVal(y, 0, x, 0, items[x]);
				}

				for (int xPower = 1; xPower < maxLogM; xPower++) {

					for (int x = 0; x + (1 << xPower) <= m; x++) {

						setTableVal(y, 0, x, xPower, func(
							getTableVal(y, 0, x, xPower - 1),
							getTableVal(y, 0, x + (1 << (xPower - 1)), xPower - 1)
						));

					}

				}
			}

			for (int yPower = 1; yPower < maxLogN; yPower++) {

				for (int y = 0; y + (1 << yPower) <= n; y++) {

					for (int x = 0; x < m; x++) {

						for (int xPower = 0; x + (1 << xPower) <= m; xPower++) {
							setTableVal(y, yPower, x, xPower, func(
								getTableVal(y, yPower - 1, x, xPower),
								getTableVal(y + (1 << (yPower - 1)), yPower - 1, x, xPower)
							));
						}

					}

				}

			}
		}

		int query(vector2D min, vector2D max) {

			max.x = std::clamp(max.x, 0, m - 1);
			max.y = std::clamp(max.y, 0, n - 1);

			min.x = std::clamp(min.x, 0, max.x);
			min.y = std::clamp(min.y, 0, max.y);

			int h = (max.y - min.y) + 1;
			int w = (max.x - min.x) + 1;

			return func(
				func(
					getTableVal(min.y, log2(h), min.x, log2(w)),
					getTableVal(min.y, log2(h), max.x - (1 << log2(w)) + 1, log2(w))
				),
				func(
					getTableVal(max.y - (1 << log2(h)) + 1, log2(h), min.x, log2(w)),
					getTableVal(max.y - (1 << log2(h)) + 1, log2(h), max.x - (1 << log2(w)) + 1, log2(w))
				)
			);
		}
	};






	
}