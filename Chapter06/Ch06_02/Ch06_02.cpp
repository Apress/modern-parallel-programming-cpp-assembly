//------------------------------------------------
//               Ch06_02.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Ch06_02.h"
#include "MT_Convolve.h"

static void Convolve1D_F64(void);

int main()
{
    try
    {
        Convolve1D_F64();
        Convolve1D_F64_bm();
    }

    catch (std::exception& ex)
    {
        std::cout << "Ch06_02 exception: " << ex.what() << '\n';
    }

    return 0;
}

static void Convolve1D_F64(void)
{
    const char nl = '\n';
    const size_t num_pts = 79;
    const char* bn_results = "Ch06_02_Convolve1D_F64_Results";
    const std::vector<double> kernel { 0.0625, 0.25, 0.375, 0.25, 0.0625 };

    // Create input and output signal arrays
    std::cout << "Executing Convolve1D_F64()" << nl;

    std::vector<double> x(num_pts);
    GenSignal1D(x, c_RngSeed);
    std::vector<double> y1(num_pts);
    std::vector<double> y2(num_pts);
    std::vector<double> y3(num_pts);

    // Perform 1D convolutions
    Convolve1D_F64_Cpp(y1, x, kernel);
    Convolve1D_F64_Iavx2(y2, x, kernel);
    Convolve1DKs5_F64_Iavx2(y3, x, kernel);

    // Save results
    std::vector<std::vector<double>*> signal_vectors { &x, &y1, &y2, &y3 };
    std::vector<std::string> titles { "x", "y1", "y2", "y3" };
    std::string results_fn = SaveResults1D(bn_results, signal_vectors, titles);
    std::cout << "Results saved to file " << results_fn << nl;
}
