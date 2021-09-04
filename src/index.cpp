
#include "napi.h"
#include "./window/window.h"
#include "./drawing/shape.h"
#include "./drawing/rect.h"

#include <iostream>

namespace game_node {

	Napi::Object Init(Napi::Env env, Napi::Object exports) {
		exports = Window::init(env, exports);
		exports = Vector2d::init(env, exports);
		exports = Shape::init(env, exports);
		exports = Rect::init(env, exports);

		return exports;
	}

	NODE_API_MODULE(game_node, Init)

}  // 