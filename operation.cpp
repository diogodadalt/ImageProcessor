#include "operation.h"

//----------------------------------------------------
// Public methods
//----------------------------------------------------
Operation::Operation(QObject *parent) :
    QObject(parent)
{
}

QImage Operation::flipHorizontal(QImage in)
{
    return punctualOperation(in, 0, flipHor);
}

QImage Operation::flipVertical(QImage in)
{
    return punctualOperation(in, 0, flipVer);
}

QImage Operation::luminance(QImage in)
{
    return punctualOperation(in, 0, lum);
}

QImage Operation::negative(QImage in)
{
    return punctualOperation(in, 0, neg);
}

QImage Operation::quantization(QImage in, int value)
{
    return punctualOperation(in, value, quant);
}

QImage Operation::brightness(QImage in, int value)
{
    return punctualOperation(in, value, bright);
}

QImage Operation::contrast(QImage in, int value)
{
    return punctualOperation(in, value, contr);
}

QImage Operation::histogram(QImage in)
{
    QImage image = in;
    int width = image.width();
    int height = image.height();
    uint red;
    uint green;
    uint blue;
    QRgb currentPixLum;
    uint arrHist[256];
    QImage histImage(256, 256, QImage::Format_RGB32);
    for(int i = 0; i < 256; i++)
        arrHist[i] = 0;

    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            red = qRed(image.pixel(x, y));
            green = qGreen(image.pixel(x, y));
            blue = qBlue(image.pixel(x, y));
            currentPixLum = (uint)(0.299*(float)red + 0.587*(float)green + 0.114*(float)blue);
            arrHist[currentPixLum] += 1;
        }
    }

    int shadeFreq = 0;
    for(int i = 0; i < 256; i++)
    {
        shadeFreq = qCeil(((qreal)arrHist[i] / (qreal)(width*height)) * (qreal)256 * (qreal)64);
        for(int j = 0; j < 256; j++)
        {
            if (j <= shadeFreq)
                histImage.setPixel(i, 255-j, qRgb(0, 0, 255));
            else
                histImage.setPixel(i, 255-j, qRgb(255, 255, 255));
        }
    }

    return histImage;
}

QImage Operation::histogramEqualization(QImage in)
{
    int width = in.width();
    int height = in.height();
    QImage newImage(width, height, QImage::Format_RGB32);
    uint red;
    uint green;
    uint blue;
    QRgb currentPixLum;
    uint arrHist[256];
    uint arrHistCum[256];
    uint arrHistRedCum[256];
    uint arrHistGreenCum[256];
    uint arrHistBlueCum[256];
    qreal alpha = 255.0 / (width * height);
    int min = 0;
    int minRed = 0, minGreen = 0, minBlue = 0;
    uint newShade = 0;
    uint newShadeR = 0, newShadeG = 0, newShadeB = 0;

    for(int i = 0; i < 256; i++) {
        arrHist[i] = 0;
        arrHistCum[i] = 0;
        arrHistRedCum[i] = 0;
        arrHistGreenCum[i] = 0;
        arrHistBlueCum[i] = 0;
    }

    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            red = qRed(in.pixel(x, y));
            green = qGreen(in.pixel(x, y));
            blue = qBlue(in.pixel(x, y));
            currentPixLum = (uint)(0.299*(float)red + 0.587*(float)green + 0.114*(float)blue);
            arrHist[currentPixLum] += 1;
        }
    }

    arrHistRedCum[0] = alpha * arrHist[0];
    arrHistGreenCum[0] = alpha * arrHist[0];
    arrHistBlueCum[0] = alpha * arrHist[0];
    for(int i = 1; i <= 255; i++) {
        arrHistRedCum[i] = arrHistRedCum[i-1] + alpha * arrHist[i];
        arrHistGreenCum[i] = arrHistGreenCum[i-1] + alpha * arrHist[i];
        arrHistBlueCum[i] = arrHistBlueCum[i-1] + alpha * arrHist[i];

        if (arrHistRedCum[i] > 0 && minRed == 0)
            minRed = arrHistRedCum[i];
        if (arrHistGreenCum[i] > 0 && minGreen == 0)
            minGreen = arrHistGreenCum[i];
        if (arrHistBlueCum[i] > 0 && minBlue == 0)
            minBlue = arrHistBlueCum[i];
    }


    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            red = qRed(in.pixel(x, y));
            green = qGreen(in.pixel(x, y));
            blue = qBlue(in.pixel(x, y));
            newShadeR = arrHistRedCum[red];
            newShadeG = arrHistGreenCum[green];
            newShadeB = arrHistBlueCum[blue];
            newImage.setPixel(x, y, qRgb(newShadeR, newShadeG, newShadeB));
        }
    }

    return newImage;
}

