#include <cpprealm/internal/bridge/utils.hpp>
#include <cpprealm/internal/bridge/sync_error.hpp>

#include <realm/sync/config.hpp>

namespace realm::internal::bridge {
#ifdef __i386__
    static_assert(SizeCheck<80, sizeof(SyncError)>{});
    static_assert(SizeCheck<4, alignof(SyncError)>{});
#elif __x86_64__
    #if defined(__clang__)
    static_assert(SizeCheck<152, sizeof(SyncError)>{});
    #elif defined(__GNUC__) || defined(__GNUG__)
    static_assert(SizeCheck<176, sizeof(SyncError)>{});
    #endif
    static_assert(SizeCheck<8, alignof(SyncError)>{});
#elif __arm__
    static_assert(SizeCheck<80, sizeof(SyncError)>{});
    static_assert(SizeCheck<4, alignof(SyncError)>{});
#elif __aarch64__
    static_assert(SizeCheck<152, sizeof(SyncError)>{});
    static_assert(SizeCheck<8, alignof(SyncError)>{});
#endif
    std::string sync_error::message() const {
        return reinterpret_cast<const SyncError*>(m_error)->message;
    }

    std::error_code sync_error::error_code() const {
        return reinterpret_cast<const SyncError*>(m_error)->error_code;
    }

    bool sync_error::is_client_error() const {
        return reinterpret_cast<const SyncError*>(m_error)->is_client_error();
    }

    bool sync_error::is_client_reset_requested() const {
        return reinterpret_cast<const SyncError*>(m_error)->is_client_reset_requested();
    }

    bool sync_error::is_connection_level_protocol_error() const {
        return reinterpret_cast<const SyncError*>(m_error)->is_connection_level_protocol_error();
    }

    bool sync_error::is_fatal() const {
        return reinterpret_cast<const SyncError*>(m_error)->is_fatal;
    }

    bool sync_error::is_session_level_protocol_error() const {
        return reinterpret_cast<const SyncError*>(m_error)->is_session_level_protocol_error();
    }

    sync_error::sync_error(realm::SyncError &&v) {
        new (&m_error) SyncError(std::move(v));
    }
}
