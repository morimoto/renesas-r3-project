// SPDX-License-Identifier: MIT
//
// main.c
//
// Copyright (c) 2022 Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct my_priv {
	int test;
	struct r4_i2c_priv *r4;
};
#define R4_TO_PRIV(r4) (struct my_priv *)(r4)->private

rU32 r4_i2c_read(struct r4_i2c_priv *priv, int reg)
{
	printf("read:  (reg)%08x\n", reg);

	/* avoid busy loop at r4_i2c_xfer_atomic() */
	if (reg == ICMSR)
		return WAIT_BUSY;

	return 0;
}

void r4_i2c_write(struct r4_i2c_priv *priv, int reg, rU32 val)
{
	printf("write: (reg)%08x / (val)%08x\n", reg, val);
}

void r4_i2c_udelay(struct r4_i2c_priv *priv, unsigned int time)
{
	printf("sleep %d sec\n", time);
}

void show_version(struct r4_i2c_priv *r4)
{
	struct my_priv *priv = R4_TO_PRIV(r4);

	printf("Version: %d.%d.%d",
	       R4_I2C_VERSION_MAJOR(r4),
	       R4_I2C_VERSION_MINOR(r4),
	       R4_I2C_VERSION_BUGFIX(r4));
	if (R4_I2C_VERSION_RC(r4))
		printf("-rc%d", R4_I2C_VERSION_RC(r4));
	printf("\n");

	/* You can use your own private date */
	priv->test += 10;
}

int main(void)
{
	struct r4_i2c_priv *r4;
	struct my_priv priv;
	rU8 data[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

	priv.test = 1;

	/*
	 * To use R4, it needs to "alloc" r4 via .alloc_size,
	 * and "zero init", "copy" it.
	 * Because each SoC code need to use own settings which
	 * OS side never care.
	 *
	 * R4 doesn't have such method, because
	 * how to alloc/init/copy are depends on each OS.
	 */
	r4 = malloc(  r4_i2c_rcar_gen3.alloc_size);
	memset(r4, 0, r4_i2c_rcar_gen3.alloc_size);
	memcpy(r4,   &r4_i2c_rcar_gen3, sizeof(r4_i2c_rcar_gen3));
	priv.r4 = r4;

	r4_i2c_probe(r4, &priv);
	r4_i2c_setup_speed(r4, 100 * 1000); /* 100 kHz */

	show_version(r4);

	r4_i2c_xfer_atomic(r4,
			   0, 1,
			   0xab, /* address */
			   data, 10);

	/*
	 * When you finish to use R4, you need to *free* priv.
	 * This is also OS dependent
	 */
	free(r4);

	return 0;
}
