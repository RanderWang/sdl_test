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

int err_pcm_prepare()
{
	int handle = 0xdeedbeef;
	int err;

	err = snd_pcm_prepare(NULL);
	if (!err) {
		error("failed to check NULL hand");
		return -EINVAL;
	}

	err = snd_pcm_prepare(&handle);
	if (!err) {
		error("failed to check NULL hand");
		return -EINVAL;
	}

	return 0;
}

int err_pcm_prepare_check(snd_pcm_t *handle)
{
	int err;

#ifdef ERR_CHECK
	err = err_pcm_prepare(NULL);
	if (err)
		return err;
#endif

	err = snd_pcm_prepare(handle);
	if (err) {
		error("failed to prepare pcm %s", snd_strerror(err));
		return err;
	}

	return 0;
}

