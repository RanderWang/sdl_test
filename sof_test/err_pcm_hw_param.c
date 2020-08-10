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
		printf("failed to detect error for access mode -1\n");
		return -EINVAL;
	}

	err = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_LAST + 1);
	if (!err) {
		printf("failed to detect error for access mode -1\n");
		return -EINVAL;
	}
	
	return 0;
}

static snd_pcm_format_t unsupported_format[] = {
	SND_PCM_FORMAT_S8 ,
	/** Unsigned 8 bit */
	SND_PCM_FORMAT_U8,
	/** Signed 16 bit Big Endian */
	SND_PCM_FORMAT_S16_BE,
	/** Unsigned 16 bit Little Endian */
	SND_PCM_FORMAT_U16_LE,
	/** Unsigned 16 bit Big Endian */
	SND_PCM_FORMAT_U16_BE,
	/** Signed 24 bit Little Endian using low three bytes in 32-bit word */
	SND_PCM_FORMAT_S24_LE,
	/** Signed 24 bit Big Endian using low three bytes in 32-bit word */
	SND_PCM_FORMAT_S24_BE,
	/** Unsigned 24 bit Little Endian using low three bytes in 32-bit word */
	SND_PCM_FORMAT_U24_LE,
	/** Unsigned 24 bit Big Endian using low three bytes in 32-bit word */
	SND_PCM_FORMAT_U24_BE,
	/** Signed 32 bit Big Endian */
	SND_PCM_FORMAT_S32_BE,
	/** Unsigned 32 bit Little Endian */
	SND_PCM_FORMAT_U32_LE,
	/** Unsigned 32 bit Big Endian */
	SND_PCM_FORMAT_U32_BE,
	/** Float 32 bit Little Endian, Range -1.0 to 1.0 */
	SND_PCM_FORMAT_FLOAT_LE,
	/** Float 32 bit Big Endian, Range -1.0 to 1.0 */
	SND_PCM_FORMAT_FLOAT_BE
};

int err_pcm_hw_params_set_format(snd_pcm_t *handle, snd_pcm_hw_params_t *params)
{
	int err;
	int i;

	err = snd_pcm_hw_params_set_format(handle, params, -1);
	if (!err) {
		printf("failed to detect incorrect format -1\n");
		return -EINVAL;
	}
	
	err = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_LAST + 1);
	if (!err) {
		printf("failed to detect incorrect format %d\n", SND_PCM_FORMAT_LAST + 1);
		return -EINVAL;
	}

	for (i = 0; i < ARRAY_SIZE(unsupported_format); i++) {
		err = snd_pcm_hw_params_set_format(handle, params, unsupported_format[i]);
		if (!err) {
			printf("failed to detect incorrect format %d\n", i);
			return -EINVAL;
		}
	}

	return 0;
}

int err_pcm_hw_params_set_channels(snd_pcm_t *handle, snd_pcm_hw_params_t *params)
{
	int err;

	err = snd_pcm_hw_params_set_channels(handle, params, -1);
	if (!err ) {
		printf("failed to detect incorrect Channels count  -1%d\n", err);
		return -EINVAL;
	}

	err = snd_pcm_hw_params_set_channels(handle, params, 16);
	if (!err ) {
		printf("failed to detect incorrect Channels count 16 %d\n", err);
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
		printf("failed to detect incorrect rate dir  2 %d\n", err);
		return -EINVAL;
	}

	rate = -1;
	dir = 1;
	err = snd_pcm_hw_params_set_rate_near(handle, params, &rate, &dir);
	if (!err ) {
		printf("failed to detect incorrect rate dir 1 for -1 %d\n", err);
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
		printf("failed to detect incorrect params %d\n", err);
		return -EINVAL;
	}

	err = snd_pcm_hw_params(handle, blank_params);
	if (!err ) {
		printf("failed to detect blank params %d\n", err);
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
		printf("Broken configuration for this PCM: no configurations available\n");
		return -EINVAL;
	}

#if ERR_HW_PARAM_CHECK
	err = err_pcm_hw_params_set_access(handle, params);
	if (err)
		return err;

	err = snd_pcm_hw_params_set_access(NULL, params,
				SND_PCM_ACCESS_RW_INTERLEAVED);
	if (!err) {
		printf("failed to detect null handle\n");
		return -EINVAL;
	}

        err = snd_pcm_hw_params_set_access((snd_pcm_t *)(0xdeadbeef),
			           params,SND_PCM_ACCESS_RW_INTERLEAVED);
	if (!err) {
	       printf("failed to detect invalid handle\n");
	       return -EINVAL;
	}
#endif

	err = snd_pcm_hw_params_set_access(handle, params,
				   SND_PCM_ACCESS_RW_INTERLEAVED);
	if (err < 0) {
		printf("Access type not available %d\n", err);
		return -EINVAL;
	}

#if ERR_HW_PARAM_CHECK
	err = err_pcm_hw_params_set_format(handle, params);
	if (err)
		return err;
#endif

	err = snd_pcm_hw_params_set_format(handle, params, hw_params->format);
	if (err)
	{
		printf("cannot set sample format %x (%s)\n\n", hw_params->format, snd_strerror (err));
		return -EINVAL;
	}

#if ERR_HW_PARAM_CHECK
	err = err_pcm_hw_params_set_channels(handle, params);
	if (err)
		return err;
#endif

	err = snd_pcm_hw_params_set_channels(handle, params, hw_params->channels);
	if (err < 0) {
		printf("Channels count non available %d\n", err);
		return -EINVAL;
	}

#if ERR_HW_PARAM_CHECK
	err = err_pcm_hw_params_set_rate_near(handle, params);
	if (err)
		return err;
#endif

	err = snd_pcm_hw_params_set_rate_near(handle, params, &hw_params->rate, 0);
	if (err < 0) {
		printf("failed to init rate %d\n", hw_params->rate);
		return -EINVAL;
	}

#if ERR_HW_PARAM_CHECK
	err = err_pcm_hw_params(handle, params);
	if (err)
		return err;
#endif

	err = snd_pcm_hw_params (handle, params);
	if (err) {
		printf("failled to init hw params %d\n", err);
		return -EINVAL;
	}
}

