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

        int sum_of_squares_rgb() const;
        Pixel operator-(const Pixel & other) const;
    };

    Image(std::vector<std::vector<Pixel>> table);

    Pixel GetPixel(size_t columnId, size_t rowId) const;

    std::vector<std::vector<Pixel>> m_table;

    size_t column_size() const;
    size_t row_size() const;
    void delete_pixel_vertical(size_t, size_t);
    void delete_pixel_horizontal(size_t, size_t);
    void remove_last_vec();
};