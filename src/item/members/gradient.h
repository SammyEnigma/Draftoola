/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2019 Martin Reininger <nitramr>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

**************************************************************************************/

#ifndef GRADIENT_H
#define GRADIENT_H

#include <QString>
#include <QDebug>
#include <QGradient>

#include <utilities.h>
#include <abstractproperty.h>

class Gradient : public AbstractProperty
{

    Q_CLASSINFO("Version", "1.0.0")

    Q_PROPERTY(qreal angle READ angle WRITE setAngle)
    Q_PROPERTY(QPointF center READ center WRITE setCenter)
    Q_PROPERTY(QPointF start READ start WRITE setStart)
    Q_PROPERTY(QPointF end READ finalStop WRITE setFinalStop)
    Q_PROPERTY(QPointF focalPoint READ focalPoint WRITE setFocalPoint)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius)

public:
    Gradient();    
    Gradient(QString caption, const QGradient &gradient);
    Gradient(const Gradient &) = default;
    ~Gradient() = default;

    Gradient &operator=(const Gradient &) = default;
    bool operator==( const Gradient & other ) const;
    inline bool operator!=(const Gradient &gradient) const { return !(operator==(gradient)); }
    friend QDataStream &operator<<(QDataStream &out, const Gradient &obj);
    friend QDataStream &operator>>(QDataStream &in, Gradient &obj);

#ifndef QT_NO_DEBUG_STREAM
    friend QDebug operator<<(QDebug dbg, const Gradient &gradient);
#endif

    QRadialGradient radial(QRectF target = QRectF()) const;    
    QConicalGradient conical(QRectF target = QRectF()) const;
    QLinearGradient linear(QRectF target = QRectF()) const;
    QLinearGradient linear(QLineF target) const;

    FillType type() const;

    QGradientStops stops() const;
    void setStops(QGradientStops stops);

    qreal angle() const;
    void setAngle(qreal angle);

    QGradient::Spread spread() const;
    void setSpread(QGradient::Spread spread);

    QGradient::CoordinateMode coordinateMode() const;
    void setCoordinateMode(QGradient::CoordinateMode cmode);

    QGradient::InterpolationMode interpolationMode() const;
    void setInterpolationMode(QGradient::InterpolationMode imode);

    QPointF center() const;
    void setCenter(QPointF center);

    QPointF start() const;
    void setStart(QPointF start);

    QPointF finalStop() const;
    void setFinalStop(QPointF stop);

    QPointF focalPoint() const;
    void setFocalPoint(QPointF focal);

    qreal radius() const;
    void setRadius(qreal radius);

    void setColorAt(double position, QColor color);


private:
    FillType m_type;
    QGradientStops m_stops;
    qreal m_angle;
    QGradient::Spread m_spread;
    QGradient::CoordinateMode  m_cmode;
    QGradient::InterpolationMode m_imode;
    QPointF m_center;
    QPointF m_start;
    QPointF m_stop;
    QPointF m_focal;
    qreal m_radius;

    void fromObject(AbstractProperty object);

};
Q_DECLARE_METATYPE(Gradient)



#endif // GRADIENT_H
