#include <iostream>
#include <stdio.h>
#include <png.h>

int read_png_file(char const *filename, uint8_t *&pimg, int &width, int &stridex, int &height)
{
    FILE *fp = nullptr;
    png_structp png = nullptr;
    png_infop info = nullptr;
    png_bytep *row_pointers = nullptr;
    int result = -1;

    do
    {
        fp = fopen(filename, "rb");
        if (!fp)
        {
            std::cerr << "can't open the image" << std::endl;
            break;
        }
        png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (!png)
        {
            std::cerr << "not enought memory?" << std::endl;
            break;
        }
        info = png_create_info_struct(png);
        if (!info)
        {
            std::cerr << "it seems, the image is corrupted or not supported" << std::endl;
            break;
        }
        if (setjmp(png_jmpbuf(png)))
        {
            std::cerr << "not enought memory?" << std::endl;
            break;
        }
        png_init_io(png, fp);
        png_read_info(png, info);
        width = png_get_image_width(png, info);
        height = png_get_image_height(png, info);
        if (png_get_bit_depth(png, info) != 8)
        {
            std::cerr << "support 8-bit one channel images only" << std::endl;
            break;
        }
        if (png_get_color_type(png, info) != PNG_COLOR_TYPE_GRAY)
        {
            std::cerr << "support 8-bit one channel images only" << std::endl;
            break;
        }
        png_read_update_info(png, info);
        stridex = png_get_rowbytes(png, info);
        row_pointers = new png_bytep[height];
        pimg = new uint8_t[stridex * height];
        for (int y = 0; y < height; ++y)
        {
            row_pointers[y] = reinterpret_cast<png_bytep>(pimg + y * stridex);
        }

        png_read_image(png, row_pointers);
        delete[] row_pointers;
    } while (false);

    if (fp)
        fclose(fp);
    png_destroy_read_struct(png ? &png : nullptr, info ? &info : nullptr, nullptr);
    return 0;
}

int main()
{
    int width = 0, height = 0, stridex = 0;
    uint8_t *pimg;
    read_png_file("./download.png", pimg, width, stridex, height);
    uint8_t *p = pimg;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            printf("%02X", *p & 0xFF);
            ++p;
        }
        printf("\n");
    }
    return 0;
}