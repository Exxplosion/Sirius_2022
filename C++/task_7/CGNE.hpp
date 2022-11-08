#pragma once
#include "COO.hpp"
#include "CSC.hpp"
#include "CSR.hpp"
#include <vector>
#include <iostream>
#include <type_traits>
#include <typeinfo>

enum class vec_operation
{
    minus,
    plus
};

template <class vector_type, vec_operation operation_type>
vector_type vec_sum(vector_type &a, const vector_type &b)
{
    if (a.size() != b.size())
    {
        throw std::runtime_error("vec_sum: operands have diffirent dimension");
    }

    if (operation_type == vec_operation::plus)
    {
        for(size_t i = 0; i < a.size(); i++)
        {
            a[i] += b[i];
        }
    }
    else
    {
        for (size_t i = 0; i < a.size(); i++)
        {
            //std::cout <<"hehe" << a[i] << ' ' << b[i] << std::endl;

            a[i] -= b[i];
        }
    }
    return a; //optimization here?
}


template <class vector_type>
vector_type scalar_product(const vector_type &a, const vector_type &b)
{
    if (a.size() != b.size())
    {
        throw std::runtime_error("scalar: operands have diffirent dimension");
    }

    vector_type out(1, 0);
    for (size_t i = 0; i < a.size(); i++)
    {
        out[0] += a[i] * b[i];
    }

    return out;
}

template <class vector_type>
vector_type product_on_number(const vector_type &a, const vector_type &b)
{
    if (a.size() != 1)
    {
        throw std::runtime_error("can not product on not number");
    } 

    vector_type out(b);
    for (size_t i = 0; i < b.size(); i++)
    {
        out[i] *= a.back();
    }
    return out;
}

template <class vector_type>
vector_type euclidean_norm_square(const vector_type &a)
{
    vector_type out(1, 0);
    for (size_t i = 0; i < a.size(); i++)
    {
        out[0] += a[i] * a[i];
    }
    return out;
}

template<class Matrix, class vector_type, class accuracy_err_type>
vector_type CGNE(const Matrix& A, const vector_type& b, accuracy_err_type eps)
{
    vector_type x_k_prev(A.get_rows_number(), 1);
    vector_type out(A.get_rows_number());
    A.matvec(x_k_prev.data(), out.data(), false);

    for (size_t i = 0; i < out.size(); i++)
    {
        std::cout << out[i] << std::endl;
    }

    vector_type b_aux(b);
    vector_type r_k_prev = vec_sum<vector_type, vec_operation::minus>(b_aux, out);
    vector_type z_k_prev = r_k_prev;

    std::cout << "----------------------------------->  \n";

    for (size_t i = 0; i < r_k_prev.size(); i++)
    {
        std::cout << r_k_prev[i] << std::endl;
    }
    vector_type x_k;
    vector_type alpha_k(1);
    vector_type z_k;
    vector_type r_k;
    vector_type beta_k(1);



/* 
    std::vector<vector_type> x;
    std::vector<vector_type> z;
    std::vector<vector_type> r;
    std::vector<vector_type> R;

    x.push_back(x_zero);
    r.push_back(r_zero);
    z.push_back(z_zero);
    R.push_back(r_zero); */

    while (true)
    {

        vector_type out(A.get_rows_number());
        A.matvec(z_k_prev.data(), out.data(), false);

        std::cout << "\n ----------------------------------->  \n";

        for (size_t i = 0; i < out.size(); i++)
        {
            std::cout << out[i] << std::endl;
        }

        vector_type scalar_r_k_prev = scalar_product<vector_type>(r_k_prev, r_k_prev);
        vector_type scalar_A_z_k_prev = scalar_product<vector_type>(out, z_k_prev);
        vector_type scalar_r_k = scalar_product<vector_type>(r_k, r_k);

        std::cout << "\n ----------------------------------->  \n";

        std::cout << "scalar_r_k_prev[0]    " << scalar_r_k_prev[0];

        std::cout << "\n ----------------------------------->  \n";

        std::cout << "scalar_A_z_k_prev[0] " << scalar_A_z_k_prev[0];

        std::cout << "\n ----------------------------------->  \n";

        std::cout << "scalar_r_k[0] / [0]   " << scalar_r_k_prev[0] / scalar_A_z_k_prev[0];

        std::cout << "\n ----------------------------------->  \n";

        alpha_k[0] = (scalar_r_k_prev[0] / scalar_A_z_k_prev[0]);
        x_k = vec_sum<vector_type, vec_operation::plus>(x_k_prev, product_on_number<vector_type>(alpha_k, z_k_prev));

        r_k = vec_sum<vector_type, vec_operation::minus>(r_k_prev, product_on_number<vector_type>(alpha_k, out));

        beta_k[0] = (scalar_r_k[0] / scalar_r_k_prev[0]);

        z_k = vec_sum<vector_type, vec_operation::plus>(r_k, product_on_number<vector_type>(beta_k, z_k_prev));

        vector_type eucld_tmp = euclidean_norm_square<vector_type>(r_k);
        std::cout << "eucld_tmp:    " << eucld_tmp[0] << std::endl;
        if (eucld_tmp[0] < eps * eps)
        {
            return x_k;
        }

        x_k_prev = x_k;
        r_k_prev = r_k;
        z_k_prev = z_k;

        //x_k = r_k = z_k = vector_type 0;

        //return x.back();
    }
}
