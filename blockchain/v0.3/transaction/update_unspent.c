#include "transaction.h"

/**
 * find_unspent - find unspent matching a transaction output
 *
 * @node: current node, unspent_txo_t
 * @arg: txo id
 *
 * Return: 1 if found, otherwise 0
 */
static int find_unspent(llist_node_t node, void *arg)
{
	unspent_tx_out_t *utxo = node;

	if (!memcmp(utxo->out.hash, arg, SHA256_DIGEST_LENGTH))
		return (1);
	return (0);
}

/**
 * foreach_input - remove UTXOs matching the tx output referenced by tx input
 *
 * @node: current node, txi
 * @idx: index of node
 * @arg: arguments
 *
 * Return: Always 0
 */
static int foreach_input(
	llist_node_t node, unsigned int idx __attribute__((unused)), void *arg)
{
	void **args = arg;
	tx_in_t *txi = node;

	llist_remove_node(args[0], find_unspent, txi->tx_out_hash, 1, free);
	return (0);
}

/**
 * foreach_output - create UTXO for a tx output
 *
 * @node: current node, txo
 * @idx: index of node
 * @arg: arguments
 *
 * Return: Always 0
 */
static int foreach_output(
	llist_node_t node, unsigned int idx __attribute__((unused)), void *arg)
{
	void **args = arg;
	tx_out_t *txo = node;
	unspent_tx_out_t *utxo = unspent_tx_out_create(args[1], args[2], txo);

	if (utxo)
		llist_add_node(args[0], utxo, ADD_NODE_REAR);
	return (0);
}

/**
 * foreach_transaction - maps output to input transactions
 *
 * @node: current node, tx
 * @idx: index of node
 * @arg: arguments
 *
 * Return: Always 0
 */
static int foreach_transaction(
	llist_node_t node, unsigned int idx __attribute__((unused)), void *arg)
{
	transaction_t *tx = node;
	void **args = arg;
	void *new_args[3] = {args[0], args[1], tx->id};

	llist_for_each(tx->inputs, foreach_input, new_args);
	llist_for_each(tx->outputs, foreach_output, new_args);
	return (0);
}

/**
 * update_unspent - updates list of UTXOs
 *
 * @transactions: list of validate txs
 * @block_hash: hash of block containing txs
 * @all_unspent: list of all UTXOs
 *
 * Return: new UTXO list
 */
llist_t *update_unspent(
	llist_t *transactions, uint8_t block_hash[SHA256_DIGEST_LENGTH],
	llist_t *all_unspent)
{
	void *args[2] = {all_unspent, block_hash};

	llist_for_each(transactions, foreach_transaction, args);
	return (all_unspent);
}
