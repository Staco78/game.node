
#include "napi.h"
#include "./window/window.h"

namespace game_node {

	Napi::Object Init(Napi::Env env, Napi::Object exports) {
		exports = Window::init(env, exports);
		return exports;
	}

	NODE_API_MODULE(hello, Init)

}  // 