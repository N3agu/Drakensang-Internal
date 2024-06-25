# Drakensang Injector & Internal Cheat

The injector was written in c# (.NET 4.8), the cheat was written in c++17. The cheat is using [MinHook](https://github.com/TsudaKageyu/minhook) for DirectX9 hooking with an [ImGui](https://github.com/ocornut/imgui) implementation for the menu.

## Injector:
soon

![injector](https://raw.githubusercontent.com/N3agu/Drakensang-Internal/main/images/injector.png)

## Internal Cheat
soon
### Features:
- Camera
Address: **threadstack0 - 0x00000270**<br>
Offsets: **0x78, 0x110, 0x738, 0x78, 0x60, 0x78**
<details>
<summary>Camera Image</summary>
<br>
<img src="https://raw.githubusercontent.com/N3agu/Drakensang-Internal/main/images/camera.png">
</details>

- Smoke
Address: **threadstack0 - 0x00000270**<br>
Offsets: **0x78, 0x110, 0x738, 0x78, 0x60, 0x88**
<details>
<summary>Smoke Image</summary>
<br>
<img src="https://raw.githubusercontent.com/N3agu/Drakensang-Internal/main/images/smoke.png">
</details>

- Angle of View
Address: **threadstack0 - 0x00000270**<br>
Offsets: **0x78, 0x110, 0x738, 0x78, 0x60, 0x94**
<details>
<summary>Angle of View Image</summary>
<br>
<img src="https://raw.githubusercontent.com/N3agu/Drakensang-Internal/main/images/angle.png">
</details>

## Build
soon

## Improvements
- code refractoring
- finding entity list

## Credits
- CheatEngine's Forum - [post on ThreadStack](https://forum.cheatengine.org/viewtopic.php?p=5487976#5487976)
- [5aava's ThreadStack finder for x64](https://github.com/5aava/cheatengine-threadstack-finder-x64)

## License
Drakensang Internal is licensed under the [MIT license](https://github.com/N3agu/Drakensang-Internal/blob/main/LICENSE).

## Disclaimer
- This project is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
- This project is for learning purposes only and strictly prohibited for any illegal activities. Users bear full responsibility for any misuse.
