// SPDX-License-Identifier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may do so under either license.
//
// Copyright(c) 2020 Intel Corporation. All rights reserved.
//
// Author: Rander wang <Rander.wang@linux.intel.com>
//

struct hwparams{
	snd_pcm_format_t format;
	unsigned int channels;
	unsigned int rate;
};

#define error(...) do {\
	fprintf(stderr, "%s:%d: ", __func__, __LINE__); \
	fprintf(stderr, __VA_ARGS__); \
	putc('\n', stderr); \
} while (0)


#define ERR_CHECK 1

int err_pcm_open_check(snd_pcm_t *handle);
int err_pcm_hw_param_check(snd_pcm_t *handle, struct hwparams *hw_params);
int err_pcm_prepare_check(snd_pcm_t *handle);
int err_pcm_writei_check(snd_pcm_t *handle);
int err_pcm_close_check(snd_pcm_t *handle);

