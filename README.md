# LinuxFontInstallerGUI
Very simple Font Installer for Linux Systems for .ttf and .otf files.

Using Gtkmm 4.

All installed Fonts are in ~/.fonts/

### Usage
Open the application, press "Add" and select the folder containing the Fonts(No sub-folders).
Press "Install Font/s" and you are done.

### Compile
Make sure you have installed gtkmm 4.
To compile (in project dir):
```
cmake -S . -B build/
make -C ./build
```
# Preview
![screenshot](https://github.com/Banner244/LinuxFontInstallerGUI/blob/main/screens/usage.gif)
