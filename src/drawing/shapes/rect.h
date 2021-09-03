#pragma once

#include "napi.h"

#include <SFML/Graphics.hpp>

#include "../../structures/vector2d.h"

namespace game_node
{
	class Rect : public Napi::ObjectWrap<Rect>, public sf::RectangleShape
	{
	public:
		static Napi::Object init(Napi::Env env, Napi::Object exports);

		Rect(const Napi::CallbackInfo &info);

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

		Napi::Value getWidth(const Napi::CallbackInfo &info)
		{
			return Napi::Value::From(info.Env(), getSize().x);
		}

		void setWidth(const Napi::CallbackInfo &info, const Napi::Value &value)
		{
			if (!value.IsNumber())
				Napi::TypeError::New(info.Env(), "X must be a number").ThrowAsJavaScriptException();

			setSize(sf::Vector2f(value.ToNumber().Int64Value(), getSize().y));
		}

		Napi::Value getHeight(const Napi::CallbackInfo &info)
		{
			return Napi::Value::From(info.Env(), getSize().y);
		}

		void setHeight(const Napi::CallbackInfo &info, const Napi::Value &value)
		{
			if (!value.IsNumber())
				Napi::TypeError::New(info.Env(), "Y must be a number").ThrowAsJavaScriptException();

			setSize(sf::Vector2f(getSize().x, value.ToNumber().Int64Value()));
		}
	};

}