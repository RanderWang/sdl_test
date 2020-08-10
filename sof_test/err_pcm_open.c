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

static int open_mode = 0;

int err_pcm_open_handle_check(snd_pcm_t *handle, snd_pcm_stream_t stream)
{
	snd_pcm_t *inv_handle = (snd_pcm_t *)0xdeadbeef;
	int err;
	err = snd_pcm_open(NULL, "default", stream, open_mode);
	if (!err) {
		printf("audio open error is not detected for NULL handle\n");
		return -EINVAL;
	}

	err = snd_pcm_open(&inv_handle, "default", stream, open_mode);
	if (!err) {
		printf("audio open error is not detected for invalide handle\n");
		return -EINVAL;
	}

	return 0;
}


int err_pcm_open_name_check(snd_pcm_t *handle, snd_pcm_stream_t stream)
{
	int err;

	err = snd_pcm_open(&handle, "abd\n", stream, open_mode);
	if (!err) {
		printf("audio open error is not detected for NULL\n");
		return -EINVAL;
	}

	err = snd_pcm_open(&handle, "0,100\n", stream, open_mode);
	if (!err) {
		printf("audio open error is not detected for non-existence device:0,100\n");
		return -EINVAL;
	}

	return 0;
}

int err_pcm_open_stream_check(snd_pcm_t *handle, snd_pcm_stream_t stream)
{
	char *pcm_name = "default";
	int err;

	err = snd_pcm_open(&handle, pcm_name, -1, open_mode);
	if (!err) {
		printf("audio open error is not detected for incorrect stream direction -1\n");
		return -EINVAL;
	}

	err = snd_pcm_open(&handle, pcm_name, 4, open_mode);
	if (!err) {
		printf("audio open error is not detected for incorrect stream direction 4\n");
		return -EINVAL;
	}

	return 0;
}

int err_pcm_open_mode_check(snd_pcm_t *handle, snd_pcm_stream_t stream)
{
	char *pcm_name = "default";
	int err;

	err = snd_pcm_open(&handle, pcm_name, stream, -1);
	if (!err) {
		printf("audio open error is not detected for incorrect open mode -1\n");
		return -EINVAL;
	}

	err = snd_pcm_open(&handle, pcm_name, stream, 0x100000);
	if (!err) {
		printf("audio open error is not detected for incorrect open mode 0x100000\n");
		return -EINVAL;
	}

	return 0;
}

int err_pcm_open_check(snd_pcm_t *handle, snd_pcm_stream_t stream)
{
	int err;

#if ERR_OPEN_CHECK
        err = err_pcm_open_handle_check(handle, stream);
	if (err)
		return err;

	err = err_pcm_open_stream_check(handle, stream);
	if (err)
		return err;

	err = err_pcm_open_name_check(handle, stream);
	if (err)
		return err;

	err = err_pcm_open_mode_check(handle, stream);
	if (err)
		return err;
#endif
}

