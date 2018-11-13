#ifndef WM_VIEW_H
#define WM_VIEW_H

#include <stdbool.h>
#include <wayland-server.h>
#include <wlr/types/wlr_xdg_shell.h>
#include <wlr/types/wlr_xdg_decoration_v1.h>
#include <wlr/types/wlr_box.h>

struct wm_seat;

struct wm_view_decoration {
    struct wl_list link; // wm_server::wm_view_decorations

    struct wlr_xdg_toplevel_decoration_v1* wlr_xdg_toplevel_decoration;

    struct wl_listener request_mode;
    struct wl_listener destroy;
};

void wm_view_decoration_init(struct wm_view_decoration* deco, struct wlr_xdg_toplevel_decoration_v1* wlr_deco);
void wm_view_decoration_destroy(struct wm_view_decoration* deco);

struct wm_view {
    struct wl_list link;  // wm_server::wm_views
    struct wm_server* wm_server;

    enum {
        WM_VIEW_XDG,
        WM_VIEW_XWAYLAND
    } kind;

    const char* title;
    const char* app_id;

    bool mapped;

    double display_x;
    double display_y;
    double display_width;
    double display_height;

    struct wlr_xdg_surface* wlr_xdg_surface;
    struct wlr_xwayland_surface* wlr_xwayland_surface;

    struct wl_listener map;
    struct wl_listener unmap;
    struct wl_listener destroy;
};

void wm_view_init_xdg(struct wm_view* view, struct wm_server* server, struct wlr_xdg_surface* surface);
void wm_view_init_xwayland(struct wm_view* view, struct wm_server* server, struct wlr_xwayland_surface* surface);
void wm_view_destroy(struct wm_view* view);
void wm_view_set_box(struct wm_view* view, double x, double y, double width, double height);

void wm_view_request_size(struct wm_view* view, int width, int height);
void wm_view_get_size(struct wm_view* view, int* width, int* height);
void wm_view_focus(struct wm_view* view, struct wm_seat* seat);
struct wlr_surface* wm_view_surface_at(struct wm_view* view, double at_x, double at_y, double* sx, double* sy);
void wm_view_for_each_surface(struct wm_view* view, wlr_surface_iterator_func_t iterator, void* user_data);

#endif