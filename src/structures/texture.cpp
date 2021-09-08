#include "./texture.h"

namespace game_node
{
    namespace
    {
        static Napi::FunctionReference constructor_ref;
    }

    Napi::Object Texture::init(Napi::Env env, Napi::Object exports)
    {
        Napi::Function func = DefineClass(env, "Texture", {});

        constructor_ref = Napi::Persistent(func);

        exports.Set("Texture", func);

        return exports;
    }

    Texture::Texture(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Texture>(info)
    {
        if (info.Length() != 1)
            Napi::TypeError::New(info.Env(), "Unexpected number of arguments").ThrowAsJavaScriptException();

        if (info[0].IsObject() && info[0].ToObject().InstanceOf(Image::getConstructorRef()->Value()))
        {
            if (!m_texture.loadFromImage(Image::Unwrap(info[0].ToObject())->getSfImage()))
                Napi::Error::New(info.Env(), "Failed to load image").ThrowAsJavaScriptException();
        }
        else
            Napi::TypeError::New(info.Env(), "Argument must be an image").ThrowAsJavaScriptException();
    }

    Napi::FunctionReference *Texture::getConstructorRef()
    {
        return &constructor_ref;
    }
}