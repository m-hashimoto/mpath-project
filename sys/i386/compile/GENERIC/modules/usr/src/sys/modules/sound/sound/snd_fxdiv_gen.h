#ifndef _SND_FXDIV_GEN_H_
#define _SND_FXDIV_GEN_H_

/*
 * Generated using snd_fxdiv_gen.awk, heaven, wind and awesome.
 *
 * DO NOT EDIT!
 */

#ifdef SND_USE_FXDIV

/*
 * Fast unsigned 32bit integer division and rounding, accurate for
 * x = 1 - 65536. This table should be enough to handle possible
 * division for 1 - 72 (more can be generated though..).
 *
 * 72 = SND_CHN_MAX * PCM_32_BPS, which is why....
 */

static const uint32_t snd_fxdiv_table[][2] = {
	[0x01] = { 0x0001, 0x00 },	/* x / 1  = (x * 1    ) >> 0  */
	[0x02] = { 0x0001, 0x01 },	/* x / 2  = (x * 1    ) >> 1  */
	[0x03] = { 0x2aab, 0x0f },	/* x / 3  = (x * 10923) >> 15 */
	[0x04] = { 0x0001, 0x02 },	/* x / 4  = (x * 1    ) >> 2  */
	[0x05] = { 0x0ccd, 0x0e },	/* x / 5  = (x * 3277 ) >> 14 */
	[0x06] = { 0x2aab, 0x10 },	/* x / 6  = (x * 10923) >> 16 */
	[0x07] = { 0x2493, 0x10 },	/* x / 7  = (x * 9363 ) >> 16 */
	[0x08] = { 0x0001, 0x03 },	/* x / 8  = (x * 1    ) >> 3  */
	[0x09] = { 0x0e39, 0x0f },	/* x / 9  = (x * 3641 ) >> 15 */
	[0x0a] = { 0x0ccd, 0x0f },	/* x / 10 = (x * 3277 ) >> 15 */
	[0x0b] = { 0x0ba3, 0x0f },	/* x / 11 = (x * 2979 ) >> 15 */
	[0x0c] = { 0x0aab, 0x0f },	/* x / 12 = (x * 2731 ) >> 15 */
	[0x0d] = { 0x09d9, 0x0f },	/* x / 13 = (x * 2521 ) >> 15 */
	[0x0e] = { 0x0925, 0x0f },	/* x / 14 = (x * 2341 ) >> 15 */
	[0x0f] = { 0x0889, 0x0f },	/* x / 15 = (x * 2185 ) >> 15 */
	[0x10] = { 0x0001, 0x04 },	/* x / 16 = (x * 1    ) >> 4  */
	[0x11] = { 0x00f1, 0x0c },	/* x / 17 = (x * 241  ) >> 12 */
	[0x12] = { 0x0e39, 0x10 },	/* x / 18 = (x * 3641 ) >> 16 */
	[0x14] = { 0x0ccd, 0x10 },	/* x / 20 = (x * 3277 ) >> 16 */
	[0x15] = { 0x0c31, 0x10 },	/* x / 21 = (x * 3121 ) >> 16 */
	[0x16] = { 0x0ba3, 0x10 },	/* x / 22 = (x * 2979 ) >> 16 */
	[0x18] = { 0x0aab, 0x10 },	/* x / 24 = (x * 2731 ) >> 16 */
	[0x1a] = { 0x09d9, 0x10 },	/* x / 26 = (x * 2521 ) >> 16 */
	[0x1b] = { 0x025f, 0x0e },	/* x / 27 = (x * 607  ) >> 14 */
	[0x1c] = { 0x0925, 0x10 },	/* x / 28 = (x * 2341 ) >> 16 */
	[0x1e] = { 0x0889, 0x10 },	/* x / 30 = (x * 2185 ) >> 16 */
	[0x20] = { 0x0001, 0x05 },	/* x / 32 = (x * 1    ) >> 5  */
	[0x21] = { 0x03e1, 0x0f },	/* x / 33 = (x * 993  ) >> 15 */
	[0x22] = { 0x00f1, 0x0d },	/* x / 34 = (x * 241  ) >> 13 */
	[0x24] = { 0x071d, 0x10 },	/* x / 36 = (x * 1821 ) >> 16 */
	[0x27] = { 0x0691, 0x10 },	/* x / 39 = (x * 1681 ) >> 16 */
	[0x28] = { 0x0667, 0x10 },	/* x / 40 = (x * 1639 ) >> 16 */
	[0x2a] = { 0x0619, 0x10 },	/* x / 42 = (x * 1561 ) >> 16 */
	[0x2c] = { 0x02e9, 0x0f },	/* x / 44 = (x * 745  ) >> 15 */
	[0x2d] = { 0x05b1, 0x10 },	/* x / 45 = (x * 1457 ) >> 16 */
	[0x30] = { 0x02ab, 0x0f },	/* x / 48 = (x * 683  ) >> 15 */
	[0x33] = { 0x0283, 0x0f },	/* x / 51 = (x * 643  ) >> 15 */
	[0x34] = { 0x04ed, 0x10 },	/* x / 52 = (x * 1261 ) >> 16 */
	[0x36] = { 0x025f, 0x0f },	/* x / 54 = (x * 607  ) >> 15 */
	[0x38] = { 0x0493, 0x10 },	/* x / 56 = (x * 1171 ) >> 16 */
	[0x3c] = { 0x0445, 0x10 },	/* x / 60 = (x * 1093 ) >> 16 */
	[0x40] = { 0x0001, 0x06 },	/* x / 64 = (x * 1    ) >> 6  */
	[0x44] = { 0x00f1, 0x0e },	/* x / 68 = (x * 241  ) >> 14 */
	[0x48] = { 0x038f, 0x10 },	/* x / 72 = (x * 911  ) >> 16 */
};

#define SND_FXDIV_MAX		0x00010000
#define SND_FXDIV(x, y)		(((uint32_t)(x) *			\
				    snd_fxdiv_table[y][0]) >>		\
				    snd_fxdiv_table[y][1])
#define SND_FXROUND(x, y)	(SND_FXDIV(x, y) * (y))
#define SND_FXMOD(x, y)		((x) - SND_FXROUND(x, y))

#else	/* !SND_USE_FXDIV */

#define SND_FXDIV_MAX		0x00020000
#define SND_FXDIV(x, y)		((x) / (y))
#define SND_FXROUND(x, y)	((x) - ((x) % (y)))
#define SND_FXMOD(x, y)		((x) % (y))

#endif	/* SND_USE_FXDIV */

#endif	/* !_SND_FXDIV_GEN_H_ */
