#!/usr//bin/env sh

PROGNAME="${0##*/}"

if test "$(id -u)" -ne 0
then
  >&2 printf '%s: must be executed as root\n' "${PROGNAME}"
  exit 1
fi

printf 'Uninstalling library and headers ...\n'
rm -f /usr/local/lib/libllist.so
rm -f /usr/local/include/llist.h
ldconfig

printf 'Uninstalling man pages ...\n'
for relpath in man/*.3
do
  basename="${relpath##*/}"
  rm -f "/usr/local/man/man3/${basename}"
done
mandb

echo "Complete!"
exit 0
