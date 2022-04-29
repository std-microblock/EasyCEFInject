# EasyCEFInject
A library to inject a piece of javascript to any application that is built with Chromium Embedded Framework.

# How does it work?
The dll hooked the function `cef_v8context_get_current_context` which will be called every time the application wants to do anything that has to do with javascript, including loading pages and refreshing.

After hooking the function, we can get the current v8 context, and then we can do anything we want.

Enjoy.

# How to use it?
todo!();
