#include "./vector2d.h"

namespace game_node
{

	namespace
	{
		static Napi::FunctionReference constructor_ref;

	}

	Napi::Object Vector2d::init(Napi::Env env, Napi::Object exports)
	{
		Napi::Function func = DefineClass(env, "Vector2d", {InstanceAccessor("x", &Vector2d::getX, &Vector2d::setX), InstanceAccessor("y", &Vector2d::getY, &Vector2d::setY)});

		constructor_ref = Napi::Persistent(func);

		exports.Set("Vector2d", func);
		return exports;
	}

	Napi::FunctionReference *Vector2d::getConstructor()
	{
		return &constructor_ref;
	}
}