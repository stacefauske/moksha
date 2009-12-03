/*
 * vim:ts=8:sw=3:sts=8:noexpandtab:cino=>5n-3f0^-2{2
 */
#include "e.h"
#include "e_mod_main.h"

/* actual module specifics */
static E_Module *conf_module = NULL;

/* module setup */
EAPI E_Module_Api e_modapi =
{
   E_MODULE_API_VERSION,
     "Settings - Run Command"
};

EAPI void *
e_modapi_init(E_Module *m)
{
   e_configure_registry_category_add("advanced", 80, _("Advanced"), NULL, "preferences-advanced");
   e_configure_registry_item_add("advanced/run_command", 40, _("Run Command"), NULL, "system-run", e_int_config_exebuf);
   conf_module = m;
   e_module_delayed_set(m, 1);
   return m;
}

EAPI int
e_modapi_shutdown(E_Module *m)
{
   E_Config_Dialog *cfd;
   while ((cfd = e_config_dialog_get("E", "_config_exebuf_dialog"))) e_object_del(E_OBJECT(cfd));
   e_configure_registry_item_del("advanced/run_command");
   e_configure_registry_category_del("advanced");
   conf_module = NULL;
   return 1;
}

EAPI int
e_modapi_save(E_Module *m)
{
   return 1;
}
