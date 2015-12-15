/*
* Plugin Pidgin 2.6.2
* Andrei Coman
* UPT CTI anul I grupa 2.1
*
* Plugin that autorespondes when you are IDLE
*
*/
#define PURPLE_PLUGINS

#include <glib.h>

#include <notify.h>
#include <plugin.h>
#include <pluginpref.h>
#include <version.h>
#include <unistd.h>

#include <debug.h>

#define P_BASE "/plugins/core/ar"
#define P_TEXT P_BASE "/text"
#define P_IDLE P_BASE "/idle"

void *ar;
const char * 
get_msg(const char *m){
 const char *rep;
 rep=purple_prefs_get_string(P_TEXT);
 return rep;
}
static void
write_back(PurpleAccount *account, const char *who, const char *message,
				PurpleConversation *conv, PurpleMessageFlags flags, gpointer null){
  const char *mesaj;
  PurplePresence *presence;
  
  if (!(flags & PURPLE_MESSAGE_RECV))
		return;
  if (!message || !*message)
		return;
  if (flags & (PURPLE_MESSAGE_AUTO_RESP | PURPLE_MESSAGE_DELAYED))
		return;
  presence = purple_account_get_presence(account);
  if( purple_presence_is_status_primitive_active(presence, PURPLE_STATUS_INVISIBLE) )
    return; // Don't out us if we are invisible
  if( purple_prefs_get_bool(P_IDLE) && !purple_presence_is_idle(presence)){
	 return;
   } 
  {
	PurpleMessageFlags flag = PURPLE_MESSAGE_SEND;
	flag |= PURPLE_MESSAGE_AUTO_RESP;        
        mesaj=get_msg(message);
	purple_conv_im_send_with_flags(PURPLE_CONV_IM(conv), mesaj, flag); 
  }

}
static gboolean
plugin_load(PurplePlugin *plugin) {
       
	purple_signal_connect(purple_conversations_get_handle(), "wrote-im-msg", plugin,
						PURPLE_CALLBACK(write_back), NULL);
	ar=plugin; 

	return TRUE;
}
static gboolean
plugin_unload (PurplePlugin *plugin)
{
	purple_signal_disconnect(purple_conversations_get_handle(), "wrote-im-msg", plugin,
						PURPLE_CALLBACK(write_back));
	return TRUE;
}
static PurplePluginPrefFrame *
get_plugin_pref_frame(PurplePlugin *plugin) {

  PurplePluginPrefFrame *frame;
  PurplePluginPref *pref;
  
  frame = purple_plugin_pref_frame_new();
  
  pref = purple_plugin_pref_new_with_name_and_label(P_TEXT,"Text for autoresponse:");

  purple_plugin_pref_frame_add(frame, pref);
 
  pref = purple_plugin_pref_new_with_name_and_label(P_IDLE,"Only if I'm idle");
  
  purple_plugin_pref_frame_add(frame, pref);

  return frame;
}
static PurplePluginUiInfo prefs_info = {
	get_plugin_pref_frame,
	0,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};
static PurplePluginInfo info = {
    PURPLE_PLUGIN_MAGIC,
    PURPLE_MAJOR_VERSION,
    PURPLE_MINOR_VERSION,
    PURPLE_PLUGIN_STANDARD,
    NULL,
    0,
    NULL,
    PURPLE_PRIORITY_DEFAULT,

    "core-ar",
    "Autoresponder",
    "0.0.1",

    "Autoresponder",
    "Raspunde automat cu un text in caz ca nu sunteti la birou.",          
    "Andrei Coman <comandrei@gmail.com>",                          
    "http://github.com/comandrei/pidgin-autoresponder",     
    
    plugin_load,                   
    plugin_unload,                          
    NULL,                          
                                   
    NULL,                          
    NULL,                          
    &prefs_info,                        
    NULL,                   
    NULL,                          
    NULL,                          
    NULL,                          
    NULL                           
};                               
    
static void
init_plugin(PurplePlugin *plugin)
{
	purple_prefs_add_none(P_BASE);
	purple_prefs_add_string(P_TEXT, "I'm not available");
	purple_prefs_add_bool(P_IDLE,TRUE);
}

PURPLE_INIT_PLUGIN(ar, init_plugin, info)
