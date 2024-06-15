# Welcome in AurorOS GitHub!

<img align="right" src="https://avatars.githubusercontent.com/u/157804013?s=200&u=2ce38e6b2cf8349677f2b71a805238a6a8e1c454&v=2" style="width:128px;">

Here are the developed by Interpuce Team AurorOS source code basically for the preview how AurorOS actually works!

> [!CAUTION]
> **Working with code is really restricted with license.** Check it before doing anything! It is NOT the joke.

## Table of Contents

* [Compilation](#compilation)

## Compilation

1. Open Ubuntu / Debian terminal.

2. Use this command to update everything:

    ```sudo apt-get update```

3. Use these commands to install required items:

    ```sudo apt-get install build-essential gcc make nasm qemu-system-x86 ovmf```
    ```sudo apt-get install gnu-efi```

4. Make the OS from Makefile:

    ```make```