#pragma once

#include <exception>
#include <iostream>
#include <string>

namespace MP
{

enum class Error_action { ignore, throwing, terminating, logging };    // error-handling alternatives

constexpr Error_action default_Error_action = Error_action::throwing;  // a default

enum class Error_code { range_error, length_error, logic_error };                   // individual errors

std::string error_code_name[] { "range error", "length error" };            // names of individual errors

template<Error_action action = default_Error_action, class C>
constexpr void Expect(C cond, Error_code x) // take "action" if the expected condition "cond" doesn't hold
{
        if constexpr (action == Error_action::logging)
            if (!cond()) std::cerr << "Expect() failure: " << int(x) << ' ' << error_code_name[int(x)] << '\n';
        if constexpr (action == Error_action::throwing)
            if (!cond()) throw x;
        if constexpr (action == Error_action::terminating)
            if (!cond()) std::terminate();
        // or no action
}

} // namespace
