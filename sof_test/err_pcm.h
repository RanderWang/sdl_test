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

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

#define ERR_OPEN_CHECK 0
#define ERR_HW_PARAM_CHECK 0
#define ERR_PREPARE_CHECK 0
#define ERR_WRITE_CHECK 0
#define ERR_CLOSE_CHECK 0

int err_pcm_open_check(snd_pcm_t *handle, snd_pcm_stream_t stream);
int err_pcm_hw_param_check(snd_pcm_t *handle, struct hwparams *hw_params);
int err_pcm_prepare_check(snd_pcm_t *handle);
int err_pcm_writei_check(snd_pcm_t *handle);
int err_pcm_readi_check(snd_pcm_t *handle);
int err_pcm_close_check(snd_pcm_t *handle);

