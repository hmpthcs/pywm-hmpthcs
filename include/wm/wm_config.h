#ifndef WM_CONFIG_H
#define WM_CONFIG_H

struct wm_config {
    double output_scale;
    int enable_output_manager;

    int callback_frequency;

    const char *xkb_model;
    const char *xkb_layout;
    const char *xkb_options;

    const char* xcursor_theme;
    int xcursor_size;

    int focus_follows_mouse;
    int constrain_popups_to_toplevel;

    int encourage_csd;

    int debug_f1;
};

void wm_config_init_default(struct wm_config* config);

#endif
