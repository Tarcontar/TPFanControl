# TPFanControl

This is a Fork of https://github.com/cjbdev/TPFanControl. I've added a small hack to allow TPFanControl to turn off both fans when temperature drops below 50C. This has only been tested on my Lenovo ThinkPad P53 notebook, but it should work on the P50, P70, P71, P52, P72, P1, and X1 Extreme as well, as well as any other dual-fan Thinkpads that are released. A working release build is included in releases area, but it will need to be run each boot, or added to run at startup. 

I use Visual Studio 2019 to build the project, earlier/later versions may work as well but are not tested.

## Requirements

To avoid errors, either install [tvicport](https://www.entechtaiwan.com/dev/port/index.shtm) manually or install the original version of TPFanControl found [here](https://sourceforge.net/projects/tp4xfancontrol/), and run the dual-fan version instead of the original version.

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
