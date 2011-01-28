/*
 * This file is produced automatically.
 * Do not modify anything in here by hand.
 *
 * Created from source file
 *   @/dev/acpi_support/acpi_wmi_if.m
 * with
 *   makeobjops.awk
 *
 * See the source file for legal information
 */


#ifndef _acpi_wmi_if_h_
#define _acpi_wmi_if_h_

/** @brief Unique descriptor for the ACPI_WMI_PROVIDES_GUID_STRING() method */
extern struct kobjop_desc acpi_wmi_provides_guid_string_desc;
/** @brief A function implementing the ACPI_WMI_PROVIDES_GUID_STRING() method */
typedef int acpi_wmi_provides_guid_string_t(device_t dev,
                                            const char* guid_string);

static __inline int ACPI_WMI_PROVIDES_GUID_STRING(device_t dev,
                                                  const char* guid_string)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,acpi_wmi_provides_guid_string);
	return ((acpi_wmi_provides_guid_string_t *) _m)(dev, guid_string);
}

/** @brief Unique descriptor for the ACPI_WMI_EVALUATE_CALL() method */
extern struct kobjop_desc acpi_wmi_evaluate_call_desc;
/** @brief A function implementing the ACPI_WMI_EVALUATE_CALL() method */
typedef ACPI_STATUS acpi_wmi_evaluate_call_t(device_t dev,
                                             const char *guid_string,
                                             UINT8 instance, UINT32 method_id,
                                             const ACPI_BUFFER *in,
                                             ACPI_BUFFER *out);

static __inline ACPI_STATUS ACPI_WMI_EVALUATE_CALL(device_t dev,
                                                   const char *guid_string,
                                                   UINT8 instance,
                                                   UINT32 method_id,
                                                   const ACPI_BUFFER *in,
                                                   ACPI_BUFFER *out)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,acpi_wmi_evaluate_call);
	return ((acpi_wmi_evaluate_call_t *) _m)(dev, guid_string, instance, method_id, in, out);
}

/** @brief Unique descriptor for the ACPI_WMI_GET_BLOCK() method */
extern struct kobjop_desc acpi_wmi_get_block_desc;
/** @brief A function implementing the ACPI_WMI_GET_BLOCK() method */
typedef ACPI_STATUS acpi_wmi_get_block_t(device_t dev, const char *guid_string,
                                         UINT8 instance, ACPI_BUFFER *out);

static __inline ACPI_STATUS ACPI_WMI_GET_BLOCK(device_t dev,
                                               const char *guid_string,
                                               UINT8 instance, ACPI_BUFFER *out)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,acpi_wmi_get_block);
	return ((acpi_wmi_get_block_t *) _m)(dev, guid_string, instance, out);
}

/** @brief Unique descriptor for the ACPI_WMI_SET_BLOCK() method */
extern struct kobjop_desc acpi_wmi_set_block_desc;
/** @brief A function implementing the ACPI_WMI_SET_BLOCK() method */
typedef ACPI_STATUS acpi_wmi_set_block_t(device_t dev, const char *guid_string,
                                         UINT8 instance, const ACPI_BUFFER *in);

static __inline ACPI_STATUS ACPI_WMI_SET_BLOCK(device_t dev,
                                               const char *guid_string,
                                               UINT8 instance,
                                               const ACPI_BUFFER *in)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,acpi_wmi_set_block);
	return ((acpi_wmi_set_block_t *) _m)(dev, guid_string, instance, in);
}

/** @brief Unique descriptor for the ACPI_WMI_INSTALL_EVENT_HANDLER() method */
extern struct kobjop_desc acpi_wmi_install_event_handler_desc;
/** @brief A function implementing the ACPI_WMI_INSTALL_EVENT_HANDLER() method */
typedef ACPI_STATUS acpi_wmi_install_event_handler_t(device_t dev,
                                                     const char *guid_string,
                                                     ACPI_NOTIFY_HANDLER handler, void *data);

static __inline ACPI_STATUS ACPI_WMI_INSTALL_EVENT_HANDLER(device_t dev,
                                                           const char *guid_string, ACPI_NOTIFY_HANDLER handler, void *data)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,acpi_wmi_install_event_handler);
	return ((acpi_wmi_install_event_handler_t *) _m)(dev, guid_string, handler, data);
}

/** @brief Unique descriptor for the ACPI_WMI_REMOVE_EVENT_HANDLER() method */
extern struct kobjop_desc acpi_wmi_remove_event_handler_desc;
/** @brief A function implementing the ACPI_WMI_REMOVE_EVENT_HANDLER() method */
typedef ACPI_STATUS acpi_wmi_remove_event_handler_t(device_t dev,
                                                    const char *guid_string);

static __inline ACPI_STATUS ACPI_WMI_REMOVE_EVENT_HANDLER(device_t dev,
                                                          const char *guid_string)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,acpi_wmi_remove_event_handler);
	return ((acpi_wmi_remove_event_handler_t *) _m)(dev, guid_string);
}

/** @brief Unique descriptor for the ACPI_WMI_GET_EVENT_DATA() method */
extern struct kobjop_desc acpi_wmi_get_event_data_desc;
/** @brief A function implementing the ACPI_WMI_GET_EVENT_DATA() method */
typedef ACPI_STATUS acpi_wmi_get_event_data_t(device_t dev, UINT32 event_id,
                                              ACPI_BUFFER *out);

static __inline ACPI_STATUS ACPI_WMI_GET_EVENT_DATA(device_t dev,
                                                    UINT32 event_id,
                                                    ACPI_BUFFER *out)
{
	kobjop_t _m;
	KOBJOPLOOKUP(((kobj_t)dev)->ops,acpi_wmi_get_event_data);
	return ((acpi_wmi_get_event_data_t *) _m)(dev, event_id, out);
}

#endif /* _acpi_wmi_if_h_ */
