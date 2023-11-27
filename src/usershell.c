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

#include "config.h"

#include <unistd.h>
#include <paths.h>
#include <pthread.h>
#include <libeconf.h>

#include "usershell_econf.h"

struct data_t
{
  econf_file *key_file;
  char **keys;
  size_t key_number;
  size_t next_key;
};

static struct data_t global_data = {NULL, NULL, 0, 0};
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void
internal_endusershell (struct data_t *data)
{
  if (data->key_file != NULL)
    {
      econf_free (data->key_file);
      data->key_file = NULL;
    }
  if (data->keys)
    {
      econf_free (data->keys);
      data->keys = NULL;
    }
  data->key_number = 0;
  data->next_key = 0;
}

static void
internal_setusershell (struct data_t *data)
{
  econf_err error;

#ifdef  HAVE_ECONF_READCONFIG
  error = econf_readConfig (&(data->key_file), NULL, USRDIR,
			  "shells", NULL, "", "#");
#else
  error = econf_readDirs (&(data->key_file), USRDIR, "/etc",
			  "shells", NULL, "", "#");
#endif
  if (error)
    {
      internal_endusershell (data);
      return;
    }

  error = econf_getKeys (data->key_file, NULL,
			 &(data->key_number), &(data->keys));
  if (error)
    {
      internal_endusershell (data);
	  return;
    }
  data->next_key = 0;
}

void
setusershell_econf (void)
{
  pthread_mutex_lock (&lock);

  if (global_data.key_file != NULL)
    internal_endusershell (&global_data);

  internal_setusershell (&global_data);

  pthread_mutex_unlock (&lock);
}

void
setusershell (void)
{
  setusershell_econf ();
}

void
endusershell_econf (void)
{
  pthread_mutex_lock (&lock);
  internal_endusershell (&global_data);
  pthread_mutex_unlock (&lock);
}

void
endusershell (void)
{
  endusershell_econf ();
}

static char *
internal_getusershell (struct data_t *data)
{
  if (data->key_file == NULL || data->key_number == 0 ||
      data->next_key >= data->key_number)
    return NULL;

  return data->keys[data->next_key++];
}

char *
getusershell_econf (void)
{
  char *shell;

  pthread_mutex_lock (&lock);

  if (global_data.key_file == NULL)
    internal_setusershell(&global_data);

  shell = internal_getusershell (&global_data);

  pthread_mutex_unlock (&lock);

  return shell;
}

char *
getusershell (void)
{
  return getusershell_econf ();
}

bool
checkusershell_econf (const char *shell)
{
  struct data_t data = {NULL, NULL, 0, 0};
  bool exists = false;

  if (data.key_file == NULL)
    internal_setusershell(&data);

  char *val = NULL;
  if (!econf_getStringValue (data.key_file, NULL, shell, &val))
    exists = true;

  if (val)
    free (val);

  internal_endusershell (&data);

  return exists;
}
