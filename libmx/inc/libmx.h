#ifndef __LIBMX_H__
#define __LIBMX_H__

// ==================== typedefs =====================
typedef unsigned char ubyte;
typedef char byte;

// ===================== defines ======================

// ------------ cross platform ------------
#if defined(__APPLE__)
#include <malloc/malloc.h>
#define mx_malloc_size(x) malloc_size(x)
#elif defined(_WIN64) || defined(_WIN32)
#include <malloc.h>
#define mx_malloc_size(x) _msize(x)
#elif defined(__linux__)
#include <malloc.h>
#define mx_malloc_size(x) malloc_usable_size(x)
#endif

// ===================== macros =====================

#define MX_MIN(x, y, type) (((type)x) < ((type)y) ? (x) : (y))
#define MX_MAX(x, y, type) (((type)x) > ((type)y) ? (x) : (y))

#define size(x) sizeof(x) / sizeof(x[0])

// ===================== includes =====================
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

// ===================== structs =====================

typedef struct s_list
{
  void *data;
  struct s_list *next;
} t_list;

typedef unsigned char t_ftbyte;
//-------- READ_LINE --------//
//-------- STRUCTURE --------//

typedef struct s_fd
{
  bool eof;
  int fd;
  char *str;
  struct s_fd *next;
} t_fd;

// ===================== Functions =====================

// ===================== UTILS =====================

// ---------------- print ----------------
void mx_printchar(char c);
void mx_printstr(const char *s);
void mx_print_strarr(char **arr, const char *delim);
void mx_printint(int n);
void mx_print_unicode(wchar_t c);

// ---------------- convert ----------------
char *mx_nbr_to_hex(unsigned long nbr);
char *mx_itoa(int number);
unsigned long mx_hex_to_nbr(const char *hex);

// ---------------- math ----------------
double mx_pow(double n, unsigned int pow);
int mx_sqrt(int x);

// ---------------- sort and search ----------------
int mx_binary_search(char **arr, int size, const char *s, int *count);
int mx_bubble_sort(int *arr, int size);
int mx_quicksort(int *arr, int left, int right);

// ---------------- function pointer ----------------
void mx_foreach(int *arr, int size, void (*f)(int));

// ---------------- delete arrays ----------------
void mx_del_intarr(int **arr, int num);
void mx_del_strarr(char ***arr);
void mx_del_strarr(char ***arr);

// ==================== STRING ====================

// ------------ format string ------------
char *mx_del_extra_spaces(const char *str);
char *mx_replace_substr(const char *str, const char *sub, const char *replace);
char *mx_strtrim(const char *str);
char **mx_strsplit(const char *s, char c);

// ------- malloc & free string -------
char *mx_strnew(const int size);
void mx_strdel(char **str);

// ---------- string utils  ----------
char *mx_strcat(char *restrict s1, const char *restrict s2);
char *mx_strcpy(char *dst, const char *src);
char *mx_strdup(const char *s1);
char *mx_strndup(const char *s1, size_t n);
char *mx_strjoin(char const *s1, char const *s2);
char *mx_strncpy(char *dst, const char *src, int len);
char *mx_strstr(const char *haystack, const char *needle);
int mx_strcmp(const char *s1, const char *s2);
int mx_strncmp(register const char *s1, register const char *s2,
               register size_t n);
int mx_strlen(const char *s);

// -------------- useful functions  --------------
int mx_count_substr(const char *str, const char *sub);
int mx_count_words(const char *str, char delimiter);
int mx_get_char_index(const char *str, char c);
int mx_get_substr_index(const char *str, const char *sub);
int mx_check_substr(const char *src, const char *sub);

// ----------- swap & reverse ---------
void mx_str_reverse(char *s);
void mx_swap_char(char *s1, char *s2);

// --------- files -----------
char *mx_file_to_str(const char *filename);
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd);

// ======================= MEMORY ========================
int mx_memcmp(const void *s1, const void *s2, size_t n);

void *mx_memchr(const void *s, int c, size_t n);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);
void *mx_memmem(const void *big, size_t big_len, const void *little,
                size_t little_len);
void *mx_memset(void *b, int c, size_t len);
void *mx_memrchr(const void *s, int c, size_t n);
void *mx_memmove(void *dst, const void *src, size_t len);
void *mx_realloc(void *ptr, size_t size);

// ======================== LIST ========================
int mx_list_size(t_list *list);

t_list *mx_create_node(void *data);
t_list *mx_sort_list(t_list *list, bool (*cmp)(void *, void *));

void mx_pop_back(t_list **list);
void mx_pop_front(t_list **list);
void mx_push_back(t_list **list, void *data);
void mx_push_front(t_list **list, void *data);
void mx_swap_node(void **s1, void **s2);

// ======================== OPTIONAL ========================
bool mx_isalpha(int c);
bool mx_isdigit(int c);
bool mx_islower(int c);
bool mx_isspace(char c);
bool mx_isupper(int c);
void swap(int *xp, int *yp);
void swapn(void *v1, void *v2, int size);

char *mx_concat_words(char **words);
char *mx_strchr(const char *s, int c);

int mx_atoi(const char *str);
int mx_check_substr(const char *src, const char *sub);
int mx_factorial_iter(int n);
int mx_gcd(int a, int b);
int mx_lcm(int a, int b);
int mx_tolower(int c);
int mx_toupper(int c);

int mx_min(int a, int b);
int mx_max(int a, int b);
int mx_abs(int a);
unsigned long mx_mod(int num);
float mx_powf(float base, int exp);

void mx_only_printable(void);
void mx_print_arr_int(const int *arr, int size);
void mx_printerr(const char *s);

#endif // __LIBMX_H__
