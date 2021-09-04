#include "./shape.h"

namespace game_node
{

    namespace
    {
        static Napi::FunctionReference constructor_ref;

    }

    Napi::Object Shape::init(Napi::Env env, Napi::Object exports)
    {
        Napi::Function func = DefineClass(env, "Shape",
                                          {InstanceAccessor("x", &Shape::getX, &Shape::setX),
                                           InstanceAccessor("y", &Shape::getY, &Shape::setY)});

        constructor_ref = Napi::Persistent(func);

        exports.Set("Shape", func);
        return exports;
    }

    Napi::FunctionReference *Shape::getConstructor()
    {
        return &constructor_ref;
    }
}