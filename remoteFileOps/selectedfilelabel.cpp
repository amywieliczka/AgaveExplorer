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

#include "selectedfilelabel.h"

#include "filetreenode.h"
#include "remotefiletree.h"
#include "../AgaveClientInterface/filemetadata.h"

SelectedFileLabel::SelectedFileLabel(QWidget *parent) : QLabel(parent)
{
    newSelectedItem(NULL);
}

void SelectedFileLabel::connectFileTreeWidget(RemoteFileTree * connectedTree)
{
    if (myFileTree != NULL)
    {
        QObject::disconnect(myFileTree, 0, this, 0);
    }
    myFileTree = connectedTree;
    if (myFileTree == NULL)
    {
        newSelectedItem(NULL);
        return;
    }
    QObject::connect(myFileTree, SIGNAL(newFileSelected(FileTreeNode*)),
                     this, SLOT(newSelectedItem(FileTreeNode*)));
    newSelectedItem(myFileTree->getSelectedNode());
}

void SelectedFileLabel::newSelectedItem(FileTreeNode * newFileData)
{
    if (newFileData == NULL)
    {
        this->setText("No File Selected.");
    }
    else
    {
        FileMetaData theFileData = newFileData->getFileData();

        QString fileString = "Filename: %1\nType: %2\nSize: %3";
        fileString = fileString.arg(theFileData.getFileName(),
                                    theFileData.getFileTypeString(),
                                    QString::number(theFileData.getSize()));
        this->setText(fileString);
    }
}
