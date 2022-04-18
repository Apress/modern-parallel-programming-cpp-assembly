//------------------------------------------------
//               Ch06_01.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Ch06_01.h"
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
        std::cout << "Ch06_01 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void Convolve1D_F32(void)
{
    const char nl = '\n';
    const size_t num_pts = 79;
    const char* bn_results = "Ch06_01_Convolve1D_F32_Results";
    const std::vector<float> kernel { 0.0625f, 0.25f, 0.375f, 0.25f, 0.0625f };

    // Create input and output signal arrays
    std::cout << "Executing Convolve1D_F32()" << nl;

    std::vector<float> x(num_pts);
    GenSignal1D(x, c_RngSeed);
    std::vector<float> y1(num_pts);
    std::vector<float> y2(num_pts);
    std::vector<float> y3(num_pts);

    // Perform 1D convolutions
    Convolve1D_F32_Cpp(y1, x, kernel);
    Convolve1D_F32_Iavx2(y2, x, kernel);
    Convolve1DKs5_F32_Iavx2(y3, x, kernel);

    // Save results
    std::vector<std::vector<float>*> signal_vectors { &x, &y1, &y2, &y3 };
    std::vector<std::string> titles { "x", "y1", "y2", "y3"};
    std::string results_fn = SaveResults1D(bn_results, signal_vectors, titles);
    std::cout << "Results saved to file " << results_fn << nl;
}
