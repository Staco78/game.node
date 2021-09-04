#pragma once

#include "napi.h"
#include <SFML/Graphics.hpp>

#include "../structures/vector2d.h"
#include "../structures/colors.h"
#include "../drawing/shape.h"
#include "../drawing/rect.h"

#include <iostream>

namespace game_node
{
	class Window : public Napi::ObjectWrap<Window>
	{
	public:
		static Napi::Object init(Napi::Env env, Napi::Object exports);
		Window(const Napi::CallbackInfo &info);
		~Window();

		Napi::Value getEvents(const Napi::CallbackInfo &info);
		Napi::Value close(const Napi::CallbackInfo &info)
		{
			m_window->close();
			return info.Env().Undefined();
		}

		Napi::Value isOpen(const Napi::CallbackInfo &info)
		{
			return Napi::Value::From(info.Env(), m_window->isOpen());
		}

		Napi::Value getSize(const Napi::CallbackInfo &info)
		{
			return Vector2d::from(info.Env(), m_window->getSize());
		}

		Napi::Value setSize(const Napi::CallbackInfo &info)
		{
			Napi::Env env = info.Env();

			m_window->setSize(Vector2d::resolve<uint32_t>(info));

			return env.Undefined();
		}

		Napi::Value display(const Napi::CallbackInfo &info)
		{
			m_window->display();

			return info.Env().Undefined();
		}

		Napi::Value setFramerateLimit(const Napi::CallbackInfo &info)
		{
			Napi::Env env = info.Env();
			if (info.Length() != 1)
				Napi::TypeError::New(env, "Unexpected number of arguments").ThrowAsJavaScriptException();

			if (!info[0].IsNumber())
				Napi::TypeError::New(env, "Framerate must be a number").ThrowAsJavaScriptException();

			int64_t framerate = info[0].ToNumber().Int64Value();

			if (framerate < 0)
				Napi::TypeError::New(env, "Framerate must be positive").ThrowAsJavaScriptException();

			m_window->setFramerateLimit(framerate);
			return env.Undefined();
		}

		Napi::Value clear(const Napi::CallbackInfo &info)
		{
			Napi::Env env = info.Env();

			if (info.Length() == 0)
			{
				m_window->clear();
			}
			else if (info.Length() == 1)
			{
				Color color = Color::resolve(env, info[0]);

				m_window->clear(color.toSfmlColor());
			}
			else
				Napi::TypeError::New(env, "Unexpected number of arguments").ThrowAsJavaScriptException();

			return env.Undefined();
		}

		Napi::Value draw(const Napi::CallbackInfo &info)
		{
			if (info.Length() != 1)
			{
				Napi::TypeError::New(info.Env(), "Unexpected number of arguments").ThrowAsJavaScriptException();
			}

			if (!info[0].IsObject())
			{
				Napi::TypeError::New(info.Env(), "Element to draw must be an object").ThrowAsJavaScriptException();
			}

			if (!info[0].ToObject().InstanceOf(Shape::getConstructor()->Value())) {
				Napi::TypeError::New(info.Env(), "Element to draw must be a shape").ThrowAsJavaScriptException();
			}

			m_window->draw(*Shape::Unwrap(info[0].ToObject()));

			return info.Env().Undefined();
		}

	private:
		sf::RenderWindow *m_window = nullptr;
	};
}