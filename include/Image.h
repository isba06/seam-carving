#pragma once
#include <iostream>
#include <vector>

struct Image
{
    struct Pixel
    {
        Pixel(int red, int green, int blue);
        Pixel() = default;
        int m_red;
        int m_green;
        int m_blue;

        int sum_of_squares_rgb() const
        {
            return (m_red * m_red) + (m_green * m_green) + (m_blue * m_blue);
        }
        Pixel operator-(const Pixel & other) const
        {
            auto new_pxl = Pixel(this->m_red - other.m_red,
                                 this->m_green - other.m_green,
                                 this->m_blue - other.m_blue);
            return new_pxl;
        }
        friend std::ostream & operator<<(std::ostream & os, const Pixel & obj)
        {
            os << obj.m_red << ' ' << obj.m_blue << ' ' << obj.m_green;
            return os;
        }
    };

    Image(std::vector<std::vector<Pixel>> table);
    Pixel GetPixel(size_t columnId, size_t rowId) const;
    size_t column_size() const;
    size_t row_size() const;
    void delete_pixel_vertical(size_t, size_t);
    void delete_pixel_horizontal(size_t, size_t);
    void remove_last_vec();

    std::vector<std::vector<Pixel>> m_table;
};