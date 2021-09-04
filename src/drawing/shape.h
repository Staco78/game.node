#pragma once

#include "napi.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

namespace game_node
{
    class Shape : public Napi::ObjectWrap<Shape>, public sf::Shape
    {
    public:
        static Napi::Object init(Napi::Env env, Napi::Object exports);

        Shape(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Shape>(info)
        {
        }

        Napi::Value getX(const Napi::CallbackInfo &info)
        {
            return Napi::Value::From(info.Env(), getPosition().x);
        }

        void setX(const Napi::CallbackInfo &info, const Napi::Value &value)
        {
            if (!value.IsNumber())
                Napi::TypeError::New(info.Env(), "X must be a number").ThrowAsJavaScriptException();

            setPosition(value.ToNumber().Int64Value(), getPosition().y);
        }

        Napi::Value getY(const Napi::CallbackInfo &info)
        {
            return Napi::Value::From(info.Env(), getPosition().y);
        }

        void setY(const Napi::CallbackInfo &info, const Napi::Value &value)
        {
            if (!value.IsNumber())
                Napi::TypeError::New(info.Env(), "Y must be a number").ThrowAsJavaScriptException();

            setPosition(getPosition().x, value.ToNumber().Int64Value());
        }

        static Napi::FunctionReference *getConstructor();

        sf::Vector2f getPoint(std::size_t index) const
        {
            return sf::Vector2f(0, 0);
        }
        std::size_t getPointCount() const
        {
            return 0;
        };
    };
}