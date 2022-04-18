//------------------------------------------------
//               Ch16_05.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Ch16_05.h"
#include "MT_Convolve.h"

static void Convolve1D_F32(void);

int main()
{
    try
    {
        Convolve1D_F32();
        Convolve1D_F32_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch16_05 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void Convolve1D_F32(void)
{
    const char nl = '\n';
    std::cout << "Executing Convolve1D_F32()" << nl;

    const std::vector<float> kernel { 0.0625f, 0.25f, 0.375f, 0.25f, 0.0625f };
    const size_t num_pts = 67;
    const char* bn_results = "Ch16_05_Convolve1D_F32_Results";

    // Create signal array
    std::vector<float> x(num_pts);
    GenSignal1D(x, c_RngSeed);

    // Create result arrays
    std::vector<float> y1(num_pts);
    std::vector<float> y2(num_pts);
    std::vector<float> y3(num_pts);

    // Perform 1D convolutions
    Convolve1D_F32_Cpp(y1, x, kernel);
    Convolve1D_F32_Aavx2(y2.data(), x.data(), kernel.data(), x.size(), kernel.size());
    Convolve1DKs5_F32_Aavx2(y3.data(), x.data(), kernel.data(), x.size());

    // Save results
    std::vector<std::vector<float>*> signal_vectors { &x, &y1, &y2, &y3 };
    std::vector<std::string> titles { "x", "y1", "y2", "y3" };
    std::string results_fn = SaveResults1D(bn_results, signal_vectors, titles);
    std::cout << "Results saved to file " << results_fn << nl;
}
