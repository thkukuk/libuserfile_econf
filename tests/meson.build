# This file builds and runs the unit tests

tst_getusershell1_exe = executable('tst-getusershell1', 'tst-getusershell1.c', include_directories : inc, dependencies : libusershell_econf_dep)
test('tst-getusershell1', tst_getusershell1_exe)
tst_getusershell2_exe = executable('tst-getusershell2', 'tst-getusershell2.c', dependencies : libusershell_econf_dep)
test('tst-getusershell2', tst_getusershell2_exe)
tst_checkusershell_exe = executable('tst-checkusershell', 'tst-checkusershell.c', include_directories : inc, dependencies : libusershell_econf_dep)
test('tst-checkusershell', tst_checkusershell_exe)

