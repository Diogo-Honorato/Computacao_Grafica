#pragma once


#define DEFAULT_UBER_VERTEX             "../shader/basic_shaders/uber.vs"
#define DEFAULT_UBER_FRAGMENT           "../shader/basic_shaders/uber.fs"
#define DEFAULT_DIFFUSE_TEXTURE         "default_diffuse.def"
#define DEFAULT_SPECULAR_TEXTURE        "default_specular.def"
#define DEFAULT_MOUSE_PICKING_FRAGMENT  "../shader/basic_shaders/mouse_picking.fs"
#define DEFAULT_MOUSE_PICKING_VERTEX    "../shader/basic_shaders/mouse_picking.vs"
#define INIT_FILE_PATH                  "../config/project.init"
#define INIT_FILE_MENU                  "../config/GUI/menu_button.json"

#ifdef _WIN32
    #define HOME_VAR "USERPROFILE"
#else
    #define HOME_VAR "HOME"
#endif
