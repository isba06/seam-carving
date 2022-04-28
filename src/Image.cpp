#include "Image.h"

Image::Image(std::vector<std::vector<Image::Pixel>> table)
    : m_table(std::move(table))
{
}

Image::Pixel::Pixel(int red, int green, int blue)
    : m_red(red)
    , m_green(green)
    , m_blue(blue)
{
}

Image::Pixel Image::GetPixel(size_t columnId, size_t rowId) const
{
    return m_table[columnId][rowId];
}

size_t Image::column_size() const
{
    return m_table.size();
}

size_t Image::row_size() const
{
    return m_table[0].size();
}

void Image::delete_pixel_horizontal(size_t columnId, size_t rowId)
{
    auto it = m_table[columnId].begin();
    m_table[columnId].erase(it + rowId);
}

void Image::delete_pixel_vertical(size_t columnId, size_t rowId)
{
    for (size_t column = columnId; column < m_table.size() - 1; ++column) {
        m_table[column][rowId] = m_table[column + 1][rowId];
    }
}
void Image::remove_last_column()
{
    m_table.pop_back();
}

int Image::Pixel::sum_of_squares_rgb() const
{
    return (m_red * m_red) + (m_green * m_green) + (m_blue * m_blue);
}

Image::Pixel Image::Pixel::operator-(const Image::Pixel & other) const
{
    auto new_pxl = Image::Pixel(this->m_red - other.m_red,
                                this->m_green - other.m_green,
                                this->m_blue - other.m_blue);
    return new_pxl;
}