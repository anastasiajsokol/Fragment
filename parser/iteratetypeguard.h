/**
 *      @file parser/iteratetypeguard
 *      @brief use to restrict generic template type to only apply if the iterater type of that container is convertable to a specific target type
 *      @author Anastasia Sokol
**/

#ifndef PARSER_ITERATETYPEGUARD_H
#define PARSER_ITERATETYPEGUARD_H

#include <type_traits>  // defines std::declval used to get type of .begin() return, std::is_convertible_v used to test convertability, and std::enable_if_t used to restrict generic type
#include <iterator>     // defines std::iterator_traits used to get iterater value type

/**
 *  @brief add to template to restrict a generic type to be a container that is iterable returning a type that is convertable to a target value type
 *  @param container_type the container type you want to validate
 *  @param iterate_value_type the target (non-const) type you want the iterater to return
**/
#define only_if_iterater_type(container_type, iterate_value_type)  typename = std::enable_if_t<std::is_convertible_v<typename std::iterator_traits<decltype(std::declval<container_t>().begin())>::value_type, iterate_value_type>>

#endif