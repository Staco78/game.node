#include "./image.h"

namespace game_node
{

    namespace
    {
        static Napi::FunctionReference constructor_ref;
    }

    Napi::Object Image::init(Napi::Env env, Napi::Object exports)
    {
        Napi::Function func = DefineClass(env, "Image", {});

        constructor_ref = Napi::Persistent(func);

        exports.Set("Image", func);

        return exports;
    }

    Image::Image(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Image>(info)
    {
        if (info.Length() != 1)
            Napi::TypeError::New(info.Env(), "Unexpected number of arguments").ThrowAsJavaScriptException();

        if (!info[0].IsString())
            Napi::TypeError::New(info.Env(), "Path must be a string").ThrowAsJavaScriptException();

        if (!m_image.loadFromFile(info[0].ToString().Utf8Value()))
            Napi::Error::New(info.Env(), "Failed to load image").ThrowAsJavaScriptException();
    }

    Napi::FunctionReference *Image::getConstructorRef()
    {
        return &constructor_ref;
    }
}