# Holberton School - Blockchain

This repository contains a basic implementation of a blockchain.

## Requirements

- [GCC](https://gcc.gnu.org/) (see [`gcc(1)`](https://www.man7.org/linux/man-pages/man1/gcc.1.html) for details)
- [make](https://www.gnu.org/software/make/) (see [`make(1)`](https://man7.org/linux/man-pages/man1/make.1.html) for details)
- [OpenSSL](https://www.openssl.org/) shared library
- [pthreads](https://en.wikipedia.org/wiki/Pthreads) shared library (see [`pthreads(7)`](https://man7.org/linux/man-pages/man7/pthreads.7.html) for details)

*NOTE: For installing the above dependencies, defer to your distro's package manager.*

## Build Instructions

### Install the `llist` shared library

To install the `llist` shared library from the [`llist`](llist/) directory, execute the following commands from the root of the repository:

```sh
cd llist
sudo ./install.sh
```

*NOTE: The `llist` library can be uninstalled by running [`uninstall.sh`](llist/uninstall.sh) from the [`llist`](llist/) directory.*

### Build the `libhblk_crypto` static library

To make the `libhblk_crypto` static library from the [`crypto`](crypto/) directory, execute the following commands from the root of the repository:

```sh
cd crypto
make
```

### Build the `libhblk_blockhain` static library (version 0.3)

To make the `libhblk_blockhain` static library from the [`blockchain/v0.3`](blockchain/v0.3/) directory, execute the following commands from the root of the repository:

```sh
cd blockchain/v0.3
make
```

### Build the CLI

To make the `libhblk_blockhain` static library from the [`blockchain/v0.3`](blockchain/v0.3/) directory, execute the following commands from the root of the repository:

```sh
cd cli
make
```

## Usage

The CLI may be used to interact with the blockchain. To run the CLI, execute the following command from the root of the repository:

```sh
cli/cli
```

If execution fails with an error message indicating that the `libllist` library cannot be found, temporarily add `/usr/local/lib` to the linker's search paths by running the CLI from the root of the repository with the following command:

```sh
LD_LIBRARY_PATH="${LD_LIBRARY_PATH:+${LD_LIBRARY_PATH}}:/usr/local/lib" cli/cli
```

The commands available in the CLI are as follows:

| Command     | Usage                 | Description                                     |
| ----------- | --------------------- | ----------------------------------------------- |
| exit        | `exit`                | Exit.                                           |
| help        | `help [COMMAND]`      | Display information about available commands.   |
| info        | `info`                | Display information about the local blockchain. |
| load        | `load PATH`           | Load blockchain from a file.                    |
| mine        | `mine`                | Mine a block.                                   |
| save        | `save PATH`           | Save blockchain to a file.                      |
| send        | `send AMOUNT ADDRESS` | Send coins.                                     |
| wallet_load | `wallet_load PATH`    | Load wallet from a file.                        |
| wallet_save | `wallet_save PATH`    | Save wallet to a file.                          |

## Authors

- Patrick DeYoreo - <pdeyoreo@gmail.com>
