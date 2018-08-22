#pragma once

#include <string>
#include <array>

#define EPSILON 0.000001

class NotImplementedException
        : public std::exception {

public:

    // Construct with given error message:
    NotImplementedException(const char *error = "Functionality not yet implemented!") {
        errorMessage = error;
    }

    // Provided for compatibility with std::exception.
    const char *what() const noexcept {
        return errorMessage.c_str();
    }

private:

    std::string errorMessage;
};