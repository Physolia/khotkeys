#ifndef WINDOW_DEFINITION_LIST_WIDGET_H
#define WINDOW_DEFINITION_LIST_WIDGET_H
/* Copyright (C) 2009 Michael Jansen <kde@michael-jansen.biz>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/


#include "hotkeys_widget_iface.h"

#include "ui_window_definition_list_widget.h"
#include "windows_helper/window_selection_list.h"
#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>



/**
 * @author Michael Jansen <kde@michael-jansen.biz>
 */
class WindowDefinitionListWidget : public HotkeysWidgetIFace
    {
    Q_OBJECT

public:

    /**
     * Default constructor
     */
    WindowDefinitionListWidget(
            KHotKeys::Windowdef_list *windowdef_list,
            QWidget *parent = nullptr);

    WindowDefinitionListWidget(QWidget *parent);

    /**
     * Destructor
     */
    virtual ~WindowDefinitionListWidget();

    void setWindowDefinitions(KHotKeys::Windowdef_list *windowdef_list);

    bool isChanged() const Q_DECL_OVERRIDE;

private:

    void emitChanged(bool);

private Q_SLOTS:

    void slotDelete(bool);
    void slotDuplicate(bool);
    void slotEdit(bool);
    void slotNew(bool);

protected:

    void doCopyFromObject() Q_DECL_OVERRIDE;
    void doCopyToObject() Q_DECL_OVERRIDE;

private:

    // The Windowdefinition list
    KHotKeys::Windowdef_list    *_windowdefs;
    KHotKeys::Windowdef_list    *_working;

    // The User Interface
    Ui::WindowDefinitionListWidget ui;

    // Unsaved changes?
    bool _changed;
};


class WindowDefinitionListDialog : public QDialog
    {
    Q_OBJECT

public:

    WindowDefinitionListDialog(
            KHotKeys::Windowdef_list *list,
            QWidget *parent=nullptr)
        :   QDialog(parent)
            ,def(nullptr)
        {
        setLayout(new QVBoxLayout);

        def = new WindowDefinitionListWidget(list, this);
        def->copyFromObject();

        layout()->addWidget(def);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                | QDialogButtonBox::Cancel);

        layout()->addWidget(buttonBox);


        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accepted);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::rejected);
        }


    ~WindowDefinitionListDialog()
        {
        def = nullptr;
        }


    void accept() Q_DECL_OVERRIDE
        {
        def->copyToObject();
        QDialog::accept();
        }

private:

    WindowDefinitionListWidget *def;
    };

#endif /* #ifndef WINDOW_DEFINITION_LIST_WIDGET_H */
