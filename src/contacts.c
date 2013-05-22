//
//  contacts.c
//
//
//  Created by Daniel Miyamoto
//
//

#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "contacts.h"
#include "contact.h"

static Window contacts_window;

static SimpleMenuLayer contacts_menu_layer;
static SimpleMenuSection contacts_menu_sections[2]; //Two sections (Favorites,Others)

static SimpleMenuItem contacts_menu_fav_items[2];
static SimpleMenuItem contacts_menu_others_items[2];

void handle_contacts_appear(Window *window)
{
  scroll_layer_set_frame(&contacts_menu_layer.menu.scroll_layer, window->layer.bounds);
}

void handle_contacts_unload(Window *window)
{
}

void contacts_select_callback(int index, void *context)
{
    display_contact();
}

void init_contacts_window()
{
    window_init(&contacts_window, "Contacts");
    window_set_background_color(&contacts_window, GColorWhite);
    window_set_window_handlers(&contacts_window, (WindowHandlers) {
        .appear = (WindowHandler)handle_contacts_appear,
        .unload = (WindowHandler)handle_contacts_unload
    });
	
  contacts_menu_fav_items[0] = (SimpleMenuItem) {
      .title = "Veronica",
      .icon = NULL,
      .callback = &contacts_select_callback
  };
  
  contacts_menu_fav_items[1] = (SimpleMenuItem) {
      .title = "Rafael",
      .icon = NULL,
      .callback = &contacts_select_callback
  };
  
  contacts_menu_sections[0] = (SimpleMenuSection) {
    .title = "Favorites",
    .items = contacts_menu_fav_items,
    .num_items = ARRAY_LENGTH(contacts_menu_fav_items)
  };
  
  contacts_menu_others_items[0] = (SimpleMenuItem) {
      .title = "Helena",
      .icon = NULL,
      .callback = &contacts_select_callback
  };
  
  contacts_menu_others_items[1] = (SimpleMenuItem) {
      .title = "Daniel",
      .icon = NULL,
      .callback = &contacts_select_callback
  };
  
  contacts_menu_sections[1] = (SimpleMenuSection) {
    .title = "Others",
    .items = contacts_menu_others_items,
    .num_items = ARRAY_LENGTH(contacts_menu_others_items)
  };
    
  simple_menu_layer_init(&contacts_menu_layer, contacts_window.layer.frame, &contacts_window, contacts_menu_sections, ARRAY_LENGTH(contacts_menu_sections), NULL);
  layer_add_child(&contacts_window.layer, &contacts_menu_layer.menu.scroll_layer.layer);
    
}

void display_contacts()
{   
    init_contacts_window();
    
    window_stack_push(&contacts_window, true);
}