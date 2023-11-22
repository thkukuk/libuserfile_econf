# usershell_econf

This is a small library replacing the `setusershell()`, `getusershell()` and `endusershell()` functions of glibc with a variant, which uses [libeconf](https://github.com/openSUSE/libeconf) to read the valid shells following the
[Configuration Files Specification](https://github.com/uapi-group/specifications/blob/main/specs/configuration_files_specification.md) of the
[Linux Userspace API Group](https://uapi-group.org/).


## Building and installing usershell_econf

### Building

usershell_econf requires [libeconf](https://manpages.opensuse.org/libeconf) in
version 0.4.9 or newer and meson version 0.58 or newer.

Building with meson is quite simple:

```shell
$ meson setup build
$ meson compile -C build
$ meson test -C build
```

If you want to build with the address sanitizer enabled, add
`-Db_sanitize=address` as an argument to `meson setup build`.

### Installing

```shell
$ sudo meson install -C build
```

## Usage

There are two ways to use the new functions:

### Override glibc functions

The glibc functions can be replaced without further code changes by additionally linking the application against `libusershell_econf`. It is important that the linker does not optimize away the library, this can happen if e.g. `as-needed` is used for linking.

### Use new function names

To avoid problems, it's recommended to modify the applications source code and exchange all function calls by appending `_econf` to them:

* setusershell() -> setusershell_econf()
* getusershell() -> getusershell_econf()
* endusershell() -> endusershell_econf()

Additional you need to include an additional header file:
`#include <usershell_econf.h>`

and link against `libusershell_econf`.

Example code:
```C
...
#include <usershell_econf.h>
...
int
main (void)
{
  char *shell;

...

  setusershell_econf ();
  while ((shell = getusershell_econf ()) != NULL)
    printf ("[%s]\n", shell);
  endusershell_econf ();
...
}
```

## Licensing

See the file COPYING for full text and copying restrictions.
