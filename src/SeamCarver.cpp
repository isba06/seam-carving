#include "SeamCarver.h"

#include <cmath>

SeamCarver::SeamCarver(Image image)
    : m_image(std::move(image))
{
}

const Image & SeamCarver::GetImage() const
{
    return m_image;
}

size_t SeamCarver::GetImageWidth() const
{

    return m_image.column_size();
}

size_t SeamCarver::GetImageHeight() const
{
    return m_image.row_size();
}

double SeamCarver::GetPixelEnergy(size_t columnId, size_t rowId) const
{
    size_t column_right, column_left;
    size_t row_down, row_up;
    if (columnId == m_image.column_size() - 1) {
        column_right = 0;
    }
    else {
        column_right = columnId + 1;
    }
    if (columnId == 0) {
        column_left = m_image.column_size() - 1;
    }
    else {
        column_left = columnId - 1;
    }

    if (rowId == m_image.row_size() - 1) {
        row_down = 0;
    }
    else {
        row_down = rowId + 1;
    }
    if (rowId == 0) {
        row_up = m_image.row_size() - 1;
    }
    else {
        row_up = rowId - 1;
    }
    auto x_left = m_image.GetPixel(column_left, rowId);
    auto x_right = m_image.GetPixel(column_right, rowId);
    auto y_up = m_image.GetPixel(columnId, row_up);
    auto y_down = m_image.GetPixel(columnId, row_down);
    auto energy = (x_left - x_right).sum_of_squares_rgb() + (y_down - y_up).sum_of_squares_rgb();
    return sqrt(energy);
}

SeamCarver::Seam SeamCarver::FindHorizontalSeam() const
{
    Seam seam_min;
    size_t sum_energy_min = static_cast<size_t>(-1);
    for (size_t row_id = 0; row_id < m_image.row_size(); ++row_id) {
        Seam seam;
        auto id = row_id;
        size_t sum_energy = GetPixelEnergy(0, id);
        seam.push_back(id);
        for (size_t column_id = 0; column_id < m_image.column_size() - 1; ++column_id) {
            auto pixel_medium = GetPixelEnergy(column_id + 1, id);
            auto pixel_up_energy = GetPixelEnergy(column_id + 1, id);
            auto pixel_down_energy = GetPixelEnergy(column_id + 1, id);
            double min = pixel_medium;
            if (id != 0) {
                pixel_up_energy = GetPixelEnergy(column_id + 1, id - 1);
            }
            if (id != m_image.row_size() - 1) {
                pixel_down_energy = GetPixelEnergy(column_id + 1, id + 1);
            }
            if (pixel_up_energy < min && pixel_up_energy < pixel_down_energy) {
                min = pixel_up_energy;
                --id;
            }
            else if (pixel_down_energy < min && pixel_down_energy < pixel_up_energy) {
                min = pixel_down_energy;
                ++id;
            }
            sum_energy += min;
            seam.push_back(id);
        }
        if (sum_energy < sum_energy_min) {
            sum_energy_min = sum_energy;
            seam_min = seam;
        }
    }
    return seam_min;
}

SeamCarver::Seam SeamCarver::FindVerticalSeam() const
{
    Seam seam_min;
    size_t sum_energy_min = static_cast<size_t>(-1);
    for (size_t column_id = 0; column_id < m_image.column_size(); ++column_id) {
        Seam seam;
        auto id = column_id;
        size_t sum_energy = GetPixelEnergy(id, 0);
        double min;
        seam.push_back(id);
        for (size_t row_id = 0; row_id < m_image.row_size() - 1; ++row_id) {
            auto pixel_medium = GetPixelEnergy(id, row_id + 1);
            auto pixel_left_energy = GetPixelEnergy(id, row_id + 1);
            auto pixel_right_energy = GetPixelEnergy(id, row_id + 1);
            min = pixel_medium;
            if (id != 0) {
                pixel_left_energy = GetPixelEnergy(id - 1, row_id + 1);
            }
            if (id != m_image.column_size() - 1) {
                pixel_right_energy = GetPixelEnergy(id + 1, row_id + 1);
            }
            if (pixel_left_energy < min && pixel_left_energy < pixel_right_energy) {
                min = pixel_left_energy;
                --id;
            }
            else if (pixel_right_energy < min && pixel_right_energy < pixel_left_energy) {
                min = pixel_right_energy;
                ++id;
            }
            sum_energy += min;
            seam.push_back(id);
        }
        if (sum_energy < sum_energy_min) {
            sum_energy_min = sum_energy;
            seam_min = seam;
        }
    }
    return seam_min;
}

void SeamCarver::RemoveVerticalSeam(const Seam & seam)
{
    for (size_t id = 0, row = 0; row < m_image.row_size(); ++id, ++row) {
        m_image.delete_pixel_vertical(seam[id], row);
    }
    m_image.remove_last_vec();
}

void SeamCarver::RemoveHorizontalSeam(const Seam & seam)
{
    for (size_t column = 0, id = 0; column < m_image.column_size(); ++column, ++id) {
        m_image.delete_pixel_horizontal(column, seam[id]);
    }
}
/*
void SeamCarver::print() const
{
    m_image.print();
}

void SeamCarver::print_energy_table()
{
    for (size_t row = 0; row < m_image.row_size(); ++row) {
        for (size_t col = 0; col < m_image.column_size(); ++col) {
            std::cout << GetPixelEnergy(col, row) << " ";
        }
        std::cout << std::endl;
    }
}*/
