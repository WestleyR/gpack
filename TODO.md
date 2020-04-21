# Gpack TODO

 - [x] Make the install script look at 'bin', 'lib', and 'include' in the prefix to install stuff.
 - [x] Add -f flag when removing packages.
 - [x] Add y/n prompt before removing packages.
 - [x] Make the `package` dir a seprate repo.
 - [x] Document how to make a precompiled package.
 - [x] Document how to make a package.
 - [x] Handle `INSTALL_NOTES="blab"` and `NOTES="blab"` in package file.
 - [x] Add "c", "clang" to repo tags.
 - [x] Make `autoclean` clean the `~/.local/lib` and `~/.local/include` directories.
 - [ ] Make gpack install commands to `~/.local/bin`.
 - [ ] Autoclean after removing a package (maybe?...).
 - [x] Use a path join function in `utils.c`.
 - [x] Show version of package when listing them.
 - [x] There should be a "version" to always stay up-to-date with master (without redownloading it every time).
 - [x] Add dry-run for 'autoclean'.
 - [x] Fix 'list' so the output is aligned.
 - [x] Handle `--compile` flag when upgradding.
 - [x] Add a `search` command.
 - [x] Search should only search for names.
 - [x] Fix output when `upgrade`ing and theres nothing to upgrade.
 - [ ] After installing a package, should print `I: Done installing pkg_name`.
 - [x] Fix any issue after a clean install.
 - [x] Make a simple gist one file script handler.
 - [ ] Autoclean should remove unused (older version) of a package after upgrading it.
 - [x] Should count how many file are installed.

