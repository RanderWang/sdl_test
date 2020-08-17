// SPDX-License-Identifier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may do so under either license.
//
// Copyright(c) 2020 Intel Corporation. All rights reserved.
//
// Author: Rander wang <Rander.wang@linux.intel.com>
//

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

const char *snd_sof =  "/sys/module/snd_sof";
const char *soundwire_intel = "/sys/module/soundwire_intel";
const char *snd_soc_sof_sdw = "/sys/module/snd_soc_sof_sdw";
const char *sof_pci_module_info = "/sys/module/snd_sof_pci";
const char *snd_sof_intel_hda_common = "/sys/module/snd_sof_intel_hda_common";
const char *audio_pci_dev = "/sys/bus/pci/devices/0000:00:1f.3";

int main(int argc, char * argv [ ])
{
	int filemode;
	int fd;

	filemode = O_RDWR;
	fd = open(snd_sof, filemode);
	if (fd < 0) {
		printf("confirm that unprivileged user cant access %s\n", snd_sof);
	} else {
		printf("error, unprivileged user can access %s\n", snd_sof);
		return -1;
	}

	fd = open(soundwire_intel, filemode);
	if (fd < 0) {
		printf("confirm that unprivileged user cant access %s\n", soundwire_intel);
	} else {
		printf("error, unprivileged user can access %s\n", soundwire_intel);
		return -1;
	}

	fd = open(snd_soc_sof_sdw, filemode);
	if (fd < 0) {
		printf("confirm that unprivileged user cant access %s\n", snd_soc_sof_sdw);
	} else {
		printf("error, unprivileged user can access %s\n", snd_soc_sof_sdw);
		return -1;
	}

	fd = open(sof_pci_module_info, filemode);
	if (fd < 0) {
		printf("confirm that unprivileged user cant access %s\n", sof_pci_module_info);
	} else {
		printf("error, unprivileged user can access %s\n", sof_pci_module_info);
		return -1;
	}

	fd = open(snd_sof_intel_hda_common, filemode);
	if (fd < 0) {
		printf("confirm that unprivileged user cant access %s\n", snd_sof_intel_hda_common);
	} else {
		printf("error, unprivileged user can access %s\n", snd_sof_intel_hda_common);
		return -1;
	}

	fd = open(audio_pci_dev, filemode);
	if (fd < 0) {
		printf("confirm that unprivileged user cant access %s\n", audio_pci_dev);
	} else {
		printf("error, unprivileged user can access %s\n", audio_pci_dev);
		return -1;
	}

	printf("validation successfully!\n");
	return 0;
}

