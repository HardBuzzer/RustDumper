// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include "Il2CppIncludes.hpp"
#include "RustDumper.h"
#pragma warning(push, 0)
FILE* fp;
bool Il2CppThreadFound() {
    if (IL2CPP::Initialize(true) && IL2CPP::Thread::Attach(IL2CPP::Domain::Get())) 
    {
        return true;
    }
    else {
        return false;
    }
}
void OpenConsole() 
{
    AllocConsole();
    freopen_s(&fp, "CONOUT$", "w", stdout);
    SetConsoleTitleA("RustDumper");
}
bool print(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    return TRUE;
}

DWORD WINAPI MainThread(HMODULE hMod) 
{
    OpenConsole(); //Open Console :D
    printf("Founding Il2Cpp Dll File...");
    if (GetModuleHandleA("GameAssembly.dll")) {
        printf("Handle is Founding Successfull...");
        Sleep(5000);
        printf("Founding Il2Cpp Threads...");
        if (Il2CppThreadFound()) 
        {
            printf("Thread is Founded Success");
            Sleep(2100);
            printf("Waiting For Clicking Insert...");
            while (true) {
                if (GetAsyncKeyState(VK_INSERT))
                {
                    printf("Dumping...");
                    std::vector<std::string> vektor = RustDumper::DumpComponentsString();
                    Sleep(15000);
                    FreeLibraryAndExitThread(hMod, 0);
                }
            }
        }
        else {
            MessageBoxA(0, "Il2Cpp is Not Founded Success", "RustDumper", MB_OK || MB_ICONWARNING); //MessageBox :D
            return FALSE;
        }
        return TRUE;
    }
    else {
        printf("Handling is not Succesfull...");
        Sleep(2000); //Sleeping 2 Seconds :D
        FreeLibraryAndExitThread(hMod, 0);
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

