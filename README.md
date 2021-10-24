# Simple, fast, users (rootless) package manager

Gpack; the fast, lightweight, memory leak-free package manager for users (non-root).

_**NOTE:** the gpack workflow/code is being updated. Some packages may not
work. Run `gpack search` to see the available packages._

## Example

For this example, lets install a [srm](https://github.com/WestleyR/srm): (rm command with undo/caching)

```console
$ gpack install WestleyR/srm
# downloads and installs the srm command

$ gpack remove WestleyR/srm
# removes srm
```

To search or list for available packages, run:

```console
$ gpack search
WestleyR/srm
	Description: "here is some stuff about test"

WestleyR/gnotes
	Description: "here is some stuff about test"
```

_as you can see, this is still a beta project. if you want to contribute, please
open an issue or pull request._

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

### Setting up your environment

Add the following lines to your `~/.bashrc`, or `~/.bash_profile`, or whatever you prefer:

```bash
# For you installed commands
export PATH=${PATH}:${HOME}/.local/bin/
```

### Testing the install

To test your install, try to install a package, like:

```
gpack install WestleyR/srm
srm -V
```

You may need to create some cache/config directory.

## Memory leak test

**Yeah, there will be leaks now. Lots of changes in the code.**

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
not be leak-free, since this is the dev branch)_

## Making your own package

Please open an issue, or comment on the gist. The package list is currently
on github gist right now.

[Package list](https://gist.github.com/WestleyR/81b31029e8c02b5434ee8f9a4217af04)

## FAQ

 - Q: Does gpack support pre-compiled binaries?
   - A: Yes. In fact, it only supports pre-compiled binaries. Other competing
     package managers may only have building/compiling, which can have security
	 issues if you dont trust a package.

 - Q: What dependencies does gpack require?
   - A: Need gcc (or other c compiler) to compile gpack. Need `wget` and `tar` to download packages, and `git` for update,
   but also a couple other basic commands, like: `rm`, `cp`, `bash`, `ln`, `wget` which %99.99 of all systems have/support :)

 - Q: Can you uninstall gpack?
   - A: Yes; `rm -rf ~/.gpack` _NOTE: doing this will remove all packages that gpack installed._

 - Q: Can gpack handle shared c libraries?
   - A: ~Yes; installed and symlinked to `~/.local/lib` and `~/.local/include`.~ Not yet, since the code has changed a lot.

 - Q: Where does gpack install packages?
   - A: In `~/.gpack/installed/<user>/<package_name>`, all binaries are symlinked to `~/.local/bin`, and can easily be uninstalled.

## Disclaimer

gpack is only a helper to download, install, update and remove packages (third
party software). It is up to you to make sure you follow and agree to that
softwares license.

## License

This project is licensed under the terms of the The Clear BSD License. See the
[LICENSE file](./LICENSE) for more details.

