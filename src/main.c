
#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "contacts.h"

#define MY_UUID { 0x36, 0x17, 0x74, 0x7C, 0x43, 0x5D, 0x48, 0xE5, 0xBA, 0x16, 0xE8, 0x3C, 0x11, 0x38, 0x86, 0xF6 }
PBL_APP_INFO(MY_UUID, "Phone Link", "Daniel Miyamoto",
			 1, 0, /* App version */
			 RESOURCE_ID_IMAGE_MENU_ICON, APP_INFO_STANDARD_APP);

static Window main_window;

static SimpleMenuLayer main_menu_layer;
static SimpleMenuSection main_menu_section[1];
static SimpleMenuItem main_menu_items[2];

void main_menu_layer_select_callback(int index, void *context)
{
    switch (index) {
        case 0:
            display_contacts();
            break;
        default:
            break;
    }
}

// Standard app initialisation
void handle_init(AppContextRef ctx) {
  (void)ctx;
  
  window_init(&main_window, "Phone Link");
  window_stack_push(&main_window, true /* Animated */);

  // Loads all resources
  resource_init_current_app(&APP_RESOURCES);
  
  main_menu_items[0] = (SimpleMenuItem) {
      .title = "Contacts",
      .icon = NULL,
      .callback = &main_menu_layer_select_callback
  };
	
  main_menu_items[1] = (SimpleMenuItem) {
      .title = "Call Logs",
      .icon = NULL,
      .callback = &main_menu_layer_select_callback
  };
  
  main_menu_section[0] = (SimpleMenuSection) {
    .title = "Phone Link",
    .items = main_menu_items,
    .num_items = ARRAY_LENGTH(main_menu_items)
  };
  
  simple_menu_layer_init(&main_menu_layer, main_window.layer.frame, &main_window, main_menu_section, 1, NULL);
  layer_add_child(&main_window.layer, &main_menu_layer.menu.scroll_layer.layer);
  
}

void handle_deinit(AppContextRef ctx) {
  (void)ctx;
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
  .init_handler = &handle_init,
  .deinit_handler = &handle_deinit
  };
  app_event_loop(params, &handlers);
}
