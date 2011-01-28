/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   ../../../dev/acpi_support/acpi_wmi_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */

#include <sys/param.h>
#include <sys/queue.h>
#include <sys/kernel.h>
#include <sys/kobj.h>
#include <sys/bus.h>
#include <sys/types.h>
#include <contrib/dev/acpica/include/acpi.h>
#include "acpi_wmi_if.h"


static int
acpi_wmi_generic_provides_guid_string(device_t dev, const char* guid_string)
{
	return 0;
}

struct kobj_method acpi_wmi_provides_guid_string_method_default = {
	&acpi_wmi_provides_guid_string_desc, (kobjop_t) acpi_wmi_generic_provides_guid_string
};

struct kobjop_desc acpi_wmi_provides_guid_string_desc = {
	0, &acpi_wmi_provides_guid_string_method_default
};

struct kobj_method acpi_wmi_evaluate_call_method_default = {
	&acpi_wmi_evaluate_call_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc acpi_wmi_evaluate_call_desc = {
	0, &acpi_wmi_evaluate_call_method_default
};

struct kobj_method acpi_wmi_get_block_method_default = {
	&acpi_wmi_get_block_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc acpi_wmi_get_block_desc = {
	0, &acpi_wmi_get_block_method_default
};

struct kobj_method acpi_wmi_set_block_method_default = {
	&acpi_wmi_set_block_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc acpi_wmi_set_block_desc = {
	0, &acpi_wmi_set_block_method_default
};

struct kobj_method acpi_wmi_install_event_handler_method_default = {
	&acpi_wmi_install_event_handler_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc acpi_wmi_install_event_handler_desc = {
	0, &acpi_wmi_install_event_handler_method_default
};

struct kobj_method acpi_wmi_remove_event_handler_method_default = {
	&acpi_wmi_remove_event_handler_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc acpi_wmi_remove_event_handler_desc = {
	0, &acpi_wmi_remove_event_handler_method_default
};

struct kobj_method acpi_wmi_get_event_data_method_default = {
	&acpi_wmi_get_event_data_desc, (kobjop_t) kobj_error_method
};

struct kobjop_desc acpi_wmi_get_event_data_desc = {
	0, &acpi_wmi_get_event_data_method_default
};

