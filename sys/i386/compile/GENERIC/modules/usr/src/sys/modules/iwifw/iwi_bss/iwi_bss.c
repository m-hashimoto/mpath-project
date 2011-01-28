#include <sys/param.h>
#include <sys/errno.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/linker.h>
#include <sys/firmware.h>
#include <sys/systm.h>

static long intel_iwi_license_ack = 0;
extern char _binary_iwi_bss_start[], _binary_iwi_bss_end[];

static int
iwi_bss_fw_modevent(module_t mod, int type, void *unused)
{
	const struct firmware *fp, *parent;
	int error;
	switch (type) {
	case MOD_LOAD:


		TUNABLE_LONG_FETCH("legal.intel_iwi.license_ack", &intel_iwi_license_ack);
		if (!intel_iwi_license_ack) {
			printf("iwi_bss: You need to read the LICENSE file in /usr/share/doc/legal/intel_iwi/.\n");
			printf("iwi_bss: If you agree with the license, set legal.intel_iwi.license_ack=1 in /boot/loader.conf.\n");
			return(EPERM);
		}

		fp = firmware_register("iwi_bss", _binary_iwi_bss_start , (size_t)(_binary_iwi_bss_end - _binary_iwi_bss_start), 300, NULL);
		if (fp == NULL)
			goto fail_0;
		parent = fp;
		return (0);
	fail_0:
		return (ENXIO);
	case MOD_UNLOAD:
		error = firmware_unregister("iwi_bss");
		return (error);
	}
	return (EINVAL);
}

static moduledata_t iwi_bss_fw_mod = {
        "iwi_bss_fw",
        iwi_bss_fw_modevent,
        0
};
DECLARE_MODULE(iwi_bss_fw, iwi_bss_fw_mod, SI_SUB_DRIVERS, SI_ORDER_FIRST);
MODULE_VERSION(iwi_bss_fw, 1);
MODULE_DEPEND(iwi_bss_fw, firmware, 1, 1, 1);

