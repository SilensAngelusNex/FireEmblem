#pragma once

#include <utility>
#include <optional>

template<typename A, typename B>
using optional_pair = std::pair<std::optional<A>, std::optional<B>>;