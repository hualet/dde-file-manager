/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     Rekols <rekols@foxmail.com>
 *
 * Maintainer: Rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "dfmsidebarrecentitem.h"
#include "dfilemanagerwindow.h"
#include "dfmsidebartagitem.h"
#include "dtagactionwidget.h"
#include "dfilemenu.h"
#include "dfmeventdispatcher.h"
#include "dfmevent.h"

#include "views/windowmanager.h"

#include <QWidgetAction>

DFM_BEGIN_NAMESPACE

DFMSideBarRecentItem::DFMSideBarRecentItem(DFMStandardPaths::StandardLocation location, QWidget *parent)
    : DFMSideBarDefaultItem(location, parent)
{
}

QMenu *DFMSideBarRecentItem::createStandardContextMenu() const
{
    DFileMenu *menu = new DFileMenu();
    DFileManagerWindow *wnd = qobject_cast<DFileManagerWindow *>(topLevelWidget());
    bool shouldDisable = !WindowManager::tabAddableByWinId(wnd->windowId());

    menu->addAction(QObject::tr("Open in new window"), [this]() {
        WindowManager::instance()->showNewWindow(url(), true);
    });

    menu->addAction(QObject::tr("Open in new tab"), [wnd, this]() {
        wnd->openNewTab(url());
    })->setDisabled(shouldDisable);

#ifdef QT_DEBUG
    menu->addSeparator();

    menu->addAction(QObject::tr("Clear recent history"), [](){
        //
    });
#endif // QT_DEBUG

    return menu;
}

DFM_END_NAMESPACE
