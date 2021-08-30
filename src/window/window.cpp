#include "./window.h"

namespace game_node {
	Napi::Object Window::init(Napi::Env env, Napi::Object exports) {
		Napi::Function func = DefineClass(env, "Window", {
				InstanceMethod<&Window::getEvents>("getEvents"),
				InstanceMethod<&Window::close>("close"),
				InstanceMethod<&Window::isOpen>("isOpen"),
				InstanceMethod<&Window::getSize>("getSize"),
				InstanceMethod<&Window::setSize>("setSize"),
				InstanceMethod<&Window::display>("display"),
				InstanceMethod<&Window::setFramerateLimit>("setFramerateLimit"),
				InstanceMethod<&Window::clear>("clear")
			});

		Napi::FunctionReference* constructor = new Napi::FunctionReference();
		*constructor = Napi::Persistent(func);
		env.SetInstanceData(constructor);

		exports.Set("Window", func);
		return exports;
	}

	Window::Window(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Window>(info) {
		Napi::Env env = info.Env();

		if (info.Length() != 2)
			Napi::TypeError::New(env, "Unexpected number of arguments").ThrowAsJavaScriptException();

		if (!info[0].IsArray())
			Napi::TypeError::New(env, "Size must be an array of two numbers").ThrowAsJavaScriptException();

		Napi::Value _width = info[0].As<Napi::Array>()[uint32_t(0)].operator Napi::Value();
		Napi::Value _height = info[0].As<Napi::Array>()[uint32_t(1)].operator Napi::Value();

		if (!_width.IsNumber() || !_height.IsNumber())
			Napi::TypeError::New(env, "Size must be an array of two numbers").ThrowAsJavaScriptException();

		uint32_t width = _width.ToNumber().Uint32Value();
		uint32_t height = _height.ToNumber().Uint32Value();

		if (!info[1].IsString())
			Napi::TypeError::New(env, "Title must be a string").ThrowAsJavaScriptException();

		m_window = new sf::RenderWindow(sf::VideoMode(width, height), info[1].ToString().Utf8Value());
		m_window->setFramerateLimit(60);

	}

	Napi::Value Window::getEvents(const Napi::CallbackInfo& info) {
		Napi::Env env = info.Env();

		Napi::Array array = Napi::Array::New(env);

		sf::Event event;
		int i = 0;
		while (m_window->pollEvent(event)) {

			//Napi::Value value = Napi::Value::From(env, 1);
			//array[1] = value;
			array[i] = Napi::Value::From(env, int(event.type));
			i++;
		}

		return array;

	}

	Window::~Window() {
		delete m_window;
	}
}
