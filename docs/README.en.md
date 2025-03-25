# 🖥️ **EasyAdmin** - Windows Management with Commands

**EasyAdmin** is a convenient tool for managing the Windows system using simple commands. With it, you can control power, sound, processes, network, and many other aspects of the system. This tool is perfect for both task automation and quick command execution.

In this guide, you will learn how to use **EasyAdmin** in Python or directly via the command line to perform various operations.

---

## 🚀 **How to Use EasyAdmin in Python?**

To integrate **EasyAdmin** into your Python project, simply call it via the command line using the `subprocess` module. Follow the steps below to get started.

### 1️⃣ **Preparation**

1. Download **EasyAdmin** and place it in your project folder or any location accessible from the command line. For example, you can place it in the folder `C:\Tools\EasyAdmin`.
2. Ensure the path to **EasyAdmin** is added to the `PATH` environment variable, or use the full path when calling it.

### 2️⃣ **Import the subprocess Module**

To execute commands from Python, use the standard `subprocess` module. This module allows you to run commands in the command line directly from a Python script.

### 3️⃣ **Code Example**

Create a function for convenient execution of **EasyAdmin** commands:

```python
import subprocess

def run_easyadmin(command, param=""):
    """
    Executes an EasyAdmin command via the command line.

    :param command: The command to execute (e.g., 'volumemute').
    :param param: An additional parameter for the command (e.g., 'off').
    """
    command_str = f"EasyAdmin.exe {command} {param}" if param else f"EasyAdmin.exe {command}"
    try:
        subprocess.run(command_str, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Command execution error: {e}")
```

#### Usage Examples:

- **Mute Sound** 🔇:
  ```python
  run_easyadmin("volumemute")
  ```

- **Disable Wi-Fi** 🌐:
  ```python
  run_easyadmin("wifi", "off")
  ```

- **Reboot Computer** 🔄:
  ```python
  run_easyadmin("reboot")
  ```

---

## 💻 **Using EasyAdmin Without Python (via Command Line)**

If you are not using Python, you can call **EasyAdmin** directly from the command line (CMD). This is especially useful for quick task execution.

### Command Examples:

- **Decrease Volume** 🔉:
  ```console
  EasyAdmin.exe volumedown
  ```

- **Increase Volume** 🔊:
  ```console
  EasyAdmin.exe volumeup
  ```

- **Shut Down Computer** 🖥️:
  ```console
  EasyAdmin.exe shutdown
  ```

---

## 📜 **List of Available Commands**

| Command                        | Description                                                                                 |
|--------------------------------|---------------------------------------------------------------------------------------------|
| `lockscreen`                   | Lock the screen                                                                             |
| `volumedown`                   | Decrease volume                                                                             |
| `volumeup`                     | Increase volume                                                                             |
| `volumemute`                   | Mute sound                                                                                 |
| `nexttrack`                    | Next track                                                                                 |
| `prevtrack`                    | Previous track                                                                             |
| `playpause`                    | Play/Pause                                                                                 |
| `monitoroff`                   | Turn off the monitor                                                                       |
| `standby`                      | Put the system into standby mode                                                           |
| `logoff`                       | Log off the user account                                                                   |
| `reboot`                       | Reboot the system                                                                          |
| `shutdown`                     | Shut down the system                                                                       |
| `kill <process>`               | Terminate a process by name                                                                |
| `killpid <PID>`                | Terminate a process by PID                                                                 |
| `killnotresp`                  | Terminate unresponsive processes                                                           |
| `cdrom <drive> open|close`     | Open/Close the CD-ROM                                                                      |
| `brightness <0-100>`           | Set screen brightness                                                                      |
| `wifi <on|off>`                | Enable or disable Wi-Fi                                                                    |
| `sysinfo`                      | Display system information                                                                 |
| `open <path>`                  | Open a program                                                                             |

---

## 🛠️ **Helpful Tips**
1. **Task Automation**: You can use **EasyAdmin** in scripts to automate routine tasks, such as power or network management.

2. **Security**: Ensure you download **EasyAdmin** only from trusted sources to avoid malicious software.

---

## 📚 **Conclusion**

**EasyAdmin** is an open-source tool for Windows management that can be used in Python scripts or directly via the command line. It simplifies routine tasks and allows for system management automation.

Try **EasyAdmin** today and make your Windows experience easier and more convenient! 🚀