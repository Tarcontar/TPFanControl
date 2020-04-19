# TPFanControl

This is a fork of https://github.com/cjbdev/TPFanControl. I've added a small fix to allow TPFanControl to turn off both fans on Lenovo ThinkPad P53 when temperature drops below 50C. This has only been tested on my P53 notebook. A working release build is included in releases area, but it will need to be run each boot, or added to run at startup. 

I use Visual Studio 2019 to build the project, earlier/later versions may work as well but are not tested.

## Motivation
As you probably know, Lenovo completely screwed up fan controlling code on Lenovo ThinkPad P53. There is a bug in either BIOS or Lenovo Windows drivers which results in a very long delay between a temperature event and the fan speedup or slowdown. Effectively, the fans follow a temperature that was actual a long time ago. Also on my machine fans do not turn off completely even after temperature goes below 50C. And I want my P53 notebook to be completely silent under no load. See this thread on Lenovo Community forum for details:
https://forums.lenovo.com/t5/ThinkPad-P-and-W-Series-Mobile/P53-CPU-power-management-and-cooling-bugs/td-p/4596511.

## Requirements

To avoid errors, either install [tvicport](https://www.entechtaiwan.com/dev/port/index.shtm) manually or install the original version of TPFanControl found [here](https://thinkwiki.de/TPFanControl/), and run the dual-fan version instead of the original version.

## Installation
* Install TPFanControl from here: https://thinkwiki.de/TPFanControl. I'm using "latest common version, autostart by registry key as setup option, bug fixing, new options: startup in manual mode with manual fan speed adjustable, widget stays on top, optional slim widget. NEW: Hotkey integration." Direct download link to the installer: http://thinkwiki.de/tpfancontrol/tpfc_v062.zip.

* Copy TPFanControl.exe and TPFanControl.ini from this repository [releases area](https://github.com/stenri/TPFanControl/releases) over the installed files.

* Stop "Lenovo Intelligent Thermal Solution" service and set to "Startup type: Disabled". At some point I noticed GPU fan is spinning like crazy despite max sensors temperature being below 50C as reported by TPFanControl. After I stopped "Lenovo Intelligent Thermal Solution" service, left fan's speed immediately went down. So "Lenovo Intelligent Thermal Solution" can interfere with TPFanControl. 

* I've also uninstalled "Lenovo Intelligent Thermal Solution" drivers. After you run Thermal Solution installer from Lenovo website, see where it unpacks temporary files and run this command from this folder: "dpinst.exe /U LITSDrv.inf" to uninstall Thermal Solution drivers. Not sure if this step is necessary.

## Running at startup

The easiest way to run TPFC at startup is:

- Right-click on TPFanControl.exe and select copy
- Press Windows-r or search for run in the start menu
- Type `shell:startup` in the run box
- Right click in the window that opens and select paste shortcut

Note: this won’t start TPFC until you reboot.

## License

The original TPFanControl code is in public domain. See this fork for public domain code:
https://github.com/cjbdev/TPFanControl
All my own patches are licensed under GNU GPL v3 license. See notice below and LICENSE file for details.

Copyright (c) Stanislav Vinokurov, 2020

This program is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with this program. If not, see < https://www.gnu.org/licenses/>.
