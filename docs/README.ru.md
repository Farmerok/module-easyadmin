# 🖥️ **EasyAdmin** - Управление Windows с помощью команд

**EasyAdmin** — это удобный инструмент для управления системой Windows с помощью простых команд. С его помощью вы можете управлять питанием, звуком, процессами, сетью и многими другими аспектами системы. Этот инструмент идеально подходит как для автоматизации задач, так и для быстрого выполнения команд.

В этом руководстве вы узнаете, как использовать **EasyAdmin** в Python или напрямую через командную строку для выполнения различных операций.

---

## 🚀 **Как использовать EasyAdmin в Python?**

Чтобы интегрировать **EasyAdmin** в ваш Python-проект, достаточно вызывать его через командную строку с использованием модуля `subprocess`. Следуйте шагам ниже, чтобы начать.

### 1️⃣ **Подготовка**

1. Скачайте **EasyAdmin** и поместите его в папку с вашим проектом или в любое место, доступное из командной строки. Например, вы можете разместить его в папке `C:\Tools\EasyAdmin`.
2. Убедитесь, что путь к **EasyAdmin** добавлен в переменную окружения `PATH`, либо используйте полный путь при вызове.

### 2️⃣ **Импорт модуля subprocess**

Для выполнения команд из Python используйте стандартный модуль `subprocess`. Этот модуль позволяет запускать команды в командной строке прямо из Python-скрипта.

### 3️⃣ **Пример кода**

Создайте функцию для удобного вызова команд **EasyAdmin**:

```python
import subprocess

def run_easyadmin(command, param=""):
    """
    Выполняет команду EasyAdmin через командную строку.

    :param command: Команда для выполнения (например, 'volumemute').
    :param param: Дополнительный параметр команды (например, 'off').
    """
    command_str = f"EasyAdmin.exe {command} {param}" if param else f"EasyAdmin.exe {command}"
    try:
        subprocess.run(command_str, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Ошибка выполнения команды: {e}")
```

#### Примеры использования:

- **Отключение звука** 🔇:
  ```python
  run_easyadmin("volumemute")
  ```

- **Отключение Wi-Fi** 🌐:
  ```python
  run_easyadmin("wifi", "off")
  ```

- **Перезагрузка компьютера** 🔄:
  ```python
  run_easyadmin("reboot")
  ```

---

## 💻 **Использование EasyAdmin без Python (через командную строку)**

Если вы не используете Python, вы можете вызывать **EasyAdmin** напрямую из командной строки (CMD). Это особенно полезно для быстрого выполнения задач.

### Примеры команд:

- **Уменьшение громкости** 🔉:
  ```console
  EasyAdmin.exe volumedown
  ```

- **Увеличение громкости** 🔊:
  ```console
  EasyAdmin.exe volumeup
  ```

- **Выключение компьютера** 🖥️:
  ```console
  EasyAdmin.exe shutdown
  ```

---

## 📜 **Список доступных команд**

| Команда                        | Описание                                                                                     |
|--------------------------------|----------------------------------------------------------------------------------------------|
| `lockscreen`                   | Заблокировать экран                                                                          |
| `volumedown`                   | Уменьшить громкость                                                                          |
| `volumeup`                     | Увеличить громкость                                                                          |
| `volumemute`                   | Отключить звук                                                                               |
| `nexttrack`                    | Следующий трек                                                                               |
| `prevtrack`                    | Предыдущий трек                                                                              |
| `playpause`                    | Воспроизведение/Пауза                                                                        |
| `monitoroff`                   | Выключить монитор                                                                            |
| `standby`                      | Перевести систему в режим ожидания                                                          |
| `logoff`                       | Выйти из учетной записи                                                                      |
| `reboot`                       | Перезагрузить систему                                                                        |
| `shutdown`                     | Выключить систему                                                                            |
| `kill <process>`               | Завершить процесс по имени                                                                   |
| `killpid <PID>`                | Завершить процесс по PID                                                                     |
| `killnotresp`                  | Завершить неотвечающие процессы                                                              |
| `cdrom <drive> open|close`     | Открыть/Закрыть CD-ROM                                                                       |
| `brightness <0-100>`           | Установить яркость экрана                                                                    |
| `wifi <on|off>`                | Включить или отключить Wi-Fi                                                                 |
| `sysinfo`                      | Показать информацию о системе                                                                |
| `open <path>`                  | Открыть программу                                                                            |

---

## 🛠️ **Полезные советы**
1. **Автоматизация задач**: Вы можете использовать **EasyAdmin** в скриптах для автоматизации рутинных задач, таких как управление питанием или сетью.

2. **Безопасность**: Убедитесь, что вы скачиваете **EasyAdmin** только из доверенных источников, чтобы избежать вредоносного ПО.

---

## 📚 **Заключение**

**EasyAdmin** — это инструмент с открытым исходным кодом для управления Windows, который можно использовать как в Python-скриптах, так и напрямую через командную строку. Он упрощает выполнение рутинных задач и позволяет автоматизировать управление системой.

Попробуйте **EasyAdmin** уже сегодня и сделайте свою работу с Windows проще и удобнее! 🚀