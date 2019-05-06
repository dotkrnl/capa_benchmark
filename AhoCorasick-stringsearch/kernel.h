#pragma once

void AhoCorasick_search(
        int substring_length, char *substrings, char *query,
        int *substring_indexes, int *query_indexes);
