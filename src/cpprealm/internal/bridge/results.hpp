#ifndef CPP_REALM_BRIDGE_RESULTS_HPP
#define CPP_REALM_BRIDGE_RESULTS_HPP

#include <cstddef>
#include "cpprealm/internal/bridge/obj.hpp"

namespace realm {
    class Results;
}
namespace realm::internal::bridge {
    struct realm;
    struct table;
    struct query;
    struct notification_token;
    struct obj;
    struct collection_change_set;

    struct results {
        results(const Results&); //NOLINT(google-explicit-constructor)
        size_t size();
        [[nodiscard]] realm get_realm() const;
        [[nodiscard]] table get_table() const;
        results(const realm&, const query&);
        notification_token add_notification_callback(std::shared_ptr<collection_change_callback>&&);
    private:
        template <typename T>
        friend T get(results&, size_t);
#ifdef __i386__
        std::aligned_storage<496, 4>::type m_results[1];
#elif __x86_64__
    #if defined(__clang__)
        std::aligned_storage<896, 8>::type m_results[1];
    #elif defined(__GNUC__) || defined(__GNUG__)
        std::aligned_storage<912, 8>::type m_results[1];
    #endif
#elif __arm__
        std::aligned_storage<568, 8>::type m_results[1];
#elif __aarch64__
        std::aligned_storage<896, 8>::type m_results[1];
#endif
    };

    template <typename T>
    T get(results&, size_t);
    template <>
    obj get(results&, size_t);
}

#endif //CPP_REALM_BRIDGE_RESULTS_HPP
