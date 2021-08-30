#include "./vector2.h"

namespace game_node {
	Napi::Object Vector2::init(Napi::Env env, Napi::Object exports) {
		Napi::Function func = DefineClass(env, "Vector2", {
			InstanceAccessor("x", &Vector2::xGetter, &Vector2::xSetter),
			InstanceAccessor("y", &Vector2::yGetter, &Vector2::ySetter)
			});

		Napi::FunctionReference* constructor = new Napi::FunctionReference();
		*constructor = Napi::Persistent(func);
		env.SetInstanceData(constructor);

		exports.Set("Vector2", func);
		return exports;
	}

	Vector2::Vector2(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Vector2>(info){

	}
}