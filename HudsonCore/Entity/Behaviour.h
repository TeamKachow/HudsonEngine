﻿#pragma once
#include "Component.h"

namespace Hudson::Entity
{
    /**
     * \brief A scripted behaviour, which acts on certain parts of an object's update loop.
     */
    class Behaviour : public Component
    {
    public:
        /**
         * \brief Handles when a behaviour is added to a game object.
         */
        virtual void OnCreate() = 0;
        /**
         * \brief Handles when a game object's behaviours are updated.
         * \param dt The interval sicne the last update loop. (This interval should not change at runtime.)
         */
        virtual void OnTick(const double &dt) = 0;
        /**
         * \brief Handles when the behaviour is removed from its game object.
         */
        virtual void OnDestroy() = 0;
    };
}