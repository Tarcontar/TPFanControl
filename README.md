# TPFanControl

This is a fork of https://github.com/cjbdev/TPFanControl. I've added a small fix to allow TPFanControl to turn off both fans on Lenovo ThinkPad P53 when temperature drops below 50C. This has only been tested on my P53 notebook. A working release build is included in releases area, but it will need to be run each boot, or added to run at startup. 

I use Visual Studio 2019 to build the project, earlier/later versions may work as well but are not tested.

## Motivation
As you probably know, Lenovo completely screwed up fan controlling code on Lenovo ThinkPad P53. There is a bug in either BIOS or Lenovo Windows drivers which results in a very long delay between a temperature event and the fan speedup or slowdown. Effectively, the fans follow a temperature that was actual a long time ago. Also on my machine fans do not turn off completely even after temperature goes below 50C. And I want my P53 notebook to be completely silent under no load. See this thread on Lenovo Community forum for details:
https://forums.lenovo.com/t5/ThinkPad-P-and-W-Series-Mobile/P53-CPU-power-management-and-cooling-bugs/td-p/4596511.

What I noticed is that when temperature goes below 50C if I set "Manual: Fan 0" mode in TPFanControl, left fan (responsible for GPU) often continues to work. But if I switch mode to "BIOS" for a short period of time, then set "Manual: Fan 1" mode, and then "Manual: Fan 0" mode, fans become silent.

So I developed a fix to automate this procedure in TPFanControl as doing this manually every time was quite annoying. At this point I did not dig deep into the low level code that works with I/O ports. But instead developed a quick fix that works a following (in pseudo-code):
```
if MaxTemp < 50 then
    Set mode to "BIOS";
    Sleep 1 sec;
    Set mode to "Manual: Fan 1";
    Sleep 1 sec;
    Set mode to "Manual: Fan 0";
```    
Then notebook remains silent while "ManModeExit" temperature is reached (see TPFanControl.ini config file). TPFanControl activates Smart profile which cools system temperature down to 50C, and the loop repeats.

This solution is meant to be a temporary fix while Lenovo fixes bugs in Thermal control code in BIOS/Lenovo Windows drivers.

## Requirements

To avoid errors, either install [tvicport](https://www.entechtaiwan.com/dev/port/index.shtm) manually or install the original version of TPFanControl found [here](https://thinkwiki.de/TPFanControl/), and run the dual-fan version instead of the original version.

## Installation
* Install TPFanControl from here: https://thinkwiki.de/TPFanControl. I'm using "latest common version, autostart by registry key as setup option, bug fixing, new options: startup in manual mode with manual fan speed adjustable, widget stays on top, optional slim widget. NEW: Hotkey integration." Direct download link to the installer: http://thinkwiki.de/tpfancontrol/tpfc_v062.zip.

* Copy TPFanControl.exe and TPFanControl.ini from this repository releases area over the installed files.


The following steps may not be necessary, but you can try them in case something does not work as expected:

* Stop "Lenovo Intelligent Thermal Solution" service and set to "Startup type: Disabled". At some point I noticed GPU fan is spinning like crazy despite max sensors temperature being below 50C as reported by TPFanControl. After I stopped "Lenovo Intelligent Thermal Solution" service, left fan's speed immediately went down. So "Lenovo Intelligent Thermal Solution" can interfere with TPFanControl. UPD: I noticed that after Windows 10 update Lenovo service is running, and fan controlling works fine. So probably this step is not needed.

* I've also uninstalled "Lenovo Intelligent Thermal Solution" drivers. After you run Thermal Solution installer from Lenovo website, see where it unpacks temporary files and run this command from this folder: "dpinst.exe /U LITSDrv.inf" to uninstall Thermal Solution drivers.

## Running at startup

The easiest way to run TPFC at startup is:

- Right-click on TPFanControl.exe and select copy
- Press Windows-r or search for run in the start menu
- Type `shell:startup` in the run box
- Right click in the window that opens and select paste shortcut

Note: this won’t start TPFC until you reboot.
