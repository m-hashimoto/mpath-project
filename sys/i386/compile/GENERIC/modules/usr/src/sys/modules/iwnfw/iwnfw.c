#include <sys/param.h>
#include <sys/errno.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/linker.h>
#include <sys/firmware.h>
#include <sys/systm.h>

extern char _binary_iwlwifi_4965_4_44_17_fw_start[], _binary_iwlwifi_4965_4_44_17_fw_end[];

static int
iwnfw_fw_modevent(module_t mod, int type, void *unused)
{
	const struct firmware *fp, *parent;
	int error;
	switch (type) {
	case MOD_LOAD:

		fp = firmware_register("iwnfw", _binary_iwlwifi_4965_4_44_17_fw_start , (size_t)(_binary_iwlwifi_4965_4_44_17_fw_end - _binary_iwlwifi_4965_4_44_17_fw_start), 44417, NULL);
		if (fp == NULL)
			goto fail_0;
		parent = fp;
		return (0);
	fail_0:
		return (ENXIO);
	case MOD_UNLOAD:
		error = firmware_unregister("iwnfw");
		return (error);
	}
	return (EINVAL);
}

static moduledata_t iwnfw_fw_mod = {
        "iwnfw_fw",
        iwnfw_fw_modevent,
        0
};
DECLARE_MODULE(iwnfw_fw, iwnfw_fw_mod, SI_SUB_DRIVERS, SI_ORDER_FIRST);
MODULE_VERSION(iwnfw_fw, 1);
MODULE_DEPEND(iwnfw_fw, firmware, 1, 1, 1);

