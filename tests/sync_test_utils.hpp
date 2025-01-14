#ifndef REALM_SYNC_TEST_UTILS_HPP
#define REALM_SYNC_TEST_UTILS_HPP

#include <cpprealm/sdk.hpp>

#include <realm/object-store/sync/sync_session.hpp>
#include <realm/object-store/sync/sync_manager.hpp>
#include <realm/object-store/sync/sync_user.hpp>

namespace test {
    inline std::promise<void> wait_for_sync_uploads(const realm::user& user) {
        auto sync_sessions = user.m_user->sync_manager()->get_all_sessions();
        auto session = sync_sessions[0];

        std::promise<void> p;
        session->wait_for_upload_completion([&p](auto ec){
            if (ec) p.set_exception(std::make_exception_ptr(ec));
            else p.set_value();
        });

        return p;
    }

    inline std::promise<void> wait_for_sync_downloads(const realm::user& user) {
        auto sync_sessions = user.m_user->sync_manager()->get_all_sessions();
        auto session = sync_sessions[0];
        std::promise<void> p;
        session->wait_for_download_completion([&p](auto ec) {
            if (ec) p.set_exception(std::make_exception_ptr(ec));
            else p.set_value();
        });

        return p;
    }
}

#endif //REALM_SYNC_TEST_UTILS_HPP
