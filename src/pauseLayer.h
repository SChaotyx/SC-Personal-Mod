#pragma once
#include "includes.h"

namespace PauseLayer {
	inline bool(__thiscall* init)(CCLayer* self);
	bool __fastcall hook(CCLayer* self);
	class Callbacks {
	public:
		void practiceMusicButton(CCObject*);
	};
}