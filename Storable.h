#pragma once

#include <concepts>
#include <type_traits>

template<typename T>
concept Storable =
    std::is_default_constructible_v<T> &&
    std::is_move_constructible_v<T>;