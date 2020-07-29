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

int err_pcm_close()
{
	int handle = 0xdeedbeef;
	int err;

	err = snd_pcm_close(NULL);
	if (!err) {
		error("failed to check NULL hand");
		return -EINVAL;
	}

	err = snd_pcm_close(&handle);
	if (!err) {
		error("failed to check NULL hand");
		return -EINVAL;
	}

	return 0;

}

int err_pcm_close_check(snd_pcm_t *handle)
{
	int err;

#ifdef ERR_CHECK
	err = err_pcm_close();
	if (err)
		return err;
#endif

	snd_pcm_close(handle);
	return 0;
}

