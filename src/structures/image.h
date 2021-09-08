#pragma once

#include "napi.h"

#include "SFML/Graphics.hpp"

namespace game_node
{

    class Image : public Napi::ObjectWrap<Image>
    {
    public:
        static Napi::Object init(Napi::Env env, Napi::Object exports);

        Image(const Napi::CallbackInfo &info);

        static Napi::FunctionReference *getConstructorRef();

        sf::Image getSfImage()
        {
            return m_image;
        }

    private:
        sf::Image m_image;
    };
}