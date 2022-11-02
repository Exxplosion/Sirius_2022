#pragma once
#include "../matrix/Matrix.h"
#include <vector>
#include <iostream>

class dijkstra
{
    public:
        const uint32_t INF_ = 45000; //45K
        uint32_t x_s;
        uint32_t x_f;
        uint32_t N = 0, M = 0;
        uint32_t count_vertex = 0;
        MatrixP adjancency_matrix;
        std::vector<std::vector<std::pair<uint32_t, uint32_t>>> adjacency_list; //may using typedef here;

        std::vector<uint32_t> current_weights;
        std::vector<uint32_t> parrent_array;
        std::vector<bool> marker;
        std::vector<uint32_t> optimal_path;

        void find_optimal_weights();
        std::vector<uint32_t>& find_optimal_path();
        //std::vector<uint32_t>& path_to_dumb_view() const;

        template<typename T>
        std::vector<T>& path_to_dumb_view() const
        {
            std::vector<T> *path_dumb = new std::vector<T>(0);
            for (uint32_t i = 0; i < optimal_path.size(); ++i)
            {
                if (M >= N)
                {
                    (*path_dumb).push_back(optimal_path[i] % M); // case M > N
                }
                else
                {
                    (*path_dumb).push_back(optimal_path[i] % N); // case M > N
                }
            }
            return (*path_dumb);
        }

        dijkstra() = default;
        dijkstra(MatrixP &enter_matrix, uint32_t x_s, uint32_t x_f);

        void matrix_to_adjacency_list(std::vector<std::vector<std::pair<uint32_t, uint32_t>>>& adjacency_list, const MatrixP& adjancency_matrix);
        void print_adjacency_list() const;
};