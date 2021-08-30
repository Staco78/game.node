#pragma once

#include "napi.h"
#include <SFML/Graphics.hpp>

#include "../structures/vector2.h"


namespace game_node {
	class Window : public Napi::ObjectWrap<Window>
	{
	public:
		static Napi::Object init(Napi::Env env, Napi::Object exports);
		Window(const Napi::CallbackInfo& info);
		~Window();

		Napi::Value getEvents(const Napi::CallbackInfo& info);
		Napi::Value close(const Napi::CallbackInfo& info) {
			m_window->close();
			return info.Env().Undefined();
		}

		Napi::Value isOpen(const Napi::CallbackInfo& info) {
			return Napi::Value::From(info.Env(), m_window->isOpen());
		}

		Napi::Value getSize(const Napi::CallbackInfo& info) {
			return Vector2::from(info.Env(), m_window->getSize());
		}



	private:
		sf::RenderWindow* m_window = nullptr;
	};
}