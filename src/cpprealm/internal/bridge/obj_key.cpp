#include <cpprealm/internal/bridge/obj_key.hpp>
#include <cpprealm/internal/bridge/utils.hpp>

#include <realm/obj.hpp>

namespace realm::internal::bridge {
#ifdef __i386__
    static_assert(SizeCheck<8, sizeof(ObjKey)>{});
    static_assert(SizeCheck<4, alignof(ObjKey)>{});
#elif __x86_64__
    static_assert(SizeCheck<8, sizeof(ObjKey)>{});
    static_assert(SizeCheck<8, alignof(ObjKey)>{});
#elif __arm__
    static_assert(SizeCheck<8, sizeof(ObjKey)>{});
    static_assert(SizeCheck<8, alignof(ObjKey)>{});
#elif __aarch64__
    static_assert(SizeCheck<8, sizeof(ObjKey)>{});
    static_assert(SizeCheck<8, alignof(ObjKey)>{});
#endif

    obj_key::obj_key() {
        new (&m_obj_key) ObjKey();
    }

    obj_key::obj_key(int64_t v) {
        new (&m_obj_key) ObjKey(v);
    }

    obj_key::obj_key(const ObjKey& v) {
        new (&m_obj_key) ObjKey(v);
    }

    obj_key::operator ObjKey() const {
        return *reinterpret_cast<const ObjKey*>(m_obj_key);
    }

    bool operator==(obj_key const& lhs, obj_key const& rhs) {
        return static_cast<ObjKey>(lhs) == static_cast<ObjKey>(rhs);
    }

#ifdef __i386__
    static_assert(SizeCheck<12, sizeof(ObjLink)>{});
    static_assert(SizeCheck<4, alignof(ObjLink)>{});
#elif __x86_64__
    static_assert(SizeCheck<16, sizeof(ObjLink)>{});
    static_assert(SizeCheck<8, alignof(ObjLink)>{});
#elif __arm__
    static_assert(SizeCheck<16, sizeof(ObjLink)>{});
    static_assert(SizeCheck<8, alignof(ObjLink)>{});
#elif __aarch64__
    static_assert(SizeCheck<16, sizeof(ObjLink)>{});
    static_assert(SizeCheck<8, alignof(ObjLink)>{});
#endif

    obj_link::obj_link() {
        new (&m_obj_link) ObjLink();
    }

    obj_link::obj_link(const ObjLink& v) {
        new (&m_obj_link) ObjLink(v);
    }

    obj_link::operator ObjLink() const {
        return *reinterpret_cast<const ObjLink*>(m_obj_link);
    }

    obj_key obj_link::get_obj_key() {
        return reinterpret_cast<const ObjLink*>(m_obj_link)->get_obj_key();
    }

    bool operator==(obj_link const& lhs, obj_link const& rhs) {
        return static_cast<ObjLink>(lhs) == static_cast<ObjLink>(rhs);
    }
}