# Using the terminal

The AurorOS has build-in console mode and terminal. Here's how you can use them.

## Table of contents

* [Basics](#basics)
    * [Special terminal characters](#special-terminal-characters)
    * [Paths (changing the current directory, creating a directory and deleting it)](#paths)

## Basics

When you launch AurorOS there are success / error messages. If GUI elements were not found or if you restarted to console mode system will boot to console mode.

In the screen of console mode or in the terminal there will be prompt like this:

```username@computer-name:~\```

You can input the commands using the keyboard like this:

```command first_argument second_argument etc```

> [!CAUTION]
> **Any command argument is interpretted by terminal by string.** Note this when building apps.

You can run command as administartor using the `admin` command (like `sudo` in Linux):

```admin command first_argument second_argument etc```

In AurorOS this command asks you for computer password (basically `root` user password defined in installation).

### Special terminal characters

When argument must contains spaces (paths, user-provided strings, etc.) or `|` character use quotes to normalize the argument like this:

`admin command first_arg "Hello |:>"`

Spaces separates arguments. When you type `command arg arg2` the arg is the first argument and the arg2 is second argument. Use `command "arg arg2"` to make the `arg arg2` one argument. 

The `|` character is used to provide the result of the command to the command after this character as the last argument.

### Paths (changing the current directory, creating a directory and deleting it)

When you on the `~` path (by default) use cd to move into another folder. You can use this command to move to `~/Desktop`:

```cd Dekstop```

You can also use path like `~/Dekstop` to go to `~/Dekstop` (NOT `~/~/Dekstop`):

```cd ~\\Dekstop```

> [!WARNING]
> **The `~` is special character in paths!** This character is used to represent home folder (`C:\user\`).

You can also use absolute paths like `C:\AurorOS` or use paths starts with `/` (**which is another special character in paths**) to go to folder from main drive folder.

You can go backwards using the `cd ..` command.

You can create folders using the `md` command like this:

```md ~/hello```

For deleting folders use this command:

```rd ~/hello```

> [!WARNING]
> **You can't delete AurorOS folder and user folder.** In AurorOS folder you cannot also delete subfolders.
