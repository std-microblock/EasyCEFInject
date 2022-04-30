# EasyCEFInject
A library to inject a piece of javascript to any application that is built with Chromium Embedded Framework.

Neither now nor future supports cross-platform.

# How does it work?
The dll hooked the function `cef_v8context_get_current_context` which will be called every time the application wants to do anything that has to do with javascript, including loading pages and refreshing.

After hooking the function, we can get the current v8 context, and then we can do anything we want.

Enjoy.

# How to use it?
 1. First of all, inject the dll into the target application whatever the way you used (like the project [BetterNCM](https://github.com/BetterNCM), used the branch [msimg32.dll-hijacking](https://github.com/MicroCBer/EasyCEFInject/tree/msimg32.dll-hijacking) to make Netease Cloud Music load the DLL once it runs by doing some hijacks on msimg32.dll).
 2. After that, the dll will read `easycefinject.js` and inject it. Normally, your script will run only once.

# How to build it?
 This library used vcpkg to install the dependencies it used. So install vcpkg and install the following libraries.
 ```
 detours
 ```
 And also, it used the included files of `CEF` in order to hook. Download the source code of the version you want, and replace the whole `include` folder in `EasyCEFInject` with the `include` folder in the source code of `CEF` you downloaded. And then build it. You can also build directly after installing the dependencies. In that case, the project will use an older version of `CEF`(CEF 51) which is included in my source code.
