#pragma once

typedef long long lld;

extern "C" {
void process_top(int n, int l, int m,
		lld *mat1, lld *mat2, lld *mat3, bool *fallback);
}