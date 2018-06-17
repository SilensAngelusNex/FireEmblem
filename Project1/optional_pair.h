#pragma once

#include <utility>
#include <optional>

template<typename A, typename B = A>
using optional_pair = std::pair<std::optional<A>, std::optional<B>>;