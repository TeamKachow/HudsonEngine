﻿#pragma once

#include "../World/SceneManager.h"

#include "../Physics/PhysicsManager.h"

namespace Hudson
{
    namespace Render
    {
        class Renderer;
    }
}

namespace Hudson::Common
{
    /**
     * \brief The entrypoint to the engine.
     * \details This manages the lifecycle (start -> game loop -> exit) of the game.
     */
    class Engine
    {
    private:
        std::unique_ptr<World::SceneManager> _sceneManager;
        std::unique_ptr<Render::Renderer> _renderer; 
        std::unique_ptr<Physics::PhysicsManager> _physics;
        // TODO: std::unique_ptr<AudioManager> _audio; 
        // TODO: std::unique_ptr<InputManager> _input; 
        
        bool _shutdownFlag = false;
        std::vector<std::function<void(Engine*)>> _frameHooks;

    public:
        Engine();
        ~Engine();

        // TODO: figure out which things belong in which parts of the engine lifecycle
        /**
         * \brief Set up game engine resources and run setup function if provided
         */
        void Setup();

        /**
         * \brief Run the engine loop. This will return when the game/editor exits.
         */
        void Run();

        /**
         * \brief Shut down the engine at the end of the current update loop.
         * \details If currently running, this will set a flag to stop at the end of the current update loop.
         * \details This will *not* clean up the game resources - for that, see Cleanup()
         */
        void Shutdown();

        /**
         * \brief Clean up engine resources.
         */
        void Cleanup();

        /**
         * \brief Get the engine's scene manager.
         * \return The scene manager
         */
        [[nodiscard]] Hudson::World::SceneManager* GetSceneManager() const;

        /**
         * \brief Register a hook to run after engine systems have run for the frame but before it renders.
         * \param frameHook The function to call before a frame renders.
         */
        void RegisterFrameHook(std::function<void(Engine*)> frameHook);
    };
}
