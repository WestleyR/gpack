# Simple, fast, rootless package and library manager

This is a basic package manager that can manage non-system (users) packages and
libraries.

**WARNING:** The package installer code is being rewritten, some packages may not work right now. New update will be completly written in pure C. See the `new-dev` branch for develpment.

## Example

```bash
gpack install WestleyR/list-files
# downloads and installs the lf command (list-files)

gpack remove WestleyR/list-files
# removes lf
```

Quick demo:

[![asciicast](https://asciinema.org/a/288403.svg)](https://asciinema.org/a/288403)

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

Add the following lines to your `~/.bashrc`:

```
# For you installed commands
export PATH=${PATH}:${HOME}/.gpack/bin/  # This will be in ~/.local/bin soon
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

<br>

## Making your own package

To make your own gpack package, you first need to decided if your package will
be updated whenever you push a new commit (always master), or only releases.

If you want to base you package of the releases (recommend), then you can use
this template file:

```sh
USR_NAME="your_username"
PKG_NAME="your_repo_name"
NAME="name_of_your_package" # Typical, this is the same as the PKG_NAME
PKG_VERSION="1.0.0" # Your package version (without the 'v' prefix)

TARBALL="https://github.com/${USR_NAME}/${PKG_NAME}/archive/v${PKG_VERSION}.tar.gz" # The URL for the tarball.
# Note: There is the 'v' prefix here, if you done use the 'v' prefix then remove it here.

# The sha256sum for your tarball
SHA256SUM="fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"

# This is the directory name of the un-tared package
UNTAR_DIR="${PKG_NAME}-${PKG_VERSION}"

# If you want to have pre-compiled binaries of you package, then you will need
# to add a assest on your release, it should be called 'repo-name-v1.0.0-x86_64_linux.tar.gz',
# eg. 'lf-v1.5.2-x86_64_linux.tar.gz'. This tarball should be a tared directory
# of your projects prefix, in its version, like: 'repo_name/1.0.0/bin/executable'
# eg. 'list-files/1.5.2/bin/lf'

# Linux Ubuntu
X86_64_LINUX_URL="https://github.com/${USR_NAME}/${PKG_NAME}/releases/download/v${PKG_VERSION}/lf-v${PKG_VERSION}-x86_64_linux.tar.gz"
X86_64_LINUX_SHA256SUM="ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"

# Macos
MACOS_URL="https://github.com/${USR_NAME}/${PKG_NAME}/releases/download/v${PKG_VERSION}/lf-v${PKG_VERSION}-macos.tar.gz"
MACOS_SHA256SUM="ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"

# Raspberry pi zero (and others)
ARMV6L_URL="https://github.com/${USR_NAME}/${PKG_NAME}/releases/download/v${PKG_VERSION}/lf-v${PKG_VERSION}-armv6l.tar.gz"
ARMV6L_SHA256SUM="ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"

# Load the prefix
. load_gpack ${PKG_NAME}

# This is the install command(s) for your project
INSTALL_CMD="make install PREFIX=${gpack_prefix}"
```

Now, if you want your package to always be up-to-date with master (gets updated
whenever theres a new commit), then you can use this template file:

```sh
USR_NAME="your_username"
PKG_NAME="your_repo_name"
NAME="name_of_your_package" # Tipicaly, this is the same as the PKG_NAME

# This will return a github commit hash, that will be used as the version.
# The 'get-json-value' command comes installed with gpack, so dont worry
# about that.
PKG_VERSION=`curl -s "https://api.github.com/repos/${USR_NAME}/${PKG_NAME}/commits/master" | get-json-value`

TARBALL="https://github.com/${USR_NAME}/${PKG_NAME}/archive/${PKG_VERSION}.tar.gz"

# This is the directory name of the un-tared package
UNTAR_DIR="${PKG_NAME}-*"

# Load the prefix
. load_gpack ${PKG_NAME}

INSTALL_CMD="./configure --prefix ${gpack_prefix} && make install"
```

By using this template, there is no sha256sum/checksum to verify with, thats
the downside of having your project "alwasys-up-to-date with master". Another
downside is that there is no pre-compiled binaries support for this.

### FAQ

 - Q: Does gpack support pre-compiled binaries?
   - A: Yes.

 - Q: What dependencies does gpack require?
   - A: Need gcc (or other c compiler) to compile gpack. Need `wget` and `tar` to download packages, and `git` for update,
   but also a couple other basic commands, like: `rm`, `cp`, `bash`, `ln`, `wget` which %99.99 of all systems have/support :)

 - Q: Can you uninstall gpack?
   - A: Yes; `rm -rf ~/.gpack` _NOTE: doing this will remove all packages that gpack installed._

 - Q: Can gpack handle shared c libraries?
   - A: Yes; installed and symlinked to `~/.local/lib` and `~/.local/include`.

 - Q: Where does gpack install packages?
   - A: In `~/.gpack/installed/<user>/<package_name>`, all binaries are symlinked to `~/.gpack/bin`, and can easily be uninstalled.

<br>

## Disclaimer

Gpack is only a helper to download, install, update and remove packages (third
party software). It is up to you to make sure you follow and agree to that
softwares license.

## License

This project is licensed under the terms of the The Clear BSD License. See the
[LICENSE file](LICENSE) for more details.

<br>

