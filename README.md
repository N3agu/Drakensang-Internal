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

## How to find pointers
I recommend this video for pointer scanning: [Cheat Engine Pointer Scanning Tutorial](https://www.youtube.com/watch?v=rBe8Atevd-4) (by [GuidedHacking](https://www.youtube.com/@GuidedHacking)) and [How to find entity list using luck](https://www.youtube.com/watch?v=xefIcQXmw8g) by ([Swedz](https://www.youtube.com/@SwedishTwat))<br/>

<details>
<summary>Tips for finding Health & Mana (or any characteristic that can be modified by items)</summary>
1.  In the game, hover your mouse over the mana or health bar (or open the character statistics). Search for the displayed value in CE as a 4-byte integer.<br/>
2.  Unequip an item that affects your mana or health. Search for the new, reduced value in CE.<br/>
3.  Re-equip the item. Search for the new, increased value.<br/>
4.  Repeat steps 3 and 4 until you have a small number of potential addresses remaining.<br/>
5.  Add all remaining addresses to the address list in CE.<br/>
6.  Try editing the values in the list. One or two of these addresses will likely be related to the UI display and should be ignored. Do not perform pointer scans on these UI-related addresses.<br/>
</details>
<details>
<summary>Tips for finding Camera / Smoke / Angle View</summary>
1.  In the game, set the camera to its maximum zoomed-out position. Search for the value 25 in Cheat Engine (CE) as a float.<br/>
2.  Zoom in and search for a "Decreased value." Zoom in further and search for "Decreased value" again. Then, zoom out and use "Increased value." Repeat this process a few times.<br/>
3.  After narrowing down to a few addresses, edit each one separately (try with 50). If editing a value causes the camera to zoom significantly out, that's likely your camera address. Pointer scan for this address. Once you've found the final camera pointer (the address holding the camera's float value), you can often locate the other two features relative to it:<br/>
    - Smoke: Usually found at an offset of `+0x10` from the camera's final address.<br/>
    - Angle View: Usually found at an offset of `+0xC` from the smoke's final address (or `+0x1C` from the camera's final address).<br/>
</details>
<details>
<summary>Tips for finding Name / Current Map / Selected Enemy / Selected Non-Enemy</summary>
1.  In the game, search for the target name (for selected entities, you need to hover over the enemy or non-enemy). Search for the displayed value in Cheat Engine as a string.<br/>
2.  Change the selected entities a few times.<br/>
</details>
<details>
<summary>Tips for finding Entity</summary>
1.  In the game, unequip everything that has damage, equip a spell that doesn't deal too much damage, and enter a map where you won't kill enemies in one hit.<br/>
2.  Attack one enemy multiple times (you should need to hit the enemy at least 4-5 times; you can try with a boss, but I haven't). Add up all the damage you dealt to get a rough estimate of the enemy's health.<br/>
3.  In Cheat Engine, set the scan type to "Value between..." and search for a 4-byte value. Set the minimum to your calculated estimate minus 2000, and the maximum to your calculated estimate plus 2000.<br/>
4.  From there follow the video suggested (you can also use ReClass.NET or completely reverse the game with IDA/Ghidra), keep in mind DSO is built on Nebula Engine.
</details>
<details>
<summary>General tips after finding some pointers</summary>
1. Enter a new map: After finding some pointers, move to a different in-game map and check if the values remain consistent.<br/>
2. Restart the game: If the pointers hold up across several maps, close and reopen the game. Then, verify if the saved pointers still point to the correct values.<br/>
3. Change characters: After reopening the game, try switching to a different character type. Confirm that the pointers continue to be valid for this new character.<br/>
After this checks, your pointers should hold up at least until the next DSO update.<br/>
</details>

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
