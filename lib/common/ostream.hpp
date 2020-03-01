// Copyright © 2020 Giorgio Audrito. All Rights Reserved.

/**
 * @file ostream.hpp
 * @brief Implementation of output stream operations for standard and FCPP classes.
 */

#ifndef FCPP_COMMON_OSTREAM_H_
#define FCPP_COMMON_OSTREAM_H_

#include <map>
#include <ostream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "lib/common/multitype_map.hpp"
#include "lib/common/random_access_map.hpp"
#include "lib/common/tagged_tuple.hpp"


/**
 * @brief Namespace of the C++ standard library.
 */
namespace std {
    //! @brief Printing vectors.
    template <typename T>
    std::ostream& operator<<(std::ostream& o, const std::vector<T>& m) {
        o << "[";
        bool first = true;
        for (const auto& x : m) {
            if (not first) o << ", ";
            o << x;
            first = false;
        }
        o << "]";
        return o;
    }

    //! @brief Printing ordered sets.
    template <typename T>
    std::ostream& operator<<(std::ostream& o, const std::set<T>& m) {
        o << "{";
        bool first = true;
        for (const auto& x : m) {
            if (not first) o << ", ";
            o << x;
            first = false;
        }
        o << "}";
        return o;
    }

    //! @brief Printing unordered sets.
    template <typename T>
    std::ostream& operator<<(std::ostream& o, const std::unordered_set<T>& m) {
        o << "{";
        bool first = true;
        for (const auto& x : m) {
            if (not first) o << ", ";
            o << x;
            first = false;
        }
        o << "}";
        return o;
    }

    //! @brief Printing ordered maps.
    template <typename K, typename V>
    std::ostream& operator<<(std::ostream& o, const std::map<K,V>& m) {
        o << "{";
        bool first = true;
        for (const auto& x : m) {
            if (not first) o << ", ";
            o << x.first << ":" << x.second;
            first = false;
        }
        o << "}";
        return o;
    }

    //! @brief Printing unordered maps.
    template <typename K, typename V>
    std::ostream& operator<<(std::ostream& o, const std::unordered_map<K,V>& m) {
        o << "{";
        bool first = true;
        for (const auto& x : m) {
            if (not first) o << ", ";
            o << x.first << ":" << x.second;
            first = false;
        }
        o << "}";
        return o;
    }
}


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {


//! @brief Namespace containing objects of common use.
namespace common {
    //! @brief Printing multitype maps in dictionary format.
    template <typename T, typename... Ts>
    std::ostream& operator<<(std::ostream& o, const multitype_map<T, Ts...>& m) {
        o << "(";
        m.print(o, arrowhead_tuple);
        o << ")";
        return o;
    }

    //! @brief Printing random access maps.
    template <typename K, typename V>
    std::ostream& operator<<(std::ostream& o, const random_access_map<K,V>& m) {
        o << "{";
        bool first = true;
        for (const auto& x : m) {
            if (not first) o << ", ";
            o << x.first << ":" << x.second;
            first = false;
        }
        o << "}";
        return o;
    }

    //! @brief Printing tagged tuples in dictionary format.
    template <typename S, typename T>
    std::ostream& operator<<(std::ostream& o, const tagged_tuple<S,T>& t) {
        o << "(";
        t.print(o, arrowhead_tuple);
        o << ")";
        return o;
    }
}


}


#endif // FCPP_COMMON_OSTREAM_H_
