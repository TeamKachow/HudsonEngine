#pragma once
#include "../Util/stdafx.h"

namespace Hudson::Common
{
    class ISerialisable
    {
    public:
        virtual ~ISerialisable() = default;

        /**
         * \brief Gets the serial ID.
         * \details This ID is used to resolve references to objects when saving and loading.
         * \return The ID to use to look up this object when saving and loading
         */
        virtual uint32_t GetSerialID() = 0;
    };
}

CEREAL_REGISTER_TYPE(Hudson::Common::ISerialisable)
