#ifndef _CLI_H_
#define _CLI_H_

#include <stddef.h>

#include <llist.h>

#include "../crypto/hblk_crypto.h"
#include "../blockchain/v0.3/blockchain.h"
#include "../blockchain/v0.3/provided/provided.h"
#include "../blockchain/v0.3/transaction/transaction.h"

#define BLANK " \t\n"

#define PROMPT "> "

#define EXIT_NAME "exit"
#define EXIT_HELP "exit"
#define EXIT_DESC "Exit."

#define HELP_NAME "help"
#define HELP_HELP "help [COMMAND]"
#define HELP_DESC "Display information about available commands."

#define INFO_NAME "info"
#define INFO_HELP "info"
#define INFO_DESC "Display information about the local blockchain."

#define LOAD_NAME "load"
#define LOAD_HELP "load PATH"
#define LOAD_DESC "Load blockchain from a file."

#define MINE_NAME "mine"
#define MINE_HELP "mine"
#define MINE_DESC "Mine a block."

#define SAVE_NAME "save"
#define SAVE_HELP "save PATH"
#define SAVE_DESC "Save blockchain to a file."

#define SEND_NAME "send"
#define SEND_HELP "send AMOUNT ADDRESS"
#define SEND_DESC "Send coins."

#define WALLET_LOAD_NAME "wallet_load"
#define WALLET_LOAD_HELP "wallet_load PATH"
#define WALLET_LOAD_DESC "Load wallet from a file."

#define WALLET_SAVE_NAME "wallet_save"
#define WALLET_SAVE_HELP "wallet_save PATH"
#define WALLET_SAVE_DESC "Save wallet to a file."

/**
 * struct state_s - CLI state structure
 *
 * @status: status of the most recently executed command
 * @argc: command argument count
 * @argv: command argument vector
 * @line: command line buffer
 * @linesz: size of @line
 * @wallet: wallet
 * @blockchain: blockchain
 * @tx_pool: transaction pool
 */
typedef struct state_s
{
	int status;
	int argc;
	char **argv;
	char *line;
	size_t linesz;
	EC_KEY *wallet;
	blockchain_t *blockchain;
	llist_t *tx_pool;
} state_t;

typedef int (*command_func_t)(state_t *);

/**
 * struct command_s - CLI command structure
 *
 * @func: function associated with the command
 * @name: name of the command
 * @help: short help for the command
 * @desc: description of the command
 */
typedef struct command_s
{
	command_func_t func;
	char const *name;
	char const *help;
	char const *desc;
} command_t;

int cli_exit(state_t *state);
int cli_help(state_t *state);
int cli_info(state_t *state);
int cli_load(state_t *state);
int cli_mine(state_t *state);
int cli_save(state_t *state);
int cli_send(state_t *state);
int cli_wallet_load(state_t *state);
int cli_wallet_save(state_t *state);

command_t const *get_commands(void);
command_t const *find_command(char const *name);

void state_init(state_t *state);
void state_clear(state_t *state);

void print_hex_buffer(uint8_t const *buf, size_t len);

#endif /* _CLI_H_ */
