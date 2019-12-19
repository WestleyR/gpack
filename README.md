# Simple, fast, rootless package and library manager

This is a basic package manager that can manage non-system (users) packages.

## Example

```bash
gpack install WestleyR/list-files
# downloads and installs lf

gpack remove WestleyR/list-files
# removes lf
```

Quick demo:

[![asciicast](https://asciinema.org/a/288403.svg)](https://asciinema.org/a/288403)

## Install

```
mkdir -p ~/.gpack
cd ~/.gpack

git clone https://github.com/WestleyR/gpack
cd gpack

make
make install # Dont use sudo!!!
```

`gpack` is installed in the users home directory, no root or sudo requiered.

#### Setting up your environment

Add the following lines to your `~/.bashrc`:

```
# For you installed commands
export PATH=${PATH}:${HOME}/.gpack/bin/

# For shared libraries at runtime
export LD_LIBRARY_PATH=${HOME}/.local/lib/:${LD_LIBRARY_PATH}

# For your c compiler to include the installed libraries
export CPATH=${HOME}/.local/include:${CPATH}
export LIBRARY_PATH=${HOME}/.local/lib:${LIBRARY_PATH}

# If Linux Ubuntu:
export GPACK_ARCH="X86_64_LINUX"
# Or if MacOS:
export GPACK_ARCH="MACOS"
# Or if raspberry pi zero
export GPACK_ARCH="ARMV6L"
```

If you are using macOS, then use `DYLD_LIBRARY_PATH` instead of `LD_LIBRARY_PATH`:

```
export DYLD_LIBRARY_PATH=${HOME}/.local/lib/:${LD_LIBRARY_PATH}
```

<br>

## Making your own package

Docs comming soon! As gpack is still in beta, things are changing.

<br>

### FAQ

 - Q: Does gpack support pre-compiled binaries?
   - A: Yes.

 - Q: What dependencies does gpack require?
   - A: Need gcc (or other c compiler) to compile gpack. Need `wget` and `tar` to download packages, and `git` for update,
   but also a couple other basic commands, like: `rm`, `cp`, `bash`, `ln`, which %99.99 of all systems have/support :)

 - Q: Can you uninstall gpack?
   - A: Yes; `rm -rf ~/.gpack` _NOTE: doing this will remove all packages that gpack installed._

 - Q: Can gpack handle shared c libraries?
   - A: Yes; installed and symlinked to `~/.local/lib` and `~/.local/include`.

 - Q: Where does gpack install packages?
   - A: In `~/.gpack/installed/<user>/<package_name>`, all binaries are symlinked to `~/.gpack/bin`, and can easily be uninstalled.

 - Q: Why use this when you can just use brew?
   - A: On a generic pc/laptop, it might make sence to use brew. But on a small, low power, low memory divice, thats where gpack comes in.
   Gpack is very fast, and small in size, making it very good for that use.

<br>

