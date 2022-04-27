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
    for (size_t row = rowId; row < m_table[columnId].size() - 1; ++row) {
        m_table[columnId][row] = m_table[columnId][row + 1];
    }
}
void Image::remove_last_vec()
{
    m_table.resize(m_table.size() - 1);
}
