#pragma once

namespace Spartan::Serialization
{
    struct GUIDComparer
    {
        bool operator()(const GUID& Left, const GUID& Right) const;
    };
}