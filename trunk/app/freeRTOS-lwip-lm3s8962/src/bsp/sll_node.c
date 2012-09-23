/*
 * sll_node.c
 *
 *  Created on: 2012-5-15
 *      Author: moveR
 */
#include <stdlib.h>
#include <stdint.h>
#include "sll_node.h"


node *creatList( int num )
{
	int i;
	node *list, *plist;

	if((num < 1)||(num > 255))
	{
		return NULL;
	}

	list = (node *)malloc(sizeof(node));   //给结点申请空间
	if(list != NULL)
	{
		list->next = NULL;
		plist = list;
		for(i = 1;i < num;i ++)
		{
			list = (node *)malloc(sizeof(node));
			if(list != NULL)
			{
				list->next = plist;
				plist = list;
			}
			else
			{
				return plist;
			}
		}
		return list;
	}
	else
	{
		return NULL;
	}
}

uint8_t add_Node( node **l, int value)
{
	node *p;

	p = (node *)malloc(sizeof(node));

	if(p == NULL)
		return 0;
	p->next = *l;
	p->value = value;
	*l = p;
	return 1;
}

uint8_t remove_Node(node **l, int value)
{
	node *p, *pre;

	p = *l;
	pre = p;

	while( p != NULL )
	{
		if(p->value == value)
		{
			if(p == *l)
			{
				*l = p->next;
				free(p);
				return 1;
			}
			else
			{
				pre->next = p->next;
				free(p);
				return 1;
			}
		}
		else
		{
			pre = p;
			p = p->next;
		}
	}
	return 0;
}

node *find_Node(node **l, int value)
{
	node *p;
	p = *l;

	while(p != NULL)
	{
		if (p->value == value)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

