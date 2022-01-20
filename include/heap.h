#pragma once
#include <stdlib.h>
#include "dynamic_array.h"

template<typename T>
inline T* heap_alloc(size_t size) {
    return (T*)malloc(size * sizeof(T));
}

template<typename T>
inline T* heap_realloc(T* ptr, size_t size) {
    return (T*)realloc(ptr, size * sizeof(T));
}

template<typename T>
dynamic_array<T> create_heap_array() {
    return { .size = 0, .data = nullptr };
}

template<typename T>
dynamic_array<T> create_heap_array(size_t size) {
    return { .size = 0, .data = heap_alloc<T>(size) };
}

template<typename T>
void push_to_heap_array(dynamic_array<T>* self, T elem) {
    self->data = heap_realloc<T>(self->data, ++self->size);
    memcpy(&self->data[self->size - 1], &elem, sizeof(T));
}

template<typename T>
T pop_from_heap_array(dynamic_array<T>* self) {
    T elem = self->data[self->size - 1];
    self->data = heap_realloc<T>(self->data, --self->size);
    return elem;
}

template<typename T>
void disown_heap_array(dynamic_array<T>* self) {
    self->data = nullptr;
    self->size = 0;
}

template<typename T>
void destroy_heap_array(dynamic_array<T>* self) {
    free((void*)self->data);
    self->data = nullptr;
    self->size = 0;
}