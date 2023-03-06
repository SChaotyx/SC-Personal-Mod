#include "PauseLayer.h"

bool practiceMusicEnabled = true;

void PauseLayer::Callbacks::practiceMusicButton(CCObject*) {
	practiceMusicEnabled = !practiceMusicEnabled;
	if (practiceMusicEnabled) {
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20C925), "\x90\x90\x90\x90\x90\x90", 6, NULL);
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20D143), "\x90\x90", 2, NULL);
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20A563), "\x90\x90", 2, NULL);
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20A595), "\x90\x90", 2, NULL);
	}
	else {
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20C925), "\x0f\x85\xf7\x00\x00\x00", 6, NULL);
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20D143), "\x75\x41", 2, NULL);
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20A563), "\x75\x3e", 2, NULL);
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20A595), "\x75\x0c", 2, NULL);
	}
}

auto testPracticeMusic(CCSprite* toggleOn, CCSprite* toggleOff) {
	return(practiceMusicEnabled) ? toggleOn : toggleOff;
}

bool __fastcall PauseLayer::hook(CCLayer* self)
{
	bool result = PauseLayer::init(self);
	auto director = CCDirector::sharedDirector();
	auto size = director->getWinSize();

	auto toggleOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
	auto toggleOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
	gd::CCMenuItemToggler::create(testPracticeMusic(toggleOn, toggleOff), testPracticeMusic(toggleOff, toggleOn), self, menu_selector(PauseLayer::Callbacks::practiceMusicButton));

	auto practiceMusicButton = gd::CCMenuItemToggler::create(testPracticeMusic(toggleOn, toggleOff), testPracticeMusic(toggleOff, toggleOn), self, menu_selector(PauseLayer::Callbacks::practiceMusicButton));
	auto label = CCLabelBMFont::create("P.M", "bigFont.fnt");
	practiceMusicButton->setScale(0.60f);
	label->setScale(0.5f);
	label->setPositionX(-30);

	auto menu = CCMenu::create();
	menu->setPosition({ size.width - 50, size.height - 50 });
	menu->addChild(practiceMusicButton);
	menu->addChild(label);
	self->addChild(menu);

	return result;
}