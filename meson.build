project(
  'usershell_econf',
  'c',
  meson_version : '>= 0.58.0',
  default_options : ['buildtype=debugoptimized',
  		  'default_library=shared',
                  'c_std=gnu11',
                  'prefix=/usr',
		  'b_pie=true',
                  'b_asneeded=false',
                  'b_lto=true',
		  'warning_level=2',],
  license : 'LGPLv2+',
  version : '1.0.0',
)

conf = configuration_data()
conf.set_quoted('USRDIR', get_option('usr-dir'))
conf.set('_GNU_SOURCE', 1)

cc = meson.get_compiler('c')
pkg = import('pkgconfig')
inc = include_directories('include')

possible_cc_flags = [
		  '-D_FORTIFY_SOURCE=2',
		  '-fstack-protector-strong',
		  '-funwind-tables',
		  '-fasynchronous-unwind-tables',
		  '-fstack-clash-protection',
		  '-Werror=return-type',
		  '-Wbad-function-cast',
		  '-Wcast-align',
		  '-Wcast-qual',
		  '-Winline',
		  '-Wmissing-declarations',
		  '-Wmissing-prototypes',
		  '-Wnested-externs',
		  '-Wshadow',
		  '-Wstrict-prototypes',
		  '-Wundef',
		  ]
add_project_arguments(cc.get_supported_arguments(possible_cc_flags), language : 'c')

libusershell_econf_src = files(
  'src/usershell.c'
)

mapfile = 'src/libusershell_econf.map'
version_flag = '-Wl,--version-script,@0@/@1@'.format(meson.current_source_dir(), mapfile)

libeconf_dep = dependency('libeconf', version : '>= 0.4.9')

if cc.has_function('econf_readConfig',
                   prefix : '#include <libeconf.h>',
                   dependencies : libeconf_dep)
  conf.set('HAVE_ECONF_READCONFIG', 1)
endif

lib = library(
  'usershell_econf',
  libusershell_econf_src,
  include_directories : inc,
  install : true,
  link_args : version_flag,
  link_depends : mapfile,
  version : meson.project_version(),
  soversion : '1',
  dependencies : [libeconf_dep, ],
)

pkg.generate(
  lib,
  name : 'libusershell_econf',
  description : 'usershell functions using libeconf to read shells',
  version : meson.project_version(),
)

libusershell_econf_dep = declare_dependency(
  link_with : lib,
  include_directories : inc,
)

config_h = configure_file(
                 output : 'config.h',
                 configuration : conf)

# Unit tests
subdir('tests')
