/**
 * \file
 *
 * \brief User board configuration template
 *
 */

#ifndef NET_CONFIG_H
#define NET_CONFIG_H

typedef struct{
	uint8_t			alloc;
	uint8_t			mode;
	uint8_t			ip[4];
	uint8_t			mask[4];
	uint8_t			mac[5];
}f_ip_config_t;

extern f_ip_config_t f_ip_config_tmp;
extern f_ip_config_t f_ip_config;


void f_config_handle(void);

#endif
