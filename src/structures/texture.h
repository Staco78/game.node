#pragma once

#include "napi.h"

#include "SFML/Graphics.hpp"
#include "./image.h"

namespace game_node
{
    class Texture : public Napi::ObjectWrap<Texture>
    {
    public:
        static Napi::Object init(Napi::Env env, Napi::Object exports);

        Texture(const Napi::CallbackInfo &infos);

        static Napi::FunctionReference *getConstructorRef();

        sf::Texture* getSfTexture()
        {
            return &m_texture;
        }

    private:
        sf::Texture m_texture;
    };
}