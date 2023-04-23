//
// Created by murph on 22.04.23.
//
#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#define UNUSED(x) (void)x;

template<typename Integer,
        std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
void print_ip(const Integer& integer){
    std::cout << integer << std::endl;
}

template<typename String,
        std::enable_if_t<std::is_same<String, std::string>::value, bool> = true>
void print_ip(const String& string){
    std::cout << string << std::endl;
}

template<template<typename, typename> class Container, typename T, typename Allocator,
        std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T>>::value
        || std::is_same<Container<T, Allocator>, std::vector<T>>::value, bool> = true>
void print_ip(const Container<T, Allocator>& container){
    UNUSED(container)
    std::cout << "list" << std::endl;
}

template<typename Tuple, std::size_t I = 0>
struct tuple_element_type {
    using type = typename std::tuple_element<I, Tuple>::type;
};


//TODO как то неоч выгляди для тюпла (по факту специализируем для всего чего угодно, в том числе и тьюпла
// засунь суда мапу и бан
template<typename... Args>
void print_ip(std::tuple<Args...>){

    std::cout << "tuple" << std::endl;
}