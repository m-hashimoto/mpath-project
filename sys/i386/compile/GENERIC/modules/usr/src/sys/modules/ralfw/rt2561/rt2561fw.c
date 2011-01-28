#include <sys/param.h>
#include <sys/errno.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/linker.h>
#include <sys/firmware.h>
#include <sys/systm.h>

extern char _binary_rt2561_fw_start[], _binary_rt2561_fw_end[];

static int
rt2561fw_fw_modevent(module_t mod, int type, void *unused)
{
	const struct firmware *fp, *parent;
	int error;
	switch (type) {
	case MOD_LOAD:

		fp = firmware_register("rt2561fw", _binary_rt2561_fw_start , (size_t)(_binary_rt2561_fw_end - _binary_rt2561_fw_start), 0, NULL);
		if (fp == NULL)
			goto fail_0;
		parent = fp;
		return (0);
	fail_0:
		return (ENXIO);
	case MOD_UNLOAD:
		error = firmware_unregister("rt2561fw");
		return (error);
	}
	return (EINVAL);
}

static moduledata_t rt2561fw_fw_mod = {
        "rt2561fw_fw",
        rt2561fw_fw_modevent,
        0
};
DECLARE_MODULE(rt2561fw_fw, rt2561fw_fw_mod, SI_SUB_DRIVERS, SI_ORDER_FIRST);
MODULE_VERSION(rt2561fw_fw, 1);
MODULE_DEPEND(rt2561fw_fw, firmware, 1, 1, 1);

