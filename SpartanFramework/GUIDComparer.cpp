#include "stdafx.h"
#include "GUIDComparer.h"

namespace Spartan::Serialization
{
    bool GUIDComparer::operator()(const GUID& Left, const GUID& Right) const
    {
        // comparison logic goes here
        return memcmp(&Left, &Right, sizeof(Right)) < 0;
    }
}