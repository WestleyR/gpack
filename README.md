# Simple, minimal, rootless package manager

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

Be sure to add `~/.gpack/bin` to you PATH.

<br>

### FAQ

 - Q: Do you have a precompiled binary for gpack?
   - A: Not yet, wip...

 - Q: What dependencies does gpack require?
   - A: Need gcc (or other c compiler) to compile gpack. Need `wget` and `tar` to download packages, and `git` for update.

 - Q: Can you uninstall gpack?
   - A: Yes; `rm -rf ~/.gpack` _NOTE: doing this will remove all packages that gpack installed._

 - Q: Where does gpack install packages?
   - A: In `~/.gpack/installed/<user>/<package_name>`, all binaries are symlinked to `~/.gpack/bin`, and can easily be uninstalled.


<br>

