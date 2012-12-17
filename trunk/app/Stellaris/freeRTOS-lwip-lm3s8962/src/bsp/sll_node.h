/*
 * sll_node.h
 *
 *  Created on: 2012-5-15
 *      Author: moveR
 */

#ifndef SLL_NODE_H_
#define SLL_NODE_H_

typedef struct node
{
	struct node *next;
	int value;
	char ip[16];
	char uid[4];
} node;

extern node *creatList(int num);
extern uint8_t add_Node(node **l, int value);
extern uint8_t remove_Node(node **l, int value);
extern node *find_Node(node **l, int value);

#endif /* SLL_NODE_H_ */