QImage Operation::zoomOut(QImage img, int wVal, int hVal)
{
    int width = img.width();
    int height = img.height();
    int newWidth = qCeil((float)width/(float)wVal);
    int newHeight = qCeil((float)height/(float)hVal);
    QImage newImage(newWidth, newHeight, QImage::Format_RGB32);
    uint red;
    uint green;
    uint blue;
    QPoint p(0, 0);
    for(int x = 0; x < newWidth; x++)
    {
        for(int y = 0; y < newHeight; y++)
        {
            red = 0;
            green = 0;
            blue = 0;
            for(int wf = 0; wf < wVal; wf++)
            {
                for(int hf = 0; hf < hVal; hf++)
                {
                    p.setX((x * wVal) + wf);
                    p.setY((y * hVal) + hf);
                    p.setX((p.x() > width-1) ? width-1 : p.x());
                    p.setY((p.y() > height-1) ? height-1 : p.y());
                    red += qRed(img.pixel(p.x(), p.y()));
                    green += qGreen(img.pixel(p.x(), p.y()));
                    blue += qBlue(img.pixel(p.x(), p.y()));
                }
            }
            red = qCeil((float)red / (float)(wVal*hVal));
            green = qCeil((float)green / (float)(wVal*hVal));
            blue = qCeil((float)blue / (float)(wVal*hVal));
            newImage.setPixel(x, y, qRgb(red, green, blue));
        }
    }
    return newImage;
}

QImage Operation::zoomIn(QImage img)
{
    int width = img.width();
    int height = img.height();
    int newWidth = 2 * width;
    int newHeight = 2 * height;
    QImage newImage(newWidth, newHeight, QImage::Format_RGB32);
    for(int x = 0; x < newWidth; x++)
    {
        for(int y = 0; y < newHeight; y++)
        {
            if ((x == 0 || x % 2 == 0) && (y == 0 || y % 2 == 0))
                newImage.setPixel(x, y, img.pixel(x / 2, y / 2));
        }
    }

    uint red, green, blue;
    int xPos, yPos;
    for(int x = 0; x < newWidth; x++)
    {
        for(int y = 0; y < newHeight; y++)
        {
            if ((x % 2 != 0) || (y % 2 != 0))
            {
                if (x == 0 || x % 2 == 0)
                {
                    yPos = (y+1 >= newHeight) ? newHeight-1 : y+1;
                    red = qRed(newImage.pixel(x, y-1)) + qRed(newImage.pixel(x, yPos));
                    red = qCeil((float)red / 2.0) ;
                    green = qGreen(newImage.pixel(x, y-1)) + qGreen(newImage.pixel(x, yPos));
                    green = qCeil((float)green / 2.0) ;
                    blue = qBlue(newImage.pixel(x, y-1)) + qBlue(newImage.pixel(x, yPos));
                    blue = qCeil((float)blue / 2.0) ;
                    newImage.setPixel(x, y, qRgb(red, green, blue));
                }
            }
        }
    }

    for(int x = 0; x < newWidth; x++)
    {
        for(int y = 0; y < newHeight; y++)
        {
            if ((x % 2 != 0) || (y % 2 != 0))
            {
                if (!(x == 0 || x % 2 == 0))
                {
                    xPos = (x+1 >= newWidth) ? newWidth-1 : x+1;
                    red = qRed(newImage.pixel(x-1, y)) + qRed(newImage.pixel(xPos, y));
                    red = qCeil((float)red / 2.0) ;
                    green = qGreen(newImage.pixel(x-1, y)) + qGreen(newImage.pixel(xPos, y));
                    green = qCeil((float)green / 2.0) ;
                    blue = qBlue(newImage.pixel(x-1, y)) + qBlue(newImage.pixel(xPos, y));
                    blue = qCeil((float)blue / 2.0) ;
                    newImage.setPixel(x, y, qRgb(red, green, blue));
                }
            }
        }
    }
    return newImage;
}

