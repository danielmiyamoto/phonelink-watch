//
//  contact.c
//
//
//  Created by Daniel Miyamoto
//
//

#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "contact.h"
#include "sms.h"


static Window contact_window;
static ActionBarLayer contact_action_bar_layer;

static HeapBitmap contact_phone;
static HeapBitmap contact_cancel;
static HeapBitmap contact_sms;

static SimpleMenuLayer contact_menu_layer;
static SimpleMenuSection contact_menu_section[1];
static SimpleMenuItem contact_menu_items[3];

void handle_contact_appear(Window *window)
{
  scroll_layer_set_frame(&contact_menu_layer.menu.scroll_layer, window->layer.bounds);
}

void contact_select_callback(int index, void *context)
{
  action_bar_layer_add_to_window(&contact_action_bar_layer, &contact_window);
}

void handle_contact_unload(Window *window)
{
    heap_bitmap_deinit(&contact_phone);
	heap_bitmap_deinit(&contact_cancel);
    heap_bitmap_deinit(&contact_sms);
}

void contact_call_handler(ClickRecognizerRef recognizer, Window *window) {
    (void)recognizer;
    (void)window;
	
	//Executes the call action
}

void contact_cancel_handler(ClickRecognizerRef recognizer, Window *window) {
    (void)recognizer;
    (void)window;
	
	//Executes the cancel action
	action_bar_layer_remove_from_window(&contact_action_bar_layer);
}

void contact_sms_handler(ClickRecognizerRef recognizer, Window *window) {
    (void)recognizer;
    (void)window;
	
	//Executes the SMS action
	display_sms();
    contact_action_bar_layer.is_highlighted = 0;
}

void contact_click_config_provider(ClickConfig **config, Window *window) {
    (void)window;
    
    config[BUTTON_ID_UP]->long_click.handler = (ClickHandler) contact_call_handler;
	
	config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) contact_cancel_handler;
    config[BUTTON_ID_SELECT]->click.repeat_interval_ms = 1000;
    
    config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) contact_sms_handler;
    config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 1000;
    
}

void init_contact_action_bar(){

  // Load some bitmaps 
  heap_bitmap_init(&contact_phone, RESOURCE_ID_PHONE);
  heap_bitmap_init(&contact_cancel, RESOURCE_ID_CANCEL);
  heap_bitmap_init(&contact_sms, RESOURCE_ID_SMS);
  
  //Initializes action bar/click config provider
  action_bar_layer_init(&contact_action_bar_layer);
  action_bar_layer_set_click_config_provider(&contact_action_bar_layer, (ClickConfigProvider) contact_click_config_provider);

  //Initializes the icons for action bar
  action_bar_layer_set_icon(&contact_action_bar_layer, BUTTON_ID_UP, &contact_phone.bmp);
  action_bar_layer_set_icon(&contact_action_bar_layer, BUTTON_ID_SELECT, &contact_cancel.bmp);
  action_bar_layer_set_icon(&contact_action_bar_layer, BUTTON_ID_DOWN, &contact_sms.bmp);
  
}

void init_contact_info(){
  contact_menu_items[0] = (SimpleMenuItem) {
      .title = "22018503",
      .icon = NULL,
      .callback = &contact_select_callback
  };
  
  contact_menu_items[1] = (SimpleMenuItem) {
      .title = "992092560",
      .icon = NULL,
      .callback = &contact_select_callback
  };
  
  contact_menu_items[2] = (SimpleMenuItem) {
      .title = "962787057",
      .icon = NULL,
      .callback = &contact_select_callback
  };
  
  contact_menu_section[0] = (SimpleMenuSection) {
    .items = contact_menu_items,
    .num_items = ARRAY_LENGTH(contact_menu_items)
  };
  
  simple_menu_layer_init(&contact_menu_layer, contact_window.layer.frame, &contact_window, contact_menu_section, ARRAY_LENGTH(contact_menu_section), NULL);
  layer_add_child(&contact_window.layer, &contact_menu_layer.menu.scroll_layer.layer);
}

void init_contact_window()
{
    window_init(&contact_window, "Contact");
    window_set_background_color(&contact_window, GColorWhite);
    window_set_window_handlers(&contact_window, (WindowHandlers) {
        .appear = (WindowHandler)handle_contact_appear,
        .unload = (WindowHandler)handle_contact_unload
    });
	
	
	init_contact_info();
	init_contact_action_bar();
}
	
void display_contact()
{   
    init_contact_window();
    
    window_stack_push(&contact_window, true);
}