#pragma once

#include "napi.h"
#include <SFML/System.hpp>

namespace game_node {
	class Vector2{
	public:
		static Napi::Object from(Napi::Env env, sf::Vector2i vector) {
			Napi::Object obj = Napi::Object::New(env);
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
			Napi::Object obj = Napi::Object::New(env);
			obj.Set("x", Napi::Number::New(env, double(vector.x)));
			obj.Set("y", Napi::Number::New(env, double(vector.y)));

			return obj;
		}
	};
}