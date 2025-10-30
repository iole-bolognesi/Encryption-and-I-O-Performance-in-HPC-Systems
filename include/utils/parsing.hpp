/**
 * @file Parsing.hpp
 * @brief This module declares parsing utilities to convert a string 
 * to a CiperType enum
 * @author Iole Bolognesi
 *
 * This module declares a function that maps a cipher name to the
 * corresponding CipherType enum. 
 */
#ifndef HEADER_PARSING
#define HEADER_PARSING

#include <optional>       
#include <string_view>    
#include <iostream>

#include "CipherFactory.hpp"

CipherType getEnumFromString(std::string_view input, int rank);

#endif