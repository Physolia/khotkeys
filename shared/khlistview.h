/****************************************************************************

 KHotKeys
 
 Copyright (C) 1999-2002 Lubos Lunak <l.lunak@kde.org>

 Distributed under the terms of the GNU General Public License version 2.
 
****************************************************************************/

#ifndef _KHLISTVIEW_H_
#define _KHLISTVIEW_H_

#include <qtimer.h>

#include <qlistview.h>

namespace KHotKeys
{

class KHListView
    : public QListView
    // use QListView rather than KListView ... why the hell should a listview
    // obey single/double click settings?
    {
    Q_OBJECT
    Q_PROPERTY( bool forceSelect READ forceSelect WRITE setForceSelect )
    public:
        KHListView( QWidget* parent_P, const char* name_P = NULL );
        virtual void clear();
        virtual void insertItem( QListViewItem* item_P );
        bool forceSelect() const;
        void setForceSelect( bool force_P );
    signals:
        void current_changed( QListViewItem* item_P );
    private slots:
        void slot_selection_changed( QListViewItem* item_P );
        void slot_selection_changed();
        void slot_current_changed( QListViewItem* item_P );
        void slot_insert_select();
    private:
        QListViewItem* saved_current_item;
        bool in_clear;
        bool force_select;
        QTimer insert_select_timer;
    };

//***************************************************************************
// Inline
//***************************************************************************

inline
void KHListView::setForceSelect( bool force_P )
    {
    force_select = force_P;
    }
    
inline
bool KHListView::forceSelect() const
    {
    return force_select;
    }
    
} // namespace KHotKeys

#endif
