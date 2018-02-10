#pragma once
#include <memory>


namespace Tools {
    template<typename D, typename B>
    std::unique_ptr<D> static_cast_unique_ptr(std::unique_ptr<B>& base)
    {
        return std::unique_ptr<D>(static_cast<D*>(base.release()));
    }

    template<typename D, typename B>
    std::unique_ptr<D> static_cast_unique_ptr(std::unique_ptr<B>&& base)
    {
        return std::unique_ptr<D>(static_cast<D*>(base.release()));
    }
};
