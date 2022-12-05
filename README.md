# yaSetupDxe  
yet-another implementation of UEFI Setup Menu, inspired by Breeze theme for KDE plasma.  
## Overall goal  
To make a tiny layout inflator(Android-like)/widget arranger(Qt-like) under UEFI+GOP environment.  
## Techniques planned to use / implement  
* HiDPI Support (will try to match 1920*1080 resolution. i.e., 2x zoom on 2160p screen)  
* Vector-font rasterization (A tiny port of FreeType is to be ported)  
* Elegant UI (KDE Breeze theme / Android 9-patch scaling methodology)  
* MVVM architecture (Data observer, binding, etc)  
## Progresses / plans so far  
[x]&ensp;1. Emulated window using SDL2  
[x]&ensp;2. Mouse cursor  
[&ensp;]&ensp;3. FreeType port  
[&ensp;]&ensp;4. Caption generation  
[x]&ensp;5. 9-patch scaling  
[&ensp;]&ensp;6. widget design & display  
[&ensp;]&ensp;7. widget interaction(hover/leave/click/right-click/keyboard)  
......To Be Continued  
