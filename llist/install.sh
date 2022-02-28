#!/usr//bin/env sh

PROGNAME="${0##*/}"

if test "$(id -u)" -ne 0
then
  >&2 printf '%s: must be executed as root\n' "${PROGNAME}"
  exit 1
fi

printf 'Installing library and headers ...\n'
cp libllist.so /usr/local/lib/
cp llist.h /usr/local/include/
ldconfig

printf 'Installing man pages ...\n'
mkdir -p /usr/local/man/man3
cp man/*.3 /usr/local/man/man3/
mandb

echo "Complete!"
exit 0
