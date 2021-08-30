#pragma once
#include "napi.h"

#include <SFML/System.hpp>

namespace game_node {
	class Color {
	public:
		Color static resolve(Napi::Env env, Napi::Value value) {
			const char err_msg[] = "Color must be an array of three numbers or a color object";
			if (value.IsArray()) {
				Napi::Array array = value.As<Napi::Array>();
				if (array.Length() != 3)
					Napi::TypeError::New(env, err_msg);

				Napi::Value _r = array[uint32_t(0)].operator Napi::Value();
				Napi::Value _g = array[uint32_t(1)].operator Napi::Value();
				Napi::Value _b = array[uint32_t(2)].operator Napi::Value();

				if (!_r.IsNumber() || !_g.IsNumber() || _b.IsNumber())
					Napi::TypeError::New(env, err_msg);

				uint32_t r = _r.ToNumber().Int32Value();
				uint32_t b = _b.ToNumber().Int32Value();
				uint32_t g = _g.ToNumber().Int32Value();

				if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
					Napi::TypeError::New(env, "A color channel must be between 0 and 255").ThrowAsJavaScriptException();

				return Color(r, g, b);
			}
			else if (value.IsObject()) {
				if (value.As<Napi::Object>().Has("r") && value.As<Napi::Object>().Has("g") && value.As<Napi::Object>().Has("b")) {
					Napi::Value _r = value.As<Napi::Object>().Get("r");
					Napi::Value _g = value.As<Napi::Object>().Get("g");
					Napi::Value _b = value.As<Napi::Object>().Get("b");

					if (_r.IsNumber() && _g.IsNumber() && _b.IsNumber()) {
						int32_t r = _r.ToNumber().Int32Value();
						int32_t g = _g.ToNumber().Int32Value();
						int32_t b = _b.ToNumber().Int32Value();

						if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
							Napi::TypeError::New(env, "A color channel must be between 0 and 255").ThrowAsJavaScriptException();

						return Color(r, g, b);
					}
					else Napi::TypeError::New(env, err_msg).ThrowAsJavaScriptException();

				}
				else Napi::TypeError::New(env, err_msg).ThrowAsJavaScriptException();
			}
			else Napi::TypeError::New(env, err_msg).ThrowAsJavaScriptException();
		}

		Color(uint32_t r, uint32_t g, uint32_t b) {
			m_r = r;
			m_g = g;
			m_b = b;
		}

		sf::Color toSfmlColor() {
			return sf::Color(m_r, m_g, m_b);
		}

		uint32_t m_r;
		uint32_t m_g;
		uint32_t m_b;
	};
}