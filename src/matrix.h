#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "region.h"
#include "vec3.h"

enum Voxel : uint8_t {
  Void = 0,
  Full = 1,
};

struct Matrix {
    // Construct an empty invalid matrix.
    Matrix();
    // Construct an empty Matrix with resolution R.
    explicit Matrix(int R_);
    Matrix(int R_, Voxel filled_value);
    // Construct Matrix from MDL file.
    Matrix(const std::string& filepath);

    Matrix transpose();

    Voxel& operator()(int x, int y, int z) {
        return buf[(z * R + y) * R + x];
    }
    Voxel operator()(int x, int y, int z) const {
        return buf[(z * R + y) * R + x];
    }
    Voxel& operator()(const Vec3& p) { return operator()(p.x, p.y, p.z); }
    Voxel operator()(const Vec3& p) const { return operator()(p.x, p.y, p.z); }

    // is this a valid matrix?
    bool is_valid_matrix() const {
        return 0 < R && !buf.empty();
    }

    bool is_in_matrix(int x, int y, int z) const {
         return (0 <= x && x < R) && (0 <= y && y < R) && (0 <= z && z < R);
    }
    bool is_in_matrix(const Vec3& p) const { return is_in_matrix(p.x, p.y, p.z); }

    bool any_full(Region r) const {
        r = r.canonical();
        for (int z = r.c1.z; z <= r.c2.z; ++z) {
            for (int y = r.c1.y; y <= r.c2.y; ++y) {
                for (int x = r.c1.x; x <= r.c2.x; ++x) {
                    if ((*this)(x, y, z)) return true;
                }
            }
        }
        return false;
    }

    bool dump(std::string output_path);

    bool operator==(const Matrix& other) const {
        if (R != other.R)
            return false;
        if (buf != other.buf)
            return false;
        return true;
    }

    bool operator!=(const Matrix& other) const {
        return !operator==(other);
    }

    int capacity() const;

    int R;
    std::vector<Voxel> buf;
};

bool print_difference(const Matrix& lhs, const Matrix& rhs);
