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
#include "err_pcm.h"

static snd_pcm_stream_t stream = SND_PCM_STREAM_PLAYBACK;
static int open_mode = 0;

int err_pcm_open_name_check(snd_pcm_t *handle)
{
	int err;

	err = snd_pcm_open(&handle, "abd", stream, open_mode);
	if (!err) {
		printf("audio open error is not detected for NULL");
		return -EINVAL;
	}

	err = snd_pcm_open(&handle, "0,100", stream, open_mode);
	if (!err) {
		printf("audio open error is not detected for non-existence device:0,100");
		return -EINVAL;
	}

	return 0;
}

int err_pcm_open_stream_check(snd_pcm_t *handle)
{
	char *pcm_name = "default";
	int err;

	err = snd_pcm_open(&handle, pcm_name, -1, open_mode);
	if (!err) {
		printf("audio open error is not detected for incorrect stream direction -1");
		return -EINVAL;
	}

	err = snd_pcm_open(&handle, pcm_name, 4, open_mode);
	if (!err) {
		printf("audio open error is not detected for incorrect stream direction 4");
		return -EINVAL;
	}

	return 0;
}

int err_pcm_open_mode_check(snd_pcm_t *handle)
{
	char *pcm_name = "default";
	int err;

	err = snd_pcm_open(&handle, pcm_name, stream, -1);
	if (!err) {
		printf("audio open error is not detected for incorrect open mode -1");
		return -EINVAL;
	}

	err = snd_pcm_open(&handle, pcm_name, stream, 0x100000);
	if (!err) {
		printf("audio open error is not detected for incorrect open mode 0x100000");
		return -EINVAL;
	}

	return 0;
}

int err_pcm_open_check(snd_pcm_t *handle)
{
	int err;

#if ERR_OPEN_CHECK
	err = err_pcm_open_stream_check(handle);
	if (err)
		return err;

	err = err_pcm_open_name_check(handle);
	if (err)
		return err;
#endif
}

