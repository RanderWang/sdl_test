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

int err_pcm_hw_params_set_access(snd_pcm_t *handle, snd_pcm_hw_params_t *params)
{
	int err;

	err = snd_pcm_hw_params_set_access(handle, params, -1);
	if (!err) {
		error("failed to detect error for access mode -1");
		return -EINVAL;
	}

	err = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_LAST + 1);
	if (!err) {
		error("failed to detect error for access mode -1");
		return -EINVAL;
	}
	
	return 0;
}

int err_pcm_hw_params_set_format(snd_pcm_t *handle, snd_pcm_hw_params_t *params)
{
	int err;

	err = snd_pcm_hw_params_set_format(handle, params, -1);
	if (!err) {
		error("failed to detect incorrect format -1");
		return -EINVAL;
	}
	
	err = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_LAST + 1);
	if (!err) {
		error("failed to detect incorrect format %d", SND_PCM_FORMAT_LAST + 1);
		return -EINVAL;
	}

	return 0;
}

int err_pcm_hw_params_set_channels(snd_pcm_t *handle, snd_pcm_hw_params_t *params)
{
	int err;

	err = snd_pcm_hw_params_set_channels(handle, params, -1);
	if (!err ) {
		error("failed to detect incorrect Channels count  -1%d", err);
		return -EINVAL;
	}

	err = snd_pcm_hw_params_set_channels(handle, params, 16);
	if (!err ) {
		error("failed to detect incorrect Channels count 16 %d", err);
		return -EINVAL;
	}

	return 0;
}

int err_pcm_hw_params_set_rate_near(snd_pcm_t *handle, snd_pcm_hw_params_t *params)
{
	int rate = 48000;
	int dir = 2;
	int err;

	err = snd_pcm_hw_params_set_rate_near(handle, params, &rate, &dir);
	if (!err ) {
		error("failed to detect incorrect rate dir  2 %d", err);
		return -EINVAL;
	}

	rate = -1;
	dir = 1;
	err = snd_pcm_hw_params_set_rate_near(handle, params, &rate, &dir);
	if (!err ) {
		error("failed to detect incorrect rate dir 1 for -1 %d", err);
		return -EINVAL;
	}

	return 0;
}

int err_pcm_hw_params(snd_pcm_t *handle, snd_pcm_hw_params_t *params)
{
	snd_pcm_hw_params_t *blank_params ;
	int err;

	snd_pcm_hw_params_alloca(&blank_params);

	err = snd_pcm_hw_params(handle, NULL);
	if (!err ) {
		error("failed to detect incorrect params %d", err);
		return -EINVAL;
	}

	err = snd_pcm_hw_params(handle, blank_params);
	if (!err ) {
		error("failed to detect blank params %d", err);
		return -EINVAL;
	}

	return 0;
}

int err_pcm_hw_param_check(snd_pcm_t *handle, struct hwparams *hw_params)
{
	snd_pcm_uframes_t start_threshold, stop_threshold;
	snd_pcm_sw_params_t *swparams;
	snd_pcm_hw_params_t *params;
	snd_pcm_uframes_t buffer_size;
	unsigned int rate;
	size_t n;
	int err;

	snd_pcm_hw_params_alloca(&params);
	snd_pcm_sw_params_alloca(&swparams);
	err = snd_pcm_hw_params_any(handle, params);
	if (err < 0) {
		error("Broken configuration for this PCM: no configurations available");
		return -EINVAL;
	}

#ifdef ERR_CHECK
	err = err_pcm_hw_params_set_access(handle, params);
	if (err)
		return err;
#endif

	err = snd_pcm_hw_params_set_access(handle, params,
				   SND_PCM_ACCESS_RW_INTERLEAVED);
	if (err < 0) {
		error("Access type not available %d", err);
		return -EINVAL;
	}

#ifdef ERR_CHECK
	err = err_pcm_hw_params_set_format(handle, params);
	if (err)
		return err;
#endif

	err = snd_pcm_hw_params_set_format (handle, params, hw_params->format);
	if (err)
	{
		error("cannot set sample format (%s)\n", snd_strerror (err));
		return -EINVAL;
	}

#ifdef ERR_CHECK
	err = err_pcm_hw_params_set_channels(handle, params);
	if (err)
		return err;
#endif

	err = snd_pcm_hw_params_set_channels(handle, params, hw_params->channels);
	if (err < 0) {
		error("Channels count non available %d", err);
		return -EINVAL;
	}

#ifdef ERR_CHECK
	err = err_pcm_hw_params_set_rate_near(handle, params);
	if (err)
		return err;
#endif

	err = snd_pcm_hw_params_set_rate_near(handle, params, &hw_params->rate, 0);
	if (err < 0) {
		error("failed to init rate %d", hw_params->rate);
		return -EINVAL;
	}

#ifdef ERR_CHECK
	err = err_pcm_hw_params(handle, params);
	if (err)
		return err;
#endif

	err = snd_pcm_hw_params (handle, params);
	if (err) {
		error("failled to init hw params %d", err);
		return -EINVAL;
	}
}

