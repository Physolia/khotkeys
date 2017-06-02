#ifndef SETTINGS_READER_V2_H
#define SETTINGS_READER_V2_H
/**
 * Copyright (C) 1999-2001 Lubos Lunak <l.lunak@kde.org>
 * Copyright (C) 2009 Michael Jansen <kde@michael-jansen.biz>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License version 2 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 **/

#include "action_data/action_data_visitor.h"
#include "actions/actions.h"
#include "triggers/triggers.h"
#include "settings.h"

class KConfigBase;
class KConfigGroup;

namespace KHotKeys {
    class Settings;
    class Trigger_list;
    template< typename T, typename A > class SimpleActionDataHelper;
}


/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class SettingsReaderV2 :
        public KHotKeys::ActionDataVisitor,

        public KHotKeys::ActionVisitor,
        public KHotKeys::ActivateWindowActionVisitor,
        public KHotKeys::CommandUrlActionVisitor,
        public KHotKeys::DBusActionVisitor,
        public KHotKeys::KeyboardInputActionVisitor,
        public KHotKeys::MenuEntryActionVisitor,

        public KHotKeys::TriggerVisitor,
        public KHotKeys::WindowTriggerVisitor,
        public KHotKeys::ShortcutTriggerVisitor,
        public KHotKeys::GestureTriggerVisitor
    {
public:

    SettingsReaderV2(
            KHotKeys::Settings *settings,
            bool loadAll = true,
            KHotKeys::ActionState _stateStrategy = KHotKeys::Disabled,
            const QString &importId = QString());

    virtual ~SettingsReaderV2();

    void read(const KConfigBase &config, KHotKeys::ActionDataGroup *parent);

    KHotKeys::ActionDataGroup *readGroup(const KConfigGroup &config, KHotKeys::ActionDataGroup *parent);

    KHotKeys::ActionDataBase *readActionData(const KConfigGroup &config, KHotKeys::ActionDataGroup *parent);

    KHotKeys::Trigger_list *readTriggerList(const KConfigGroup &config, KHotKeys::ActionData *parent);

    KHotKeys::ActionList *readActionList(const KConfigGroup &config, KHotKeys::ActionData *parent);

    void visitActionDataBase(KHotKeys::ActionDataBase *base) Q_DECL_OVERRIDE;

    void visitActionData(KHotKeys::ActionData *group) Q_DECL_OVERRIDE;

    void visitActionDataGroup(KHotKeys::ActionDataGroup *group) Q_DECL_OVERRIDE;

    void visitGenericActionData(KHotKeys::Generic_action_data *data) Q_DECL_OVERRIDE;

    void visitMenuentryShortcutActionData(KHotKeys::MenuEntryShortcutActionData *data) Q_DECL_OVERRIDE;

    void visitSimpleActionData(KHotKeys::SimpleActionData *data) Q_DECL_OVERRIDE;

    void visit(KHotKeys::ActivateWindowAction&) Q_DECL_OVERRIDE;
    void visit(KHotKeys::CommandUrlAction&) Q_DECL_OVERRIDE;
    void visit(KHotKeys::DBusAction&) Q_DECL_OVERRIDE;
    void visit(KHotKeys::KeyboardInputAction&) Q_DECL_OVERRIDE;
    void visit(KHotKeys::MenuEntryAction&) Q_DECL_OVERRIDE;

    void visit(KHotKeys::GestureTrigger&) Q_DECL_OVERRIDE;
    void visit(KHotKeys::ShortcutTrigger&) Q_DECL_OVERRIDE;
    void visit(KHotKeys::WindowTrigger&) Q_DECL_OVERRIDE;
private:

    const KConfigGroup *_config;

    KHotKeys::Settings *_settings;

    bool _loadAll;

    KHotKeys::ActionState _stateStrategy;

    QString _importId;

    }; // SettingsReaderV2


#endif /* SETTINGS_READER_V2_H */

