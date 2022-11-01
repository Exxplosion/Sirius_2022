#include "dijkstra.h"
#include <stdio.h>
#include <algorithm>
#include <cstring>

dijkstra::dijkstra(MatrixP &matrix, uint32_t x_s, uint32_t x_f)
{
    this->adjancency_matrix = matrix;
    //this->M = MatrixP::get_m(matrix); ???
    this->M = matrix.get_m();
    this->N = matrix.get_n();

    this->x_s = x_s + 0;
    this->x_f = x_f + (M - 1) * N;

    if (x_s > M)
    {
        std::cout << "x_s out of range!" << std::endl;
    }

    this->count_vertex = N*M;

    //this->path = std::vector<uint32_t>

    this->current_weights = std::vector<uint32_t>(count_vertex, INF_); //???
    current_weights[x_s] = 0;

    this->parrent_array = std::vector<uint32_t>(count_vertex, 0);
    this->marker = std::vector<bool>(count_vertex, false);

    this->adjacency_list = std::vector<std::vector<std::pair<uint32_t, uint32_t>>>(count_vertex);

    matrix_to_adjacency_list(adjacency_list, adjancency_matrix);
}

void dijkstra::matrix_to_adjacency_list(std::vector<std::vector<std::pair<uint32_t, uint32_t>>> &adjacency_list, const MatrixP &adjancency_matrix)
{
    printf("%d x %d", M, N);
    for (uint32_t i = 0; i < adjacency_list.size(); ++i)
    {
        /* if (i == 0)
        {
            adjacency_list[i] = std::vector<std::pair<uint32_t, uint32_t>>(2);
            adjacency_list[i][0] = std::pair(1, adjancency_matrix(0, 1));
            adjacency_list[i][1] = std::pair(M, adjancency_matrix(1, 0));
        } */

        uint32_t i_ = 0, j_ = 0;

        // M - count of rows;


        /* if ((M > N))
        {
            i_ = i / M;
            j_ = i % M;
        }
        else
 */     {
            i_ = i / N;
            j_ = i % N;
        } 

        printf("(i - %d, i_ - %d, j_ - %d)  \n", i, i_, j_);

        // FOR M > N 
        if (j_ == 0)
        {
            if (i_ != M - 1)
            {
                adjacency_list[i] = std::vector<std::pair<uint32_t, uint32_t>>(2);
                adjacency_list[i][0] = std::make_pair(i + 1, adjancency_matrix(i_, j_ + 1));
                adjacency_list[i][1] = std::make_pair(i + M + 1, adjancency_matrix(i_ + 1 , j_));
            }
            else
            {
                adjacency_list[i] = std::vector<std::pair<uint32_t, uint32_t>>(1);
                adjacency_list[i][0] = std::make_pair(i + 1, adjancency_matrix(i_, j_ + 1));
            }
        }
        else 
        {
            if (j_ == N - 1)
            {
                if (i_ != M - 1)
                {
                    adjacency_list[i] = std::vector<std::pair<uint32_t, uint32_t>>(2);
                    adjacency_list[i][0] = std::make_pair(i - 1, adjancency_matrix(i_, j_ - 1));
                    adjacency_list[i][1] = std::make_pair(i + M + 1, adjancency_matrix(i_ + 1, j_));
                }
                else
                {
                    adjacency_list[i] = std::vector<std::pair<uint32_t, uint32_t>>(0);
                    //adjacency_list[i][0] = std::make_pair(i, INF_);
                }
            }
            if ((j_ != 0) && (j_ != N-1) && (i_ == M - 1))
            {
                adjacency_list[i] = std::vector<std::pair<uint32_t, uint32_t>>(2);
                adjacency_list[i][0] = std::make_pair(i + 1, adjancency_matrix(i_, j_ + 1));
                adjacency_list[i][1] = std::make_pair(i - 1, adjancency_matrix(i_, j_ - 1));
            }
            else
            {
                if ((j_ != 0) && (j_ != N - 1) && (i_ != M - 1))
                {
                    adjacency_list[i] = std::vector<std::pair<uint32_t, uint32_t>>(3);
                    adjacency_list[i][0] = std::make_pair(i - 1, adjancency_matrix(i_, j_ - 1));
                    adjacency_list[i][1] = std::make_pair(i + M + 1, adjancency_matrix(i_ + 1, j_));
                    adjacency_list[i][2] = std::make_pair(i + 1, adjancency_matrix(i_, j_ + 1));
                }
            }
        }
    }
}


void dijkstra::print_adjacency_list() const
{
    for (uint32_t i = 0; i < adjacency_list.size(); ++i)
    {
        printf("Vertex %d: \n", i);
        for (uint32_t j = 0; j < adjacency_list[i].size(); j++)
        {
            printf("(%d, %d)", adjacency_list[i][j].first, adjacency_list[i][j].second);
        }
        printf("\n");
    }
}

void dijkstra::find_optimal_weights()
{
    for (uint32_t i = 0; i < count_vertex; ++i)
    {
        int v = -1;
        for (uint32_t j = 0; j < count_vertex; ++j)
        {
            if (!marker[j] && (v == -1 || current_weights[j] < current_weights[v]))
                v = j;
        }
        if ((current_weights[v] == INF_)) //v never be equal -1
            break;
        marker[v] = true;

        for (uint32_t j = 0; j < adjacency_list[v].size(); ++j)
        {
            uint32_t to = adjacency_list[v][j].first, len = adjacency_list[v][j].second;
            if (current_weights[v] + len < current_weights[to])
            {
                current_weights[to] = current_weights[v]+ len;
                parrent_array[to] = v;
            }
        }
    }
}

std::vector<uint32_t>& dijkstra::find_optimal_path()
{
    dijkstra::find_optimal_weights();
    std::vector<uint32_t>* path = new std::vector<uint32_t>(0);

    for (uint32_t v = x_f; v!= x_s; v = parrent_array[v])
    {
        (* path).push_back(v);
    }
    (* path).push_back(x_s);
    std::reverse((*path).begin(), (* path).end());
    //std::memcpy(optimal_path.begin(), path.begin(), sizeof(uint32_t) * path.size()); ??
    this->optimal_path = *path; //copy here???? need copy...
    return (* path);
}

std::vector<uint32_t>& dijkstra::path_to_dumb_view() const
{
    std::vector<uint32_t>* path_dumb = new std::vector<uint32_t>(0);
    for (uint32_t i = 0; i < optimal_path.size(); ++i)
    {
        (*path_dumb).push_back(optimal_path[i] % N); // case M > N
    }
    return (*path_dumb);
}
