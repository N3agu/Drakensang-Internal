# Drakensang Injector & Internal Cheat

The injector was written in c# (.NET 4.8), the cheat was written in c++17. The cheat is using [MinHook](https://github.com/TsudaKageyu/minhook) for DirectX9 hooking with an [ImGui](https://github.com/ocornut/imgui) implementation for the menu.

## Injector:
It is a simple injector which gets the handle of the game process, obtains the address of **LoadLibraryA** from **kernel32.dll**, allocates memory with **VirtualAllocEx**, writes bytes with **WriteProcessMemory**, and then creates a thread which will run **LoadLibraryA**.<br><br>
![injector](https://raw.githubusercontent.com/N3agu/Drakensang-Internal/main/images/injector.png)

### Features
- Settings (save & load config file)
- Auto start (start game - maximize - login with password - select the server specified in config)
- Inject cheat (injects a dll into *dro_client64*)
- Exit correctly (kill pid)

## Internal Cheat
It's a simple internal menu built using ImGui. It provides functionalities like adjustable camera, smoke, angle view, visual attack speed, and displays player stats such as health, mana, and map information. Hooks and memory manipulation are implemented with MinHook for efficient interaction with game processes.

### Features
- Show/Hide & Unload<br>
**INS** - hide/show the features menu<br>
**HOME** - hide/show the character menu<br>
**END** - unhook dll
<details open>
<summary>Menu Preview</summary>
<br>
<img src="https://raw.githubusercontent.com/N3agu/Drakensang-Internal/main/images/menu.png">
</details>

- Camera<br>
Address: **threadstack0 - 0x00000270**<br>
Offsets: **0x78, 0x218, 0x30, 0x50, 0x60, 0x60, 0x78**
<details open>
<summary>Camera Preview</summary>
<br>
<img src="https://raw.githubusercontent.com/N3agu/Drakensang-Internal/main/images/camera.png">
</details>

- Smoke<br>
Address: **threadstack0 - 0x00000270**<br>
Offsets: **0x78, 0x218, 0x30, 0x50, 0x60, 0x60, 0x88**
<details open>
<summary>Smoke Preview</summary>
<br>
<img src="https://raw.githubusercontent.com/N3agu/Drakensang-Internal/main/images/smoke.png">
</details>

- Angle of View<br>
Address: **threadstack0 - 0x00000270**<br>
Offsets: **0x78, 0x218, 0x30, 0x50, 0x60, 0x60, 0x94**
<details open>
<summary>Angle of View Preview</summary>
<br>
<img src="https://raw.githubusercontent.com/N3agu/Drakensang-Internal/main/images/angle.png">
</details>

- Visual Attack Speed<br>
Address: **threadstack0 - 0x00000270**<br>
Offsets: **0x78, 0x110, 0x788, 0x30, 0x0, 0xD8**
<details open>
<summary>Visual Attack Speed Preview</summary>
<br>
<img src="https://raw.githubusercontent.com/N3agu/Drakensang-Internal/main/images/attackspeed.gif">
</details>

- Visual Username<br>
Address: **threadstack0 - 0x00000270**<br>
Offsets: **0xD8, 0x120, 0x78, 0xD0, 0x60, 0x260, 0x2A0**

- Health<br>
Address: **threadstack0 - 0x00000278**<br>
Offsets: **0x80, 0xB8, 0x20, 0x530, 0x48, 0x70, 0x40**

- Mana<br>
Address: **threadstack0 - 0x00000270**<br>
Offsets: **0x80, 0x80, 0x278, 0x40, 0x48, 0x70, 0x4C**

- Current Map<br>
Address: **threadstack0 - 0x00000270**<br>
Offsets: **0x1B8, 0x98, 0x40, 0x60, 0x0, 0x260, 0x260**

- Selected Enemy<br>
Address: **threadstack0 - 0x00000270**<br>
Offsets: **0x158, 0x58, 0x60, 0x0, 0x2A0**

- Selected Non-Enemy (NPCs & Objects)<br>
Address: **threadstack0 - 0x00000270**<br>
Offsets: **0x158, 0x200, 0x10, 0x70, 0x60, 0x0, 0x2A0**

## Build
Both the injector and the cheat were built with Visual Studio 2022.

### Injector
- Framework: .NET 4.8<br>
- Target: Release<br>
- Architecture: x64

### Cheat
- C++ Language Standard: /std:c++17<br>
- Target: Release<br>
- Architecture: x64<br>
- Character Set: Use Multi-Byte<br>
- Precompiled Headers: Not Using Precompiled Headers<br><br>
The injector can be found inside "*\Drakensang Injector\bin\x64\Release*".<br>
The cheat can be found inside "*\Drakensang Internal\build*".

## Improvements
- code refractoring
- character selector
- finding entity list
- other utilities in-game (fast mount, inventory seller, etc.)

## Credits
- CheatEngine's Forum - [post on ThreadStack](https://forum.cheatengine.org/viewtopic.php?p=5487976#5487976)
- [5aava's ThreadStack finder for x64](https://github.com/5aava/cheatengine-threadstack-finder-x64)

## License
Drakensang Internal is licensed under the [MIT license](https://github.com/N3agu/Drakensang-Internal/blob/main/LICENSE).

## Disclaimer
- The latest release is **OLD**. Please build from the source.
- This project is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
- This project is for learning purposes only and strictly prohibited for any illegal activities. Users bear full responsibility for any misuse.
