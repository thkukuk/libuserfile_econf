/* libusershell_econf.so: *usershell() functions using libeconf
   Copyright (C) 2023 Thorsten Kukuk

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with program; if not, see <https://www.gnu.org/licenses/>. */

#pragma once

/* Successive calls return the shells listed in `/etc/shells' via libeconf
   following the configuration files specification for hermetic /usr:
   https://github.com/uapi-group/specifications/blob/main/specs/configuration_files_specification.md */

extern void setusershell_econf (void);
extern char *getusershell_econf (void);
extern void endusershell_econf (void);
