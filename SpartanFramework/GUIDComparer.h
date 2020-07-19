#pragma once

namespace Spartan
{
    struct GUIDComparer
    {
        bool operator()(const GUID& Left, const GUID& Right) const;
    };
}