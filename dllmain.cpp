#include "pch.h"
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>
#include "detours/detours.h"
#include "include/cef_v8.h"
#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/internal/cef_export.h"
#include "include/capi/cef_v8_capi.h"

// defination of cef_v8context_get_current_context
typedef cef_v8context_t* (*get_context)();

PVOID v8getcontext_source = NULL;

std::string script;

cef_v8context_t* v8getcontext_hooked() {
    cef_v8context_t* context = ((get_context)v8getcontext_source)();
    cef_browser_t* browser = context->get_browser(context);
    _cef_frame_t* frame = browser->get_main_frame(browser);
    CefString exec_script = "if(!window.__easyCefInject__){window.__easyCefInject__=true;"+script+"}";
    CefString url = "libeasycef/inject.js";
    frame->execute_java_script(frame, exec_script.GetStruct(), url.GetStruct(), 0);
    return context;
}

BOOL APIENTRY InstallHook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    v8getcontext_source = DetourFindFunction("libcef.dll", "cef_v8context_get_current_context");
    if (v8getcontext_source) {
        DetourAttach(&v8getcontext_source, v8getcontext_hooked);
    }
    LONG ret = DetourTransactionCommit();
    return ret == NO_ERROR;
}


BOOL APIENTRY UnInstallHook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&v8getcontext_source, v8getcontext_hooked);
    LONG ret = DetourTransactionCommit();
    return ret == NO_ERROR;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        std::ifstream t("easycefinject.js");
        std::stringstream buffer;
        buffer << t.rdbuf();
        script = buffer.str();
        InstallHook();
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        UnInstallHook();
    }

    return TRUE;
}