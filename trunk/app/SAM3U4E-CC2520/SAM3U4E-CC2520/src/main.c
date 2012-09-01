/**
 * \file
 *
 * \brief Empty user application template
 *
 */
#include <stdint.h>
#include <stdbool.h>
#include <sysclk.h>
#include <spi.h>			// ASF import files.
#include <string.h>

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>

int main (void)
{
	sysclk_init();
	board_init();

	// Insert application code here, after the board has been initialized.
}
