#ifndef STRING_ALGORITHMS_H
#define STRING_ALGORITHMS_H

void string_algorithms_demo(void);

void naive_string_matching_demo(void);
void naive_string_matching(const char* text, const char* pattern);

void kmp_demo(void);
void kmp_search(const char* text, const char* pattern);
void kmp_visualization(const char* text, const char* pattern);

void rabin_karp_demo(void);
void rabin_karp_search(char* text, char* pattern, int q);
void rabin_karp_visualization(char* text, char* pattern, int q);

// Suffix Array & Kasai's LCP
void suffix_array_demo(void);
int* build_suffix_array(const char* txt, int n);
int* build_lcp_array(const char* txt, int* suffix_arr, int n);
void find_longest_repeated_substring(const char* txt, int n, char* output);
void visualize_suffix_array(const char* txt, int n, int* suffix_arr, int* lcp_arr);

#endif // STRING_ALGORITHMS_H