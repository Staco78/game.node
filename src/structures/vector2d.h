#pragma once

#include "napi.h"
#include <SFML/System.hpp>

#include "../structures/resolveData.h"


namespace game_node {

	class Vector2d : public Napi::ObjectWrap<Vector2d> {
	public:

		static Napi::Object init(Napi::Env env, Napi::Object exports);

		template<typename T>
		static Napi::Object from(Napi::Env env, sf::Vector2<T> vector) {
			return getConstructor()->New({ Napi::Value::From(env, vector.x), Napi::Value::From(env, vector.y) });
		}


		template<typename T>
		static ResolveData<sf::Vector2<T>> resolve(const Napi::CallbackInfo& info) {
			const char err_msg[] = "Argument must be an array of 2 numbers, a Vector2d object or 2 numbers";

			if (info.Length() >= 1) {
				Napi::Value value = info[0];
				if (value.IsArray()) {
					Napi::Array array = value.As<Napi::Array>();
					if (array.Length() != 2)
						Napi::TypeError::New(info.Env(), err_msg);

					Napi::Value _x = array[uint32_t(0)].operator Napi::Value();
					Napi::Value _y = array[uint32_t(1)].operator Napi::Value();

					if (!_x.IsNumber() || !_y.IsNumber())
						Napi::TypeError::New(info.Env(), err_msg);

					return _resolve<T>(_x.ToNumber(), _y.ToNumber(), 0);
				}
				else if (value.IsObject()) {
					if (value.As<Napi::Object>().Has("x") && value.As<Napi::Object>().Has("y")) {
						Napi::Value _x = value.As<Napi::Object>().Get("x");
						Napi::Value _y = value.As<Napi::Object>().Get("y");

						if (_x.IsNumber() && _y.IsNumber()) {
							return _resolve<T>(_x.ToNumber(), _y.ToNumber(), 0);
						}
						else Napi::TypeError::New(info.Env(), err_msg).ThrowAsJavaScriptException();

					}
					else Napi::TypeError::New(info.Env(), err_msg).ThrowAsJavaScriptException();
				}
				
			}
			if (info.Length() >= 2) {
				if (info[0].IsNumber() && info[1].IsNumber())
					return _resolve<T>(info[0].ToNumber(), info[1].ToNumber(), 1);
			}
			Napi::TypeError::New(info.Env(), err_msg).ThrowAsJavaScriptException();
		}

		Vector2d(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Vector2d>(info) {
			auto data = resolve<uint32_t>(info);
			if (data.lastArgUse + 1 != info.Length())
				Napi::TypeError::New(info.Env(), "Unexpected number of arguments");

			x = data.data.x;
			y = data.data.y;
		}

		Napi::Value getX(const Napi::CallbackInfo& info) {
			return Napi::Value::From(info.Env(), x);
		}

		void setX(const Napi::CallbackInfo& info, const Napi::Value& value) {
			if (!value.IsNumber())
				Napi::TypeError::New(info.Env(), "X must be a number").ThrowAsJavaScriptException();

			x = value.ToNumber().Int32Value();
		}

		Napi::Value getY(const Napi::CallbackInfo& info) {
			return Napi::Value::From(info.Env(), y);
		}

		void setY(const Napi::CallbackInfo& info, const Napi::Value& value) {
			if (!value.IsNumber())
				Napi::TypeError::New(info.Env(), "Y must be a number").ThrowAsJavaScriptException();

			y = value.ToNumber().Int32Value();
		}


	private:
		template<typename T>
		static ResolveData<sf::Vector2<T>> _resolve(Napi::Number x, Napi::Number y, int32_t lastArgUse) {
			throw "Invalid type";
		}

		template<>
		static ResolveData<sf::Vector2<int64_t>> _resolve<int64_t>(Napi::Number x, Napi::Number y, int32_t lastArgUse) {
			return ResolveData<sf::Vector2<int64_t>>(sf::Vector2<int64_t>(x.Int64Value(), y.Int64Value()), lastArgUse);
		}

		template<>
		static ResolveData<sf::Vector2<float>> _resolve<float>(Napi::Number x, Napi::Number y, int32_t lastArgUse) {
			return ResolveData<sf::Vector2<float>>(sf::Vector2<float>(x.FloatValue(), y.FloatValue()), lastArgUse);
		}

		template<>
		static ResolveData<sf::Vector2<unsigned int>> _resolve<unsigned int>(Napi::Number x, Napi::Number y, int32_t lastArgUse) {
			return ResolveData<sf::Vector2<unsigned int>>(sf::Vector2<unsigned int>(x.Uint32Value(), y.Uint32Value()), lastArgUse);
		}

	/*	template<>
		static ResolveData<sf::Vector2<Napi::Number>> _resolve<Napi::Number>(Napi::Number x, Napi::Number y, int32_t lastArgUse) {
			return ResolveData<sf::Vector2<Napi::Number>>(sf::Vector2<Napi::Number>(x, y), lastArgUse);
		}*/


		static Napi::FunctionReference* getConstructor();


		uint32_t x;
		uint32_t y;


	};
}