#!/usr//bin/env sh

if test "$(id -u)" -ne 0
then
  >&2 echo "Must be executed as root"
  exit 1
fi

echo "Installing library and headers ..."
cp libllist.so /usr/local/lib/
cp llist.h /usr/local/include/
ldconfig

echo "Installing man pages ..."
mkdir -p /usr/local/man/man3
cp man/*.3 /usr/local/man/man3/
mandb

echo "Complete!"
