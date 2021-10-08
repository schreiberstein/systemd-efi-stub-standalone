## systemd efi stub - standalone version

This repository contains a minimal version of the meson-based systemd build environment and the required source files to build a standalone version of the excellent systemd efi stub - **that is, without actually building the entire systemd source tree.** In less than two seconds!



To get more information about the systemd efi stub itself, check out its [official documentation](https://www.freedesktop.org/software/systemd/man/systemd-stub.html).



### Use case

I experiment with the systemd efi stub quite a lot and found it quite impractical to build the entire systemd suite just to get down to the ~90K EFI stub executable. Especially because of all the additional dependencies, amount of configuration and compilation time that is required for building systemd. And since I have not found a clean way to disable all other components in the upstream configuration, I just went ahead and stripped out everything that appeared to be unrelated to the precious EFI stub build process and prepared it for redistribution.



### Source / Origin

The systemd source code files used in this repository were imported from the [upstream systemd repository](https://github.com/systemd/systemd) .

The last import was performed with the following version:

**2021-10-08 - v249 - commit [#20966](https://github.com/systemd/systemd/pull/20966) **



*All source code files required for building the systemd efi stub have been moved to a single source directory (/src). This includes: (src/boot/efi/\*), (src/fundamental\*) and (src/version/\*) from the original systemd tree. systemd-boot has also been removed.*



### Dependencies

A recent GNU/Linux system of a supported CPU architecture *(e.g. i386, amd64, arm64, ...)* is required.

**The build process depends on:**

- GCC (LLVM's linker is incompatible!)
- GNU-EFI
- meson
- ninja-build
- python3
- pkgconfig

##### On Debian GNU/Linux 11 Bullseye (amd64):

- build-essential
- meson
- ninja-build
- gnu-efi
- python3
- pkg-config



### Usage

In the repository directory, run the following commands:

```sh
make
make install
```

The Makefile serves as a tiny wrapper for the meson and ninja build process.

The latter **make install** command copies the final EFI stub *(and the ELF file it was generated from (for debugging / inspection))* to the (/install) subdirectory:

- *install/linuxx64.elf.stub (Only for debugging / inspection)*

- **install/linuxx64.efi.stub (For unified kernel images)**



```sh
make clean
```

The **make clean** command deletes both the (/build) and (/install) directories and allows you to cleanly rebuild the stub from scratch again.



### License

To the best of my knowledge, all systemd source files used in this repository are licensed under the terms of the **GNU Lesser General Public License (LGPL2.1)**, which is included in the [LICENSE.LGPL2.1](LICENSE.LGPL2.1) file.

All changes made by me, if even considered copyrightable, are hereby also published under the aforementioned terms.

**This repository is in no way affiliated with the systemd project.**



### Author

**Alexander Schreiber (schreiberstein) - 2021**

