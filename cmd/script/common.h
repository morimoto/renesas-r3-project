/* SPDX-License-Identifier: MIT
 *
 * common.h
 *
 * Copyright (c) 2023 Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#ifndef __COMMON_H
#define __COMMON_H

struct r4_i2c_priv;

#define rU32 unsigned int
#define rU16 unsigned short
#define rU8  unsigned char
rU32  r4_i2c_read(struct r4_i2c_priv *r4, int reg);
void  r4_i2c_write(struct r4_i2c_priv *r4, int reg, rU32 val);
void  r4_i2c_udelay(struct r4_i2c_priv *r4, unsigned int time);

#endif /* __COMMON_H */
