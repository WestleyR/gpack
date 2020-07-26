# Simple checksum program

![](https://github.com/WestleyR/ssum/workflows/ssum%20CI/badge.svg)

This is a simple checksum program using CRC32.

## Install

Clone the source code:

```
git clone https://github.com/WestleyR/ssum
cd ssum/
./configure
make install-lib  # install the ssum.1.so library
make              # compile ssum
make install      # install ssum
```

Also, make sure you have added this to your `~/.bashrc`:

```
# For shared libraries at runtime
export LD_LIBRARY_PATH=${HOME}/.local/lib/:${LD_LIBRARY_PATH}

# For your c compiler to include the installed libraries
export CPATH=${HOME}/.local/include:${CPATH}
export LIBRARY_PATH=${HOME}/.local/lib:${LIBRARY_PATH}
```

The `LD_LIBRARY_PATH` is needed because ssum creates a shared library, and that
is linked to the ssum command. And the `PATH` is so you can install without
`sudo`.

Alternatively you can compile ssum without any shared library:

```
./configure --without-library
make
make install
```

Default prefixes:

```
PREFIX = $(HOME)/.local
```

This can be changed by passing `--prefix /some/prefix` to the `configure`
script.

<br>

## Example

```
$ ssum README.md
5cf6f79a README.md


$ ssum README.md configure > foo.ssum

$ ssum -c foo.ssum
README.md: OK
configure: OK
```

<br>

### Using the shared library for other projects

This also comes with a shared library (`libssum.1.so`) that other projects can
use. By default, it is installed in `~/.local/lib`, and the header file is in
`~/.local/include`. To make this accessible to your c compiler, you need to add
this to your `~/.bashrc` file:

```
export CPATH=${HOME}/.local/include:${CPATH}
export LIBRARY_PATH=${HOME}/.local/lib:${LIBRARY_PATH}
```

Then you just need to add this to your c file:

```c
#include <ssum.1.h>
```

And add this to your Makefile:

```
CFLAGS += -lssum.1
```

And remember to use `CFLAGS` after the source/object files.

If you dont have your `CPATH` or `LIBRARY_PATH` set, then you can use this instead:
_You should really be using the env vars, but this also works._

```
LDFLAGS += -L/home/westleyk/.lib -I/home/westleyk/.lib/include
```

#### Use gpack to install/manage the library (beta)

You can also use [gpack](https://github.com/WestleyR/gpack) to manage/install/update/remove the library, and
can be installed with:

```
gpack install WestleyR/lib-ssum
```

This will only install the ssum library to `~/.gpack/installed/*` and the
library and header file will be symlinked to `~/.local/lib` and
`~/.local/include`. You can also install the ssum command and library with
gpack:

```
gpack install WestleyR/ssum
```

_lib-ssum will be installed if not already, since lib-ssum is needed for ssum._

<br>

### Library API/functions

This documentation may be outdated. Please see the `include/ssum.1.h` file for more details.

### `const char* libssum_version();`

#### Parameters

Non.

#### Returns

The libssum version, like `v3.0.0, Dec 19, 2019`.


### `unsigned int crc32_hash(const unsigned char *message, int msg_len);`

#### Parameters

`message` is a string. `msg_len` is the length of the message/string.

#### Returns

The crc for the given `message`.


### `unsigned int crc32_file(FILE* fp);`

#### Parameters

`fp` is the open file to read from, read it as a binary file (`"rb"`).

#### Returns

The crc for the contents of the file.


### `int check_crc32_file(FILE* fp);`

#### Parameters

`fp` is the open file that contains the hash for a file. Open the file in read
mode, and non-binary (`"r"`).

#### Returns

Returns `0` (zero) if the checksum and file match. Returns `1` if it does not.
And `-1` if theres a other error.

<br>
