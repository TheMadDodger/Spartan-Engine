#pragma once

namespace SpartanEngine
{
    struct GUIDComparer
    {
        bool operator()(const GUID& Left, const GUID& Right) const;
    };
}