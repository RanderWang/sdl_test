#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <locale.h>
#include <alsa/asoundlib.h>
#include <assert.h>
#include <termios.h>
#include <signal.h>
#include <poll.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <endian.h>
#include "formats.h"
#include "err_pcm.h"

static snd_pcm_t *handle;
static int open_mode = 0;

static snd_pcm_format_t format[] = {
	/** Signed 16 bit Little Endian */
	SND_PCM_FORMAT_S16_LE,
	/** Signed 32 bit Little Endian */
	SND_PCM_FORMAT_S32_LE,
};

static int rate[] = {44100, 48000, 96000, 192000};
static int channels[] = { 1, 2, 4, 6, 8};

int main(int argc, char *argv[])
{
	char *pcm_name = "default";
	snd_pcm_info_t *info;
	snd_pcm_info_alloca(&info);
	struct hwparams hw_params;
	
	int stream = 0;
	int err;
	int i, j, k;

	printf("======== start to check playback ========\n");

	err = err_pcm_open_check(handle, stream);
	if (err < 0) {
		printf("audio open error check failed: %s\n", snd_strerror(err));
		return -1;
	}

	err = snd_pcm_open(&handle, pcm_name, stream, open_mode);
	if (err < 0) {
		printf("audio open error: %s\n", snd_strerror(err));
		return -1;
	}

	err = snd_pcm_info(handle, info);
	if (err < 0) {
		printf("info error: %s\n", snd_strerror(err));
		return -1;
	}

	for (i = 0; i < ARRAY_SIZE(format); i++) {
		for (j = 0; j < ARRAY_SIZE(rate); j++) {
			for (k = 0; k < ARRAY_SIZE(channels); k++) {
				hw_params.format = format[i];
				hw_params.rate = rate[j];
				hw_params.channels = channels[k];

				err = err_pcm_hw_param_check(handle, &hw_params);
				if (err < 0) {
					printf("hw param error: %s\n", snd_strerror(err));
					return -1;
				}
			}
		}
	}

	err = err_pcm_prepare_check(handle);
	if (err < 0) {
		printf("pcm prepare error %s\n", snd_strerror(err));
		return -1;
	}

	err = err_pcm_writei_check(handle);
	if (err < 0) {
		printf("pcm prepare error %s\n", snd_strerror(err));
		return -1;
	}

	err_pcm_close_check(handle);

capture:
	stream = 1;
	printf("======== start to check capture ========\n");

	err = err_pcm_open_check(handle, stream);
	if (err < 0) {
		printf("audio open error check failed: %s", snd_strerror(err));
		return -1;
	}

	err = snd_pcm_open(&handle, pcm_name, stream, open_mode);
	if (err < 0) {
		printf("audio open error: %s", snd_strerror(err));
		return -1;
	}

	err = snd_pcm_info(handle, info);
	if (err < 0) {
		printf("info error: %s", snd_strerror(err));
		return -1;
	}

	for (i = 0; i < ARRAY_SIZE(format); i++) {
		for (j = 0; j < ARRAY_SIZE(rate); j++) {
			for (k = 0; k < ARRAY_SIZE(channels); k++) {
				hw_params.format = format[i];
				hw_params.rate = rate[j];
				hw_params.channels = channels[k];

				err = err_pcm_hw_param_check(handle, &hw_params);
				if (err < 0) {
					printf("hw param error: %s", snd_strerror(err));
					//return -1;
				}
			}
		}
	}

	err = err_pcm_prepare_check(handle);
	if (err < 0) {
		printf("pcm prepare error %s", snd_strerror(err));
		return -1;
	}

	err = err_pcm_readi_check(handle);
	if (err < 0) {
		printf("pcm prepare error %s", snd_strerror(err));
		return -1;
	}

	err_pcm_close_check(handle);

	return 0;
}