QImage Operation::rotateLeft(QImage img)
{
    int width = img.width();
    int height = img.height();
    QImage newImage(width, height, QImage::Format_RGB32);
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            newImage.setPixel(x, y, img.pixel(height-y-1, x));
        }
    }
    return newImage;
}

QImage Operation::rotateRight(QImage img)
{
    int width = img.width();
    int height = img.height();
    QImage newImage(width, height, QImage::Format_RGB32);
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            newImage.setPixel(x, y, img.pixel(y, width-x-1));
        }
    }
    return newImage;
}

QImage Operation::convolution(QImage img, QVector<qreal> kernel)
{
    int width = img.width();
    int height = img.height();
    QImage newImage(width, height, QImage::Format_RGB32);
    qreal red;
    qreal green;
    qreal blue;
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            if ((x != 0 && x != width - 1) && (y != 0 && y != height - 1))
            {
                red = (kernel.at(8) * qRed(img.pixel(x-1, y-1))) + (kernel.at(7) * qRed(img.pixel(x, y-1))) + (kernel.at(6) * qRed(img.pixel(x+1, y-1)));
                red += (kernel.at(5) * qRed(img.pixel(x-1, y))) + (kernel.at(4) * qRed(img.pixel(x, y))) + (kernel.at(3) * qRed(img.pixel(x+1, y)));
                red += (kernel.at(2) * qRed(img.pixel(x-1, y+1))) + (kernel.at(1) * qRed(img.pixel(x, y+1))) + (kernel.at(0) * qRed(img.pixel(x+1, y+1)));
                red = (red > 255.0) ? 255.0 : (red < 0) ? 0 : red;

                green = (kernel.at(8) * qGreen(img.pixel(x-1, y-1))) + (kernel.at(7) * qGreen(img.pixel(x, y-1))) + (kernel.at(6) * qGreen(img.pixel(x+1, y-1)));
                green += (kernel.at(5) * qGreen(img.pixel(x-1, y))) + (kernel.at(4) * qGreen(img.pixel(x, y))) + (kernel.at(3) * qGreen(img.pixel(x+1, y)));
                green += (kernel.at(2) * qGreen(img.pixel(x-1, y+1))) + (kernel.at(1) * qGreen(img.pixel(x, y+1))) + (kernel.at(0) * qGreen(img.pixel(x+1, y+1)));
                green = (green > 255.0) ? 255.0 : (green < 0) ? 0 : green;

                blue = (kernel.at(8) * qBlue(img.pixel(x-1, y-1))) + (kernel.at(7) * qBlue(img.pixel(x, y-1))) + (kernel.at(6) * qBlue(img.pixel(x+1, y-1)));
                blue += (kernel.at(5) * qBlue(img.pixel(x-1, y))) + (kernel.at(4) * qBlue(img.pixel(x, y))) + (kernel.at(3) * qBlue(img.pixel(x+1, y)));
                blue += (kernel.at(2) * qBlue(img.pixel(x-1, y+1))) + (kernel.at(1) * qBlue(img.pixel(x, y+1))) + (kernel.at(0) * qBlue(img.pixel(x+1, y+1)));
                blue = (blue > 255.0) ? 255.0 : (blue < 0) ? 0 : blue;

                newImage.setPixel(x, y, qRgb(qCeil(red), qCeil(green), qCeil(blue)));
            }
        }
    }
    return newImage;
}

