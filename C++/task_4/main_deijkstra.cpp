#include "dijkstra.h"
#include "Matrix.h"


#include <png.h>

int main()
{
    MatrixP A(3, 4);

    dijkstra G(A, 0, 1);

    for (int i = 0; i < 3; i++)
    {
        printf("\n");
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", A(i, j));
        }
    }
    printf("\n");

    G.print_adjacency_list();

    G.find_optimal_weights();

    std::vector<uint32_t> path = G.find_optimal_path();

    for (uint32_t i = 0; i < path.size(); ++i)
    {
        printf("%d ", path[i]);
    }
    printf("\n");
    std::vector<uint32_t> dumb_path = G.path_to_dumb_view<uint32_t>();
    for (uint32_t i = 0; i < dumb_path.size(); ++i)
    {
        printf("%d ", dumb_path[i]);
    }
}
