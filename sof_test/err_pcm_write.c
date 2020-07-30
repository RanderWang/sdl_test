// SPDX-License-Identifier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may do so under either license.
//
// Copyright(c) 2020 Intel Corporation. All rights reserved.
//
// Author: Rander wang <Rander.wang@linux.intel.com>
//
#include <alsa/asoundlib.h>
#include <alsa/pcm.h>
#include "err_pcm.h"

int err_pcm_writei(snd_pcm_t *handle)
{
	int buf[128];
	int err;

	err = snd_pcm_writei(NULL, buf, 128);
	if (err == 128) {
		printf("failed to detect error when writing data to NULL pcm %d", err);
		return -EINVAL;
	}

	err = snd_pcm_writei(handle, buf, 256);
	if (err == 256) {
		printf("failed to detect error when writing data of 256 byte to pcm %d", err);
		return -EINVAL;
	}

	return 0;
}

int err_pcm_writei_check(snd_pcm_t *handle)
{
	char buf[128];
	int err;

#if ERR_WRITE_CHECK
	err = err_pcm_writei(handle);
	if (err)
		return err;
#endif

	err = snd_pcm_writei(handle, buf, 128);
	if (err != 128) {
		printf("failed to write data to pcm %d", err);
		return -EINVAL;
	}

	return 0;
}

