/****************************************************************************

 KHotKeys
 
 Copyright (C) 1999-2001 Lubos Lunak <l.lunak@kde.org>

 Distributed under the terms of the GNU General Public License version 2.
 
****************************************************************************/

#ifndef _KCMKHOTKEYS_H_
#define _KCMKHOTKEYS_H_

#define KDE3_SUPPORT
#include <kcmodule.h>
#undef KDE3_SUPPORT
#include <kshortcut.h>

#include <actions.h>
#include <settings.h>


namespace KHotKeys
{

class Actions_listview_widget;
class Tab_widget;
class Action_data_base;
class Main_buttons_widget;

class Module
    : public KCModule
    {
    Q_OBJECT
    public:
        Module( QWidget *parent_P, const QVariantList &args );
        virtual ~Module();
        virtual void load();
        virtual void save();
//        virtual void defaults(); not used
        QString quickHelp() const;
        int buttons();
        void set_current_action_data( Action_data_base* data_P );
        Action_data_base* current_action_data();
        void action_name_changed( const QString& name_P );
        Action_data_group* actions_root() const;
        void set_gestures_disabled( bool set );
        bool gestures_disabled() const;
        void set_gesture_button( int button );
        int gesture_button() const;
        void set_gesture_timeout( int time );
        int gesture_timeout() const;
        void set_gestures_exclude( Windowdef_list* windows );
        const Windowdef_list* gestures_exclude() const;
        void set_daemon_disabled( bool disable );
        bool daemon_disabled() const;
        void import();

    public Q_SLOTS:
		KShortcut voice_shortcut() const;
		void set_voice_shortcut( const KShortcut&) ;
        void changed();
    protected:
        void set_new_current_action( bool save_old_P );
        void init_arts();
        Actions_listview_widget* actions_listview_widget;
        Tab_widget* tab_widget;
        Main_buttons_widget* buttons_widget;
        Action_data_group* _actions_root; // vlastni vsechny Action_data
        Action_data_base* _current_action_data;
        bool listview_is_changed;
        bool deleting_action;
        Settings settings;
    protected Q_SLOTS:
        void listview_current_action_changed();
        void new_action();
        void new_action_group();
        void delete_action();
        void global_settings();
    };
    
extern Module* module;

//***************************************************************************
// Inline
//***************************************************************************

// Module

inline
Action_data_group* Module::actions_root() const
    {
    return _actions_root;
    }

inline
Action_data_base* Module::current_action_data()
    {
    return _current_action_data;
    }
    
inline
void Module::set_gestures_disabled( bool set )
    {
    if (set)
        settings.disableGestures();
    else
        settings.enableGestures();
    }

inline
bool Module::gestures_disabled() const
    {
    return settings.areGesturesDisabled();
    }

inline
void Module::set_gesture_button( int button )
    {
    settings.setGestureMouseButton( button );    
    }

inline
int Module::gesture_button() const
    {
    return settings.gestureMouseButton();
    }

inline
void Module::set_gesture_timeout( int time )
    {
    settings.setGestureTimeOut( time );
    }

inline
int Module::gesture_timeout() const
    {
    return settings.gestureTimeOut();
    }

inline
const Windowdef_list* Module::gestures_exclude() const
    {
    return settings.gesturesExclude();
    }

inline
void Module::set_daemon_disabled( bool disabled_P )
    {
    if (disabled_P)
        settings.disableDaemon();
    else
        settings.enableDaemon();
    }

inline
bool Module::daemon_disabled() const
    {
    return settings.isDaemonDisabled();
    }


inline
void Module::set_voice_shortcut( const KShortcut& cut)
   {
    settings.setVoiceShortcut(cut);
   }

inline 
KShortcut Module::voice_shortcut() const
   {
   return settings.voiceShortcut();
   }


} // namespace KHotKeys

#endif
