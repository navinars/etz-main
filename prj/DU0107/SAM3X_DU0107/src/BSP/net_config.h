/**
 * \file
 *
 * \brief User board configuration template
 *
 */

#ifndef NET_CONFIG_H
#define NET_CONFIG_H

typedef struct{
	uint8_t mode;
	uint8_t ip[4];
	uint8_t mask[4];
	uint8_t mac[4];
}ip_save_t;

extern ip_save_t IPsave;
extern ip_save_t IPsave_tmp;


void netmode_init(void);

#endif
