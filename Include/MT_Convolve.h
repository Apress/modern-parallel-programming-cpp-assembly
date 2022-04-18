//------------------------------------------------
//               MT_Convolve.h
//------------------------------------------------

#pragma once
#include <fstream>
#include <iomanip>
#include <vector>
#include <random>
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>
#include "OS.h"

template<typename T> std::vector<T> GenGaussianKernel1D(T sigma, size_t ks)
{
    if ((ks < 3) || ((ks & 0x1) == 0))
        throw std::runtime_error("GenGaussianKernel1D() - invalid kernel size");

    if (sigma <= (T)0)
        throw std::runtime_error("GenGaussianKernel1D() - invalid value for sigma");

    int ks2 = (int)ks / 2;
    T sigma_sq = sigma * sigma;
    std::vector<T> kernel(ks);
    const T pi = (T)M_PI;

    T sum = 0;

    for (int i = -ks2; i <= ks2; i++)
    {
        T temp1 = (T)i * i;
        T temp2 = -(temp1 / ((T)2.0 * sigma_sq));
        T temp3 = exp(temp2);
        T temp4 = ((T)1.0 / (sqrt((T)2.0 * pi) * sigma)) * temp3;

        kernel[i + ks2] = (T)temp4;
        sum += kernel[i + ks2];
    }

    for (size_t i = 0; i < ks; i++)
        kernel[i] /= sum;

    return kernel;
}

template<typename T> std::vector<T> GenGaussianKernel2D(T sigma, size_t ks)
{
    if ((ks < 3) || ((ks & 0x1) == 0))
        throw std::runtime_error("GenGaussianKernel2D() - invalid kernel size");

    if (sigma <= (T)0)
        throw std::runtime_error("GenGaussianKernel2D() - invalid value for sigma");

    int ks2 = (int)ks / 2;
    T sigma_sq = sigma * sigma;
    std::vector<T> kernel(ks * ks);
    const T pi = (T)M_PI;

     T sum = 0;

    for (int i = -ks2; i <= ks2; i++)
    {
        for (int j = -ks2; j <= ks2; j++)
        {
            T temp1 = (T)i * i + j * j;
            T temp2 = -(temp1 / ((T)2.0 * sigma_sq));
            T temp3 = exp(temp2);
            T temp4 = (T)1.0 / ((T)2.0 * pi * sigma_sq) * temp3;

            int k = (i + ks2) * (int)ks + j + ks2; 
            kernel[k] = (T)temp4;

            sum += kernel[k];
        }
    }

    for (size_t i = 0; i < ks * ks; i++)
        kernel[i] /= sum;

    return kernel;
}

template <typename T> void GenSignal1D(std::vector<T>& x, unsigned int rng_seed)
{
    const double degtorad = M_PI / 180.0;
    const double t_start = 0;
    const double t_step = 0.002;
    const size_t m = 3;
    const double amp[m]  {1.0, 0.80, 1.20};
    const double freq[m] {5.0, 10.0, 15.0};
    const double phase[m] {0.0, 45.0, 90.0};

    double t = t_start;
    size_t num_pts = x.size();
    std::mt19937 rng {rng_seed};
    std::uniform_real_distribution<double> dist {0, 500};

    for (size_t i = 0; i < num_pts; i++, t += t_step)
    {
        double x_val = 0;

        for (size_t j = 0; j < m; j++)
        {
            double omega = 2.0 * M_PI * freq[j];
            double x_temp1 = amp[j] * sin(omega * t + phase[j] * degtorad);
            double rand_val = dist(rng);

            double noise = (rand_val - 250.0) / 10.0;
            double x_temp2 = x_temp1 + x_temp1 * noise / 100.0;

            x_val += x_temp2;
        }

        x[i] = (T)x_val;
    }
}

template <typename T>
std::string SaveResults1D(const char* bn, const std::vector<std::vector<T>*>& signal_vectors, const std::vector<std::string>& titles)
{
    size_t num_signal_vectors = signal_vectors.size();

    if (num_signal_vectors == 0)
        throw std::runtime_error("SaveResults1D() - num_signal_vectors is zero");

    std::string s1 = std::string("_");
    std::string s2 = std::string(".csv");
    std::string fn = bn + s1 + OS::GetComputerName() + s2;

    std::ofstream ofs(fn);

    if (ofs.bad())
        throw std::runtime_error("SaveResults1D() - file error");

    const char nl = '\n';
    const char* delim = ", ";
    bool done = false;
    size_t i = 0;
    size_t w = 12;

    // Write column titles
    ofs << "ID" << delim;
    for (size_t i = 0; i < num_signal_vectors; i++)
        ofs << titles[i] << delim;
    ofs << nl;

    // Dump vector data
    ofs << std::fixed << std::setprecision(7);

    while (!done)
    {
        size_t x = 0;

        ofs << std::setw(5) << i << delim;
        
        for (size_t j = 0; j < num_signal_vectors; j++)
        {
            std::vector<T>& v = *signal_vectors[j];

            if (i < v.size())
                ofs << std::setw(w) << v[i] << delim;
            else
                    ofs << std::setw(w) << delim;

            if ((i + 1) >= v.size())
                x++;
        }

        ofs << nl;

        if (x == num_signal_vectors)
            done = true;
        else
            i++;
    }

    ofs.close();

    return fn;
}
