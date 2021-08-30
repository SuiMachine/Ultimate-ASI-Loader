# Ultimate ASI Loader - Mono Loader

## DESCRIPTION

This is a DLL file which adds ASI plugin loading functionality to any game as well as load .NET compiled DLL libraries, which uses any of the following libraries:

- d3d9.dll
- d3d11.dll
- ddraw.dll
- dinput.dll
- dinput8.dll (x86 and x64)
- dsound.dll (x86 and x64)
- msacm32.dll
- msvfw32.dll
- version.dll (x86 and x64)
- wininet.dll (x86 and x64)
- winmm.dll
- xlive.dll

- vorbisFile.dll
- binkw32.dll

With the last two, it is possible to load the original dll by renaming it to 'vorbisHooked.dll' or 'binkw32Hooked.dll'.
Usually it is not required and you can simply replace the dll. Always make a backup before replacing any files.

Majority of library was based on original code by [ThirteenAG](https://github.com/ThirteenAG/Ultimate-ASI-Loader).

It was designed to inject any wanted class and create MonoObject inside Unity's game without having to redistribute original game's libraries. Currently won't work with 64bit libraries and 32bit is still junky. D3D8.dll support was removed, as this library mostly targets Unity.

## INSTALLATION

In order to install it, you just need to place DLL into game directory. Usually it works as dinput8.dll, but if it's not, there is a possibility to rename it(see the list of supported names above).

## USAGE
To use .NET libary injection compile your libraries to preferbably use NET 3.5 (Mono 2.0 wasn't tested) and put them in 'mono_plugins'.

~~Put ASI files in game root directory, 'scripts' or 'plugins' folder.~~
~~If configuration is necessary, global.ini file can be placed to 'scripts' or 'plugins' folder. It can be used alongside the chosen dll and if so, it is also possible to use dll name for ini file, e.g. version.dll/version.ini.~~
[See example of global.ini here](https://github.com/ThirteenAG/Ultimate-ASI-Loader/blob/master/data/scripts/global.ini).

## ADDITIONAL WINDOWED MODE FEATURE

ASI loader have built-in wndmode.dll, which can be loaded, if you create empty wndmode.ini in the folder with asi loader's dll. It will be automatically filled with example configuration at the first run of the game. Settings are not universal and should be changed in every specific case, but usually it works as is.


[See example of global.ini here](https://github.com/ThirteenAG/Ultimate-ASI-Loader/blob/master/data/scripts/global.ini#L6).

## CrashDumps

ASI loader is now capable of generating crash minidumps and crash logs. To use this feature, create a folder named `CrashDumps` in the folder with asi loader's dll. You can disable that via `DisableCrashDumps=1` ini option.
