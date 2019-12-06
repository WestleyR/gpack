# Simple, fast, rootless package and library manager

WIP

## Example

```bash
gpack install WestleyR/list-files
# downloads and installs lf

gpack remove WestleyR/list-files
# removes lf
```

## Install

_WIP_

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

# optional (this helps other projects find your libries) (not nessary if you do the above)
export LDFLAGS="${LDFLAGS} -L${HOME}/.local/lib -I${HOME}/.local/include"
```

If you are using macOS, then use `DYLD_LIBRARY_PATH` instead of `LD_LIBRARY_PATH`:

```
export DYLD_LIBRARY_PATH=${HOME}/.local/lib/:${LD_LIBRARY_PATH}
```

<br>

### FAQ

 - Q: Do you have a precompiled binary for gpack?
   - A: Not yet, wip...

 - Q: What dependencies does gpack require?
   - A: Need gcc (or other c compiler) to compile gpack. Need `wget` and `tar` to download packages, and `git` for update.

 - Q: Can you uninstall gpack?
   - A: Yes; `rm -rf ~/.gpack` _NOTE: doing this will remove all packages that gpack installed._

 - Q: Can gpack handle shared c libraries?
   - A: Yes; installed and symlinked to `~/.local/lib` and `~/.local/include`.

 - Q: Where does gpack install packages?
   - A: In `~/.gpack/installed/<user>/<package_name>`, all binaries are symlinked to `~/.gpack/bin`, and can easily be uninstalled.

<br>

