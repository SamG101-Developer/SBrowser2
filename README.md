# SBrowser

SBrowser is a brand-new browser engine built from the ground up, containing no code from the Chromium or Firefox
project. It contains its own DOM/CSS/HTML implementations, and every web spec is implemented in raw C++. The web api
implementations, network stack, render stack, storage access and GUI are all newly designed. The only major 3rd party
components used are the Qt6 GUI Framework, and Google's V8 JavaScript engine. Other 3rd party components used are
smaller projects individually developed and available on GitHub, of which are mostly drop-in STL component replacements,
offering better performance. A list of these can be identified in the CMakeLists.txt file.

The SBrowser engine aims to be very memory-efficient, whilst still offering ultra-high speeds for webpage access and
rendering.

