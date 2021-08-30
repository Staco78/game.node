
#include "napi.h"
#include "./window/window.h"

#include <iostream>

namespace game_node {

	Napi::Object Init(Napi::Env env, Napi::Object exports) {
		exports = Window::init(env, exports);
		return exports;
	}

	NODE_API_MODULE(hello, Init)

}  // 