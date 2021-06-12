# Simple, fast, users (rootless) package manager

Gpack; the fast, lightweight, memory leak-free package manager for users (non-root).

_**NOTE:** the gpack workflow/code is being updated. Some packages may not work._

## Example

For this example, lets install a [srm](https://github.com/WestleyR/srm): (rm command with undo/caching)

```bash
gpack install WestleyR/srm
# downloads and installs the srm command

gpack remove WestleyR/srm
# removes srm
```

## Install

Gpack is installed in `~/.gpack`, so first create that directory and clone the
gpack repo:

```
mkdir ~/.gpack
cd ~/.gpack

git clone https://github.com/WestleyR/gpack
cd gpack

make
make install # Dont use sudo!!!
```

_**NOTES:**_

 1. `gpack` is installed in the users home directory, so that user should install it. No root or sudo required.
 2. Make sure you download gpack using `git`, (dont download zip) otherwise gpack cant update itself.

### Setting up your environment

Add the following lines to your `~/.bashrc`, or `~/.bash_profile`, or whatever you prefer:

```
# For you installed commands
export PATH=${PATH}:${HOME}/.local/bin/

# For shared libraries at runtime
export LD_LIBRARY_PATH=${HOME}/.local/lib/:${LD_LIBRARY_PATH}

# For your c compiler to include the installed libraries
export CPATH=${HOME}/.local/include:${CPATH}
export LIBRARY_PATH=${HOME}/.local/lib:${LIBRARY_PATH}

# If Linux Ubuntu:
export GPACK_ARCH="x86_64_linux"
# Or if MacOS:
export GPACK_ARCH="macos"
# Or if raspberry pi zero (or other raspberry pi)
export GPACK_ARCH="armv6l"
```

If you are using macOS, then use `DYLD_LIBRARY_PATH` instead of `LD_LIBRARY_PATH`:

```
export DYLD_LIBRARY_PATH=${HOME}/.local/lib/:${LD_LIBRARY_PATH}
```

### Testing the install

To test your install, try to install a package, like:

```
gpack install WestleyR/list-files

# Run the command
lf
```

## Memory leak test

This package manager is designed to be memory leak-free! Heres an example of installing
a package: (clipped output from valgrind)

```
==32286== Command: ./gpack install WestleyR/srm
==32286== 
I: Installing: WestleyR/srm ...
I: Installing srm...
I: Downloading binary for armv6l...
I: Done installing WestleyR/srm
I: Total installed files: 21
==32286== 
==32286== HEAP SUMMARY:
==32286==     in use at exit: 0 bytes in 0 blocks
==32286==   total heap usage: 106 allocs, 106 frees, 1,813,810 bytes allocated
==32286== 
==32286== All heap blocks were freed -- no leaks are possible
```

As you can see, there are no memory leaks! And only using a total of 1.8Mbs
of memory (which will be improved later...). _(some of the gpack commands may
not be leak-free, since this is the dev branch.)_

## Making your own package

Lets look at the `srm` package as an example:

```ini
UserName=WestleyR
Name=srm
Version=v2.0.0.a1

Note=This is a test message

[macOS]

TarballURL=https://github.com/WestleyR/srm/releases/download/v2.0.0.a1/srm-v2.0.0.a1-macos.tar.gz
SSUM=058e89d0
BIN_FILES=srm/2.0.0.a1/bin/srm

[x86_64_linux]

TarballURL=https://github.com/WestleyR/srm/releases/download/v2.0.0.a1/srm-v2.0.0.a1-x86_64_linux.tar.gz
SSUM=9efbbaed
BIN_FILES=srm/2.0.0.a1/bin/srm

[armv6l]

TarballURL=https://github.com/WestleyR/srm/releases/download/v2.0.0.a1/srm-v2.0.0.a1-armv6l.tar.gz
SSUM=5ba1a7bc
BIN_FILES=srm/2.0.0.a1/bin/srm

# This file is a .ini file without the extension
# vim: syntax=dosini
```

The `TarballURL` is the download URL to the zipped binary (tar.gz). And the
`BIN_FILES` is the path to the command/binary after the tarball is unzipped.

## FAQ

 - Q: Does gpack support pre-compiled binaries?
   - A: Yes. It is recomended to only use precompiled binaries.

 - Q: What dependencies does gpack require?
   - A: Need gcc (or other c compiler) to compile gpack. Need `wget` and `tar` to download packages, and `git` for update,
   but also a couple other basic commands, like: `rm`, `cp`, `bash`, `ln`, `wget` which %99.99 of all systems have/support :)

 - Q: Can you uninstall gpack?
   - A: Yes; `rm -rf ~/.gpack` _NOTE: doing this will remove all packages that gpack installed._

 - Q: Can gpack handle shared c libraries?
   - A: Yes; installed and symlinked to `~/.local/lib` and `~/.local/include`.

 - Q: Where does gpack install packages?
   - A: In `~/.gpack/installed/<user>/<package_name>`, all binaries are symlinked to `~/.gpack/bin`, and can easily be uninstalled.

## Disclaimer

Gpack is only a helper to download, install, update and remove packages (third
party software). It is up to you to make sure you follow and agree to that
softwares license.

## License

This project is licensed under the terms of the The Clear BSD License. See the
[LICENSE file](./LICENSE) for more details.

