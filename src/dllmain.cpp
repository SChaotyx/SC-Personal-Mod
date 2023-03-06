#include "includes.h"
#include "pauseLayer.h"


DWORD WINAPI thread_func(void* hModule) {
    // initialize minhook
    MH_Initialize();
    //practice music hack toggle
    MH_CreateHook(
        reinterpret_cast<void*>(gd::base + 0x1E4620),
        PauseLayer::hook,
        reinterpret_cast<void**>(&PauseLayer::init)
    );
        
    // enable all hooks you've created with minhook
    MH_EnableHook(MH_ALL_HOOKS);
    
    auto libBase = reinterpret_cast<uintptr_t>(GetModuleHandle("libcocos2d.dll"));
    
    //practice music
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20C925), "\x90\x90\x90\x90\x90\x90", 6, NULL);
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20D143), "\x90\x90", 2, NULL);
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20A563), "\x90\x90", 2, NULL);
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x20A595), "\x90\x90", 2, NULL);

    //Text length character bypass
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x21ACB), "\xEB\x04", 2, NULL);
    WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x21A99), "\x90\x90", 2, NULL);

	//No transition
	WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(libBase + 0xA5424), "\x90\x90\x90\x90\x90", 5, NULL);

   //level kick anticheat (for recording only)
   // WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(gd::base + 0x202AAA), "\xEB\x2E", 2, NULL);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        auto h = CreateThread(0, 0, thread_func, handle, 0, 0);
        if (h)
            CloseHandle(h);
        else
            return FALSE;
    }
    return TRUE;
}