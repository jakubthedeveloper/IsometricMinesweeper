#ifndef ISOCONVERT_H
#define ISOCONVERT_H
#include <cmath>
#include <Point.h>
#include <Field.h>

class IsoConvert
{
    public:
        IsoConvert();
        virtual ~IsoConvert();
        Point isoToTwoD(double x, double y);
        Point twoDToIso(double x, double y);
        void pointToField(Point *point, Field *field, int offsetX, int offsetY, int tileWidth, int tileHeight);
    protected:

    private:
};

#endif // ISOCONVERT_H
