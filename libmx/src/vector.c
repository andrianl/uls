#include "libmx.h"
#include "vector.h"

void mx_assign_vector(t_vector *v, size_t count, const void *item)
{
    if (v && count && item)
    {
        if (count > v->cap)
        {
            mx_clear_vector(v);
            for (size_t i = 0; i < count; ++i)
                mx_push_backward(v, item);
        }
        else
        {
            uint8_t *end = v->arr + count * v->bytes;

            for (uint8_t *i = v->arr; i < end; i += v->bytes)
                mx_memcpy(i, item, v->bytes);
        }
    }
}

void *mx_at(t_vector *v, size_t pos)
{
    return v && v->arr && pos < v->size ? v->arr + (v->bytes * pos) : NULL;
}

void mx_clear_vector(t_vector *v)
{
    if (v && v->size)
    {
        v->cap = MX_VECTOR_DEFAULT_SIZE;
        v->size = 0;
        if (v->size > MX_VECTOR_DEFAULT_SIZE * 64)
        {
            if (MX_MALLOC_SIZE(v->arr))
                free(v->arr);
            v->arr = malloc(v->bytes * MX_VECTOR_DEFAULT_SIZE);
        }
    }
}

t_vector *mx_copy_vector(t_vector *copy)
{
    t_vector *v = copy ? (t_vector *)malloc(sizeof(t_vector)) : NULL;

    if (v)
    {
        v->cap = copy->cap;
        v->size = copy->size;
        v->bytes = copy->bytes;
        v->arr = copy->arr ? mx_memdup(copy->arr, v->cap * v->bytes) : NULL;
    }
    return v;
}

t_vector *mx_create_vector(size_t size, size_t bytes)
{
    t_vector *v = bytes > 0 ? (t_vector *)malloc(sizeof(t_vector)) : NULL;

    if (v)
    {
        size_t cap = MX_VECTOR_DEFAULT_SIZE;

        for (size_t max = SIZE_MAX / 16; cap < size && cap < max; cap *= 2)
            ;
        v->cap = cap;
        v->size = size;
        v->bytes = bytes;
        v->arr = malloc(bytes * cap);
    }
    return v;
}

void mx_delete_vector(t_vector *v)
{
    if (v)
    {
        if (MX_MALLOC_SIZE(v->arr))
            free(v->arr);
        if (MX_MALLOC_SIZE(v))
            free(v);
    }
}

void *mx_end(t_vector *v)
{
    return v && v->arr && v->size ? v->arr + (v->bytes * v->size) : NULL;
}

void mx_erase(t_vector *v, size_t pos)
{
    if (v && v->size)
    {
        if (pos < v->size - 1)
            mx_memmove(v->arr + pos,
                       v->arr + pos + 1,
                       (v->size - pos - 1) * v->bytes);
        --v->size;
        if ((float)v->cap / v->size > 4 && v->cap > MX_VECTOR_DEFAULT_SIZE)
        {
            v->cap /= 2;
            v->arr = mx_realloc(v->arr, v->bytes * v->cap);
        }
    }
}

void mx_foreach_vector(t_vector *v, void (*f)(void *))
{
    if (v && v->arr && v->size && f)
    {
        uint8_t *end = v->arr + v->size * v->bytes;

        for (uint8_t *i = v->arr; i < end; i += v->bytes)
            f(i);
    }
}

void mx_foreach_vector_reverse(t_vector *v, void (*f)(void *))
{
    if (v && v->arr && v->size && f)
    {
        uint8_t *start = v->arr + (v->size - 1) * v->bytes;

        for (uint8_t *i = start; i >= v->arr; i -= v->bytes)
            f(i);
    }
}

void *mx_get_back(t_vector *v)
{
    return v && v->arr && v->size ? v->arr + (v->bytes * (v->size - 1)) : NULL;
}

void *mx_get_front(t_vector *v)
{
    return v && v->size ? v->arr : NULL;
}

void mx_insert(t_vector *v, size_t pos, const void *item)
{
    if (v && item && pos <= v->size)
    {
        uint8_t *ppos = v->arr + pos * v->bytes;

        if (v->size == v->cap)
        {
            v->cap *= 2;
            v->arr = mx_realloc(v->arr, v->bytes * v->cap);
        }
        if (pos < v->size)
            mx_memmove(v->arr + pos + 1, v->arr + pos,
                       (v->size - pos - 1) * v->bytes);
        mx_memcpy(ppos, item, v->bytes);
        ++v->size;
    }
}

void mx_pop_backward(t_vector *v)
{
    if (v && v->arr && v->size)
    {
        --v->size;
        if ((float)v->cap / v->size > 4 && v->cap > MX_VECTOR_DEFAULT_SIZE)
        {
            v->cap /= 2;
            v->arr = mx_realloc(v->arr, v->bytes * v->cap);
        }
    }
}

void mx_push_backward(t_vector *v, const void *item)
{
    if (v && v->arr && item)
    {
        if (v->size == v->cap)
        {
            v->cap *= 2;
            v->arr = mx_realloc(v->arr, v->bytes * v->cap);
        }
        mx_memcpy(v->arr + (v->size * v->bytes), item, v->bytes);
        ++v->size;
    }
}

void mx_reverse_vector(t_vector *v)
{
    if (v && v->size && v->arr)
    {
        uint8_t *i = v->arr;
        uint8_t *j = v->arr + (v->size - 1) * v->bytes;

        for (size_t b = v->bytes; i < j; i += b, j -= b)
            mx_swap(i, j, b);
    }
}
