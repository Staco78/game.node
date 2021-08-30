#pragma once

#include "napi.h"
#include <SFML/System.hpp>

namespace game_node {
	class Vector2 : public Napi::ObjectWrap<Vector2> {
	public:
		static Napi::Object init(Napi::Env env, Napi::Object exports);
		static Napi::Object from(Napi::Env env, sf::Vector2i vector) {
			Napi::Object obj;
			obj.Set("x", Napi::Number::New(env, double(vector.x)));
			obj.Set("y", Napi::Number::New(env, double(vector.y)));

			return obj;
		}

		static Napi::Object from(Napi::Env env, sf::Vector2u vector) {
			Napi::Object obj = Napi::Object::New(env);
			obj.Set("x", Napi::Number::New(env, double(vector.x)));
			obj.Set("y", Napi::Number::New(env, double(vector.y)));

			return obj;
		}

		static Napi::Object from(Napi::Env env, sf::Vector2f vector) {
			Napi::Object obj;
			obj.Set("x", Napi::Number::New(env, double(vector.x)));
			obj.Set("y", Napi::Number::New(env, double(vector.y)));

			return obj;
		}

		Vector2(const Napi::CallbackInfo& info);

		Napi::Value xGetter(const Napi::CallbackInfo& info) { return x; }
		Napi::Value yGetter(const Napi::CallbackInfo& info) { return y; }
		void xSetter(const Napi::CallbackInfo& info,
			const Napi::Value& value) {
			if (!value.IsNumber())
				Napi::TypeError::New(info.Env(), "x must be a number");
			x = value.As<Napi::Number>();
		}
		void ySetter(const Napi::CallbackInfo& info,
			const Napi::Value& value) {
			if (!value.IsNumber())
				Napi::TypeError::New(info.Env(), "y must be a number");
			y = value.As<Napi::Number>();
		}

	private:
		Napi::Number x;
		Napi::Number y;
	};
}