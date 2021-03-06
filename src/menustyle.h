/*
 * menustyle.h
 *
 * (c) 2015 by Muhammad Bashir Al-Noimi
 * (c) 2014 by Stefan Frings
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 */

/**
  @file
  @author Muhammad Bashir Al-Noimi
  @author Stefan Frings
*/

#ifndef MENUSTYLE_H
#define MENUSTYLE_H

#include <QProxyStyle>
#include <QStyleOption>

/**
 * This proxy style changes the size of icons relative to the font size.
 * I use it to give icons a proper size on high-res displays.
 */
class MenuStyle : public QProxyStyle {

public:
    /** Constructor */
    MenuStyle(QStyle *style = Q_NULLPTR);

    /** Convert the provided dimension in dp (device-independent pixels) to the
     *  corresponding number of actual pixels on the current display. */
    static int dpToPixels(int dp);

    /** Always draw QToolButtons in the default flat style */
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option,
                            QPainter *painter, const QWidget *widget = Q_NULLPTR) const;

    /**Never show buttons with input focus as highlighted */
    void drawControl(ControlElement element, const QStyleOption *option,
                     QPainter *painter, const QWidget *widget = Q_NULLPTR) const;

    /** Calculate the size of icons relative to the font size */
    int pixelMetric(PixelMetric metric, const QStyleOption* option=0, const QWidget* widget=0) const;

};

#endif // MENUSTYLE_H
