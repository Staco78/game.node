#include "./rect.h"

namespace game_node
{
	Napi::Object Rect::init(Napi::Env env, Napi::Object exports)
	{
		Napi::Function func = DefineClass(env, "Rect", {InstanceAccessor("x", &Rect::getX, &Rect::setX), InstanceAccessor("y", &Rect::getY, &Rect::setY), InstanceAccessor("width", &Rect::getWidth, &Rect::setWidth), InstanceAccessor("height", &Rect::getHeight, &Rect::setHeight)});

		Napi::FunctionReference *constructor = new Napi::FunctionReference();
		*constructor = Napi::Persistent(func);
		env.SetInstanceData(constructor);

		exports.Set("Rect", func);
		return exports;
	}

	Rect::Rect(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Rect>(info)
	{
		Napi::Env env = info.Env();

		if (info.Length() != 4)
			Napi::TypeError::New(env, "Unexpected number of arguments").ThrowAsJavaScriptException();

		float args[4];

		for (int i = 0; i < 4; i++)
		{
			if (!info[i].IsNumber())
				Napi::TypeError::New(env, "All of rect constructor arguments must be numbers").ThrowAsJavaScriptException();

			args[i] = info[1].ToNumber().FloatValue();
		}

		sf::RectangleShape::setPosition(args[0], args[1]);
		sf::RectangleShape::setSize(sf::Vector2f(args[2], args[3]));
	}

}