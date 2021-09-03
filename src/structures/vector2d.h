#pragma once

#include "napi.h"
#include <SFML/System.hpp>

namespace game_node
{

	class Vector2d : public Napi::ObjectWrap<Vector2d>
	{
	public:
		static Napi::Object init(Napi::Env env, Napi::Object exports);

		template <typename T>
		static Napi::Object from(Napi::Env env, sf::Vector2<T> vector)
		{
			return getConstructor()->New({Napi::Value::From(env, vector.x), Napi::Value::From(env, vector.y)});
		}

		template <typename T>
		static sf::Vector2<T> resolve(const Napi::CallbackInfo &info)
		{
			const char err_msg[] = "Argument must be an array of 2 numbers or a Vector2d object";

			if (info.Length() >= 1)
			{
				Napi::Value value = info[0];
				if (value.IsArray())
				{
					Napi::Array array = value.As<Napi::Array>();
					if (array.Length() != 2)
						Napi::TypeError::New(info.Env(), err_msg);

					Napi::Value _x = array[uint32_t(0)].operator Napi::Value();
					Napi::Value _y = array[uint32_t(1)].operator Napi::Value();

					if (!_x.IsNumber() || !_y.IsNumber())
						Napi::TypeError::New(info.Env(), err_msg);

					return _resolve<T>(_x.ToNumber(), _y.ToNumber());
				}
				else if (value.IsObject())
				{
					if (value.As<Napi::Object>().Has("x") && value.As<Napi::Object>().Has("y"))
					{
						Napi::Value _x = value.As<Napi::Object>().Get("x");
						Napi::Value _y = value.As<Napi::Object>().Get("y");

						if (_x.IsNumber() && _y.IsNumber())
						{
							return _resolve<T>(_x.ToNumber(), _y.ToNumber());
						}
						else
							Napi::TypeError::New(info.Env(), err_msg).ThrowAsJavaScriptException();
					}
					else
						Napi::TypeError::New(info.Env(), err_msg).ThrowAsJavaScriptException();
				}
			}
			Napi::TypeError::New(info.Env(), err_msg).ThrowAsJavaScriptException();
		}

		Vector2d(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Vector2d>(info)
		{
			const char err_msg[] = "Argument must be an array of 2 numbers, a Vector2d object or 2 numbers";

			if (info.Length() == 1)
			{
				Napi::Value value = info[0];
				if (value.IsArray())
				{
					Napi::Array array = value.As<Napi::Array>();
					if (array.Length() != 2)
						Napi::TypeError::New(info.Env(), err_msg);

					Napi::Value _x = array[uint32_t(0)].operator Napi::Value();
					Napi::Value _y = array[uint32_t(1)].operator Napi::Value();

					if (!_x.IsNumber() || !_y.IsNumber())
						Napi::TypeError::New(info.Env(), err_msg).ThrowAsJavaScriptException();

					x = _x.ToNumber().DoubleValue();
					y = _y.ToNumber().DoubleValue();
				}
				else if (value.IsObject())
				{
					if (value.As<Napi::Object>().Has("x") && value.As<Napi::Object>().Has("y"))
					{
						Napi::Value _x = value.As<Napi::Object>().Get("x");
						Napi::Value _y = value.As<Napi::Object>().Get("y");

						if (_x.IsNumber() && _y.IsNumber())
						{
							x = _x.ToNumber().DoubleValue();
							y = _y.ToNumber().DoubleValue();
						}
						else
							Napi::TypeError::New(info.Env(), err_msg).ThrowAsJavaScriptException();
					}
					else
						Napi::TypeError::New(info.Env(), err_msg).ThrowAsJavaScriptException();
				}
			}
			else if (info.Length() == 2){
				if (!info[0].IsNumber() || !info[1].IsNumber())
					Napi::TypeError::New(info.Env(), err_msg).ThrowAsJavaScriptException();

				x = info[0].ToNumber().DoubleValue();
				y = info[1].ToNumber().DoubleValue();
			}
			else
				Napi::TypeError::New(info.Env(), err_msg).ThrowAsJavaScriptException();
		}

		Napi::Value getX(const Napi::CallbackInfo &info)
		{
			return Napi::Value::From(info.Env(), x);
		}

		void setX(const Napi::CallbackInfo &info, const Napi::Value &value)
		{
			if (!value.IsNumber())
				Napi::TypeError::New(info.Env(), "X must be a number").ThrowAsJavaScriptException();

			x = value.ToNumber().Int32Value();
		}

		Napi::Value getY(const Napi::CallbackInfo &info)
		{
			return Napi::Value::From(info.Env(), y);
		}

		void setY(const Napi::CallbackInfo &info, const Napi::Value &value)
		{
			if (!value.IsNumber())
				Napi::TypeError::New(info.Env(), "Y must be a number").ThrowAsJavaScriptException();

			y = value.ToNumber().Int32Value();
		}

	private:
		template <typename T>
		static sf::Vector2<T> _resolve(Napi::Number x, Napi::Number y)
		{
			throw "Invalid type";
		}

		template <>
		static sf::Vector2<int64_t> _resolve<int64_t>(Napi::Number x, Napi::Number y)
		{
			return sf::Vector2<int64_t>(sf::Vector2<int64_t>(x.Int64Value(), y.Int64Value()));
		}

		template <>
		static sf::Vector2<float> _resolve<float>(Napi::Number x, Napi::Number y)
		{
			return sf::Vector2<float>(sf::Vector2<float>(x.FloatValue(), y.FloatValue()));
		}

		template <>
		static sf::Vector2<uint32_t> _resolve<uint32_t>(Napi::Number x, Napi::Number y)
		{
			return sf::Vector2<uint32_t>(sf::Vector2<uint32_t>(x.Uint32Value(), y.Uint32Value()));
		}

		static Napi::FunctionReference *getConstructor();

		double x;
		double y;
	};
}