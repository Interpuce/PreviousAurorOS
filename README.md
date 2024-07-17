# Welcome in AurorOS GitHub!

<img align="right" src="https://avatars.githubusercontent.com/u/157804013?s=200&u=2ce38e6b2cf8349677f2b71a805238a6a8e1c454&v=2" style="width:128px;">

> [!WARNING]
> **AurorOS is in alpha stage.** Some documentation files can be fake!

Welcome to official (or forked) AurorOS GitHub repository. AurorOS is an OS created with passion by Interpuce Team (and other people who wanted to voluntarily get involved in the project). 

You can find here things like AurorOS drivers, Makefile, AurorOS kernel and other stuff created by Interpuce Team for AurorOS.

## Table of contents
- [Table of contents](#table-of-contents)
- [Downloading](#downloading)
    - [Stable and pre-release versions](#stable-and-pre-release-versions)
    - [Nightly builds](#nightly-builds)

## Downloading

This section describes how you can download AurorOS.

### Stable and pre-release versions

Simply download them from [Github Releases](https://github.com/Interpuce/AurorOS/releases)

### Nightly builds

It is not recommended to use this download option because it is often untested. 

Install the dependecies. This command was tested on Ubuntu:

```apt install git make gcc nasm```

Initialize the working directory:

```md AurorOS```

```cd AurorOS```

Download AurorOS from source code, using this command:

```git clone https://github.com/Interpuce/AurorOS.git --depth 1 .```

It will clone this repository as fast as possible to curent directory.

Finnally compile AurorOS:

```make```