//----------------------------------------------------
// Private methods
//----------------------------------------------------
QImage Operation::punctualOperation(QImage in, int value, OutValues (*oper)(QImage, InValues))
{
    int width = in.width();
    int height = in.height();
    QImage newImage(width, height, QImage::Format_RGB32);
    InValues inVals;
    OutValues outVals;
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            inVals.color = in.pixel(x, y);
            inVals.pos = QPoint(x, y);
            inVals.val = value;
            outVals = oper(in, inVals);
            newImage.setPixel(outVals.pos.x(), outVals.pos.y(), outVals.color);
        }
    }
    return newImage;
}

OutValues Operation::flipHor(QImage in, InValues inVals)
{
    OutValues po;
    po.pos = QPoint(in.width() - inVals.pos.x() - 1, inVals.pos.y());
    po.color = inVals.color;
    return po;
}

OutValues Operation::flipVer(QImage in, InValues inVals)
{
    OutValues po;
    po.pos = QPoint(inVals.pos.x(), in.height() - inVals.pos.y() - 1);
    po.color = inVals.color;
    return po;
}

OutValues Operation::lum(QImage in, InValues inVals)
{
    QRgb pixColor;
    uint red = qRed(inVals.color);
    uint green = qGreen(inVals.color);
    uint blue = qBlue(inVals.color);
    pixColor = (uint)(0.299*(float)red + 0.587*(float)green + 0.114*(float)blue);
    OutValues po;
    po.pos = QPoint(inVals.pos.x(), inVals.pos.y());
    po.color = qRgb(pixColor, pixColor, pixColor);
    return po;
}

OutValues Operation::neg(QImage in, InValues inVals)
{
    uint red = 255 - qRed(inVals.color);
    uint green = 255 - qGreen(inVals.color);
    uint blue = 255 - qBlue(inVals.color);
    OutValues po;
    po.pos = QPoint(inVals.pos.x(), inVals.pos.y());
    po.color = qRgb(red, green, blue);
    return po;
}

OutValues Operation::quant(QImage in, InValues inVals)
{
    uint r = (uint)((float)256/(float)inVals.val);
    uint s = 0;
    uint pix = 0;
    uint red = qRed(inVals.color);
    uint green = qGreen(inVals.color);
    uint blue = qBlue(inVals.color);
    QRgb pixColor = (uint)(0.299*(float)red + 0.587*(float)green + 0.114*(float)blue);
    s = qCeil((float)pixColor/(float)r);
    pix = ((s*r) - r) + qCeil((float)r/(float)2);
    OutValues po;
    po.pos = QPoint(inVals.pos.x(), inVals.pos.y());
    po.color = qRgb(pix, pix, pix);
    return po;
}

OutValues Operation::bright(QImage in, InValues inVals)
{
    uint red = qRed(inVals.color);
    uint green = qGreen(inVals.color);
    uint blue = qBlue(inVals.color);
    red = ((red + inVals.val) > 255) ? 255 : ((red + inVals.val) < 0) ? 0 : red + inVals.val;
    green = ((green + inVals.val) > 255) ? 255 : ((green + inVals.val) < 0) ? 0 : green + inVals.val;
    blue = ((blue + inVals.val) > 255) ? 255 : ((blue + inVals.val) < 0) ? 0 : blue + inVals.val;
    OutValues po;
    po.pos = QPoint(inVals.pos.x(), inVals.pos.y());
    po.color = qRgb(red, green, blue);
    return po;
}

OutValues Operation::contr(QImage in, InValues inVals)
{
    uint red = qRed(inVals.color);
    uint green = qGreen(inVals.color);
    uint blue = qBlue(inVals.color);
    red = ((red * inVals.val) > 255) ? 255 : red * inVals.val;
    green = ((green * inVals.val) > 255) ? 255 : green * inVals.val;
    blue = ((blue * inVals.val) > 255) ? 255 : blue * inVals.val;
    OutValues po;
    po.pos = QPoint(inVals.pos.x(), inVals.pos.y());
    po.color = qRgb(red, green, blue);
    return po;
}
