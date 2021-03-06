/*********************************************************************************
**
** Copyright (c) 2017 The University of Notre Dame
** Copyright (c) 2017 The Regents of the University of California
**
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice, this
** list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice, this
** list of conditions and the following disclaimer in the documentation and/or other
** materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its contributors may
** be used to endorse or promote products derived from this software without specific
** prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
** EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
** SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
** TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
** BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
** IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
**
***********************************************************************************/

// Contributors:
// Written by Peter Sempolinski, for the Natural Hazard Modeling Laboratory, director: Ahsan Kareem, at Notre Dame

#ifndef EXPLORERWINDOW_H
#define EXPLORERWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QMenu>

class RemoteFileTree;
class FileMetaData;
class FileTreeNode;
class FileOperator;

class ExplorerDriver;
class RemoteDataInterface;
enum class RequestState;

namespace Ui {
class ExplorerWindow;
}

class ExplorerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExplorerWindow(ExplorerDriver * theDriver, QWidget *parent = 0);
    ~ExplorerWindow();

    void startAndShow();

    void addAppToList(QString appName);

private slots:
    void agaveAppSelected(QModelIndex clickedItem);

    void agaveCommandInvoked();
    void finishedAppInvoke(RequestState finalState, QJsonDocument * rawReply);

    void customFileMenu(QPoint pos);

    void copyMenuItem();
    void moveMenuItem();
    void renameMenuItem();
    void deleteMenuItem();

    void uploadMenuItem();
    void uploadFolderMenuItem();
    void downloadFolderMenuItem();

    void createFolderMenuItem();
    void downloadMenuItem();
    void readMenuItem();
    void retriveMenuItem();
    void compressMenuItem();
    void decompressMenuItem();
    void refreshMenuItem();

    void jobRightClickMenu(QPoint);

    void recursiveProcessPopup(bool success, QString message);

private:
    Ui::ExplorerWindow *ui;

    FileTreeNode * targetNode;
    ExplorerDriver * programDriver;

    FileOperator * theFileOperator;
    RemoteDataInterface * dataLink;

    QStandardItemModel taskListModel;
    QString selectedAgaveApp;

    QMap<QString, QStringList> agaveParamLists;

    bool waitingOnCommand = false;
};

#endif // EXPLORERWINDOW_H
