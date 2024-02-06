
## Environment setup guide.

Most steps are similar for both windows and linux/macos operating systems.

1. Download and install ide [Visual studio code](https://code.visualstudio.com/).
2. Open extensions tab **Ctrl+Shift+X** for Windows. **Command+Shift+X** for MacOS. Or simply open it in UI by pressing appropriate  button.
3. Search for [C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) from Microsoft and install it.
4. Search for [PlatformIO IDE extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) from PlatformIO and install it. The installation may take some time.
5. After full installation of PlatformIO extension it will propose to open PlatformIO interface. You can do the same by clicking platformio logo.
6. Navigate to **Quick Access** menu and click **Platforms** option : QUICK ACCESS->PIO Home->Platforms. Ensure the package Espressif32 is installed. Otherwise click on  **Embedded** tab , find and install Espressif32 package.

[Video guide](https://www.youtube.com/watch?v=K-9oDE0-XsE)

---

## Windows driver installation.

In case you work on Windows OS you will need to install CH340 driver to upload the firmware for board. 

1. Download [CH340 driver](https://www.wch.cn/downloads/CH341SER_EXE.html)
2. Install the driver manually or just use driver setup to do it.
3. Reboot your computer.

[Driver installation guide](https://electropeak.com/learn/how-to-install-ch340-driver/)

---

## Compiling project and uploading.

1. Download repository then unzip it and open folder with project from PlatformIO UI by clicking **QUICK ACCESS->PIO Home->Open->Open Project**.
2. **This step is extremely important. Pay attention not to skip it**. Press File Explorer tab and go to **lib/BLE_changed_library**. Copy **BLEHIDDEVICE.cpp** and **BLEHIDDEVICE.hpp** files. You should navigate to your profile. It is **C:/Users/VVI** for me. Move to **.platformio/packages/framework-arduinoespressif32/libraries/BLE/src** and replace the existing files by copied from BLE_changed_library. The full path for me looks like **C:/Users/VVI/.platformio/packages/framework-arduinoespressif32/libraries/BLE/src**. Enable showing hidden folders if you can't find .platformio directory.
3. Compile the project. Return back to PlatformIO user interface and press **PROJECT TASKS->General->Build**.
4. After successful compilation upload the firmware on board. Press **PROJECT TASKS->General->UPLOAD**.
