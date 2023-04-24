//
// Created by murph on 22.04.23.
//
#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#define UNUSED(x) (void)x;

template<typename Arithmetic,
        std::enable_if_t<std::is_integral<Arithmetic>::value, bool> = true>
void print_ip(const Arithmetic& val){
    size_t octets_number = sizeof(Arithmetic);
    for (size_t i = octets_number; i--;)
    {
        std::cout << (val >> (i << 3) & 0xFF);
        if (i > 0) {
            std::cout << '.';
        }
    }

    std::cout << std::endl;
}

template<typename String,
        std::enable_if_t<std::is_same<String, std::string>::value, bool> = true>
void print_ip(const String& string){
    std::cout << string << std::endl;
}

template<template<typename, typename> class Container, typename T, typename Allocator,
        std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T>>::value
        || std::is_same<Container<T, Allocator>, std::vector<T>>::value , bool> = true>
void print_ip(const Container<T, Allocator>& container){
    for (auto i:container) {
        std::cout << i;
        if (i != container.back())
            std::cout << ".";
    };
    std::cout << std::endl;
}

template <typename Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple& t) {
        TuplePrinter<Tuple, N-1>::print(t);
        std::cout << "." << std::get<N-1>(t);
    }
};

template <typename Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple& t) {
        std::cout << std::get<0>(t);
    }
};

template <typename ...T>
void print_ip(const std::tuple<T...>&tuple){
    TuplePrinter<decltype(tuple), sizeof...(T)>::print(tuple);
}