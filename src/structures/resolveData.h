#pragma once

template <typename T>
class ResolveData {
public:
	ResolveData(T data, int32_t lastArgUse) {
		ResolveData::data = data;
		ResolveData::lastArgUse = lastArgUse;
	}

	T data;
	int32_t lastArgUse;
};