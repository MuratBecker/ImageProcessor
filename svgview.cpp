/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "svgview.h"

#include <QSvgRenderer>

#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsSvgItem>
#include <QPaintEvent>
#include <qmath.h>

#ifdef USE_OPENGLWIDGETS
#include <QtOpenGLWidgets/qopenglwidget.h>
#endif

/*****************************************************************************
******* the beginning of the code block of the SvgView class implementaion ***
***************************************************************+**************/

SvgView::SvgView(QWidget *parent)
    : QGraphicsView(parent)
    , svgItem(nullptr)
{
    setScene(new QGraphicsScene(this));
    setTransformationAnchor(AnchorUnderMouse);
    setDragMode(ScrollHandDrag);
    setViewportUpdateMode(FullViewportUpdate);
}

bool SvgView::openFile(const QString &fileNameParam)
{
    QGraphicsScene *scene = QGraphicsView::scene();

    fileName = fileNameParam;
    svgItem = new QGraphicsSvgItem(fileName);
    if ( !svgItem->renderer()->isValid() )
        return false;

    scene->clear();

    scene->addItem(svgItem);
    return true;
}

qreal SvgView::zoomFactor() const
{
    return transform().m11();
}

void SvgView::zoomIn()
{
    zoomBy(2);
}

void SvgView::zoomOut()
{
    zoomBy(0.5);
}

void SvgView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
}

void SvgView::wheelEvent(QWheelEvent *event)
{
    zoomBy(qPow(1.2, event->angleDelta().y() / 240.0));
}

void SvgView::zoomBy(qreal factor)
{
    const qreal currentZoom = zoomFactor();
    if ((factor < 1 && currentZoom < 0.1) || (factor > 1 && currentZoom > 10))
        return;
    scale(factor, factor);
    emit zoomChanged();
}

/****************************************************************************************
******* the beginning of the code block of the CompositionSvgView class implementaion ***
***************************************************************+*************************/

CompositionSvgView::CompositionSvgView(QWidget *parent)
    : QGraphicsView(parent)
    , firstSvgItem(nullptr)
    , secondSvgItem(nullptr)
{
    setScene(new QGraphicsScene(this));
    setTransformationAnchor(AnchorUnderMouse);
    setDragMode(ScrollHandDrag);
    setViewportUpdateMode(FullViewportUpdate);
}

void CompositionSvgView::loadSvgItems(SvgView *firstSvgParam, SvgView *secongSvgParam)
{
    QGraphicsScene *scene = QGraphicsView::scene();

//    firstSvgItem = new QGraphicsSvgItem(firstSvgItemParam);
//    secondSvgItem = new QGraphicsSvgItem(secongSvgItemParam);

    firstSvgItem = new QGraphicsSvgItem(firstSvgParam->fileName);
    secondSvgItem = new QGraphicsSvgItem(secongSvgParam->fileName);

    scene->clear();

    scene->addItem(firstSvgItem);
    scene->addItem(secondSvgItem);
}

qreal CompositionSvgView::zoomFactor() const
{
    return transform().m11();
}

void CompositionSvgView::zoomIn()
{
    zoomBy(2);
}

void CompositionSvgView::zoomOut()
{
    zoomBy(0.5);
}

void CompositionSvgView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
}

void CompositionSvgView::wheelEvent(QWheelEvent *event)
{
    zoomBy(qPow(1.2, event->angleDelta().y() / 240.0));
}

void CompositionSvgView::zoomBy(qreal factor)
{
    const qreal currentZoom = zoomFactor();
    if ((factor < 1 && currentZoom < 0.1) || (factor > 1 && currentZoom > 10))
        return;
    scale(factor, factor);
    emit zoomChanged();
}
