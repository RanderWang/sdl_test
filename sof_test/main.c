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

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static snd_pcm_t *handle;
static int open_mode = 0;

static snd_pcm_format_t format[] = {
	SND_PCM_FORMAT_S8 ,
	/** Unsigned 8 bit */
	SND_PCM_FORMAT_U8,
	/** Signed 16 bit Little Endian */
	SND_PCM_FORMAT_S16_LE,
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
	/** Signed 32 bit Little Endian */
	SND_PCM_FORMAT_S32_LE,
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

static int rate[] = {44100, 48000 };
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

	err = err_pcm_open_check(handle);
	if (err < 0) {
		error("audio open error check failed: %s", snd_strerror(err));
		return -1;
	}

	err = snd_pcm_open(&handle, pcm_name, stream, open_mode);
	if (err < 0) {
		error("audio open error: %s", snd_strerror(err));
		return -1;
	}

	err = snd_pcm_info(handle, info);
	if (err < 0) {
		error("info error: %s", snd_strerror(err));
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
					error("hw param error: %s", snd_strerror(err));
					return -1;
				}
			}
		}
	}

	err = err_pcm_prepare_check(handle);
	if (err < 0) {
		error("pcm prepare error %s", snd_strerror(err));
		return -1;
	}

	err = err_pcm_writei_check(handle);
	if (err < 0) {
		error("pcm prepare error %s", snd_strerror(err));
		return -1;
	}

	err_pcm_close_check(handle);

	return 0;
}

