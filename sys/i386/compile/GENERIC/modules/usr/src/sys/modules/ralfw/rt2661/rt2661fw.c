#include <sys/param.h>
#include <sys/errno.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/linker.h>
#include <sys/firmware.h>
#include <sys/systm.h>

extern char _binary_rt2661_fw_start[], _binary_rt2661_fw_end[];

static int
rt2661fw_fw_modevent(module_t mod, int type, void *unused)
{
	const struct firmware *fp, *parent;
	int error;
	switch (type) {
	case MOD_LOAD:

		fp = firmware_register("rt2661fw", _binary_rt2661_fw_start , (size_t)(_binary_rt2661_fw_end - _binary_rt2661_fw_start), 0, NULL);
		if (fp == NULL)
			goto fail_0;
		parent = fp;
		return (0);
	fail_0:
		return (ENXIO);
	case MOD_UNLOAD:
		error = firmware_unregister("rt2661fw");
		return (error);
	}
	return (EINVAL);
}

static moduledata_t rt2661fw_fw_mod = {
        "rt2661fw_fw",
        rt2661fw_fw_modevent,
        0
};
DECLARE_MODULE(rt2661fw_fw, rt2661fw_fw_mod, SI_SUB_DRIVERS, SI_ORDER_FIRST);
MODULE_VERSION(rt2661fw_fw, 1);
MODULE_DEPEND(rt2661fw_fw, firmware, 1, 1, 1);

