#include "TRandom3.h"
#include "TStopwatch.h"
#include <cmath>
#include <vector> 
#include <algorithm> 
#include <iostream> 

constexpr double pi=3.1415926;

struct cartesian{
    double x{0.}; 
    double y{0.};
};

struct polar{
    double r{0.}; 
    double phi{0.}; 
}; 

struct coordinateSet{
    cartesian cart; 
    polar pol; 
};

/// precise cartesian --> polar
inline polar precisePol (const cartesian & cart){
    return polar{ std::sqrt(cart.x*cart.x+cart.y*cart.y), std::atan2(cart.y,cart.x)}; 
}
/// precise polar --> cartesian
inline cartesian preciseCart (const polar & pol){
    return cartesian{ pol.r * std::cos(pol.phi), pol.r * std::sin(pol.phi)}; 
}

inline double approxdPhi(double x, double y, double InvR, double dx, double dy){
    return - y * InvR*InvR * dx + x * InvR*InvR * dy;
}

inline double approxdR(double x, double y, double InvR, double dx, double dy){
    return x * InvR * dx + y * InvR * dy;
}

inline polar approxPol(const coordinateSet & start, const cartesian & step){
    // TODO: Check if precision better it if we use the updated cartesian R? 
    double invR = 1./start.pol.r; 
    double newPhi = start.pol.phi + approxdPhi(start.cart.x,start.cart.y, invR, step.x,step.y); 
    if (newPhi > pi) newPhi -= 2.*pi; 
    return polar{start.pol.r+approxdR(start.cart.x,start.cart.y, invR, step.x,step.y), newPhi}; 
}

/// precise coordinate update 
inline coordinateSet preciseUpdate (const coordinateSet & start, const cartesian & step){
    cartesian newCart {start.cart.x+step.x, start.cart.y+step.y}; 
    return coordinateSet{newCart, precisePol(newCart)}; 
}
/// approximate coordinate update 
inline coordinateSet approxUpdate (const coordinateSet & start, const cartesian & step){
    return coordinateSet{cartesian{start.cart.x+step.x, start.cart.y+step.y}, approxPol(start,step)};
}

class correctingUpdator{
    public: 
    correctingUpdator(int iter){ m_maxIt = iter;} 
    coordinateSet update (const coordinateSet & start, const cartesian & step){
        /// after N steps, reset the polar coordinate using the precise cartesian 
        if (++m_currIt == m_maxIt){
            m_currIt = 0;
            cartesian newCart {start.cart.x + step.x, start.cart.y + step.y}; 
            return coordinateSet{newCart,precisePol(newCart)};  
        }
        else{
            return approxUpdate(start,step); 
        }
    }
    protected: 
        int m_maxIt{0};
        int m_currIt{0}; 
};

int main(){

    TRandom3 rdm; 

    const double velocity = 5.; /// max step in x and y (mm)

    /// Let's start around the IBL: 
    polar startPolar {33., rdm.Uniform(2*pi)-pi}; 

    /// keep track of the current starting coordinate, using precise transforms
    coordinateSet currentPrecise {preciseCart(startPolar), startPolar}; 
    /// keep track of the current starting coordinate, using approximate transform 
    coordinateSet currentApprox = currentPrecise; 
    /// keep track of the current starting coordinate, using correcting approximate transform 
    coordinateSet currentCorrApprox = currentPrecise; 

    /// instantiate a test version of the correcting updator
    correctingUpdator updateEvery10{10}; 

    /// now record a series of steps to test! 
    constexpr int nSteps = 100000000; 
    std::vector<cartesian> steps(nSteps);
    for (auto & step : steps){
        step.x = rdm.Uniform(-velocity, velocity); 
        step.y = rdm.Uniform(-velocity, velocity); 
    } 

    /// now, test the three approaches 

    /// First, we only care for timing. We need to check precision later! 
    TStopwatch sw1; 
    for (auto & step : steps){ 
        currentPrecise = preciseUpdate(currentPrecise, step); 
    }
    sw1.Stop(); 

    TStopwatch sw2; 
    for (auto & step : steps){ 
        currentApprox = approxUpdate(currentApprox, step); 
    }
    sw2.Stop(); 

    TStopwatch sw3; 
    for (auto & step : steps){ 
        currentCorrApprox = updateEvery10.update(currentCorrApprox, step); 
    }
    sw3.Stop(); 
    std::cout << "Timing for 100M steps: "<<sw1.CpuTime()<<"s for precise, "<<sw2.CpuTime()<<"s for full approx, "<<sw3.CpuTime()<<"s for correcting approx"<<std::endl;
    

    /// Now check the quality - reset coordinates
    double score = 0.;  
    currentApprox = coordinateSet{preciseCart(startPolar), startPolar}; 
    currentCorrApprox = coordinateSet{preciseCart(startPolar), startPolar}; 

    /// for every step, compare estimate to real in cartesian space
    for (auto & step : steps){ 
        currentApprox = approxUpdate(currentApprox, step);
        cartesian estimatedCart = preciseCart(currentApprox.pol);  
        /// the cartesian component is always accurate - compare to approximate polar component
        double errorX = currentApprox.cart.x - estimatedCart.x; 
        double errorY = currentApprox.cart.y - estimatedCart.y; 
        score += (errorX*errorX+errorY*errorY);
    }
    double scoreApprox = std::sqrt(score)/(double)nSteps; 
    /// same for correcting approx
    score=0.; 
    for (auto & step : steps){ 
        currentCorrApprox = updateEvery10.update(currentCorrApprox, step); 
        cartesian estimatedCart = preciseCart(currentCorrApprox.pol);  
        double errorX = currentCorrApprox.cart.x - estimatedCart.x; 
        double errorY = currentCorrApprox.cart.y - estimatedCart.y; 
        score += (errorX*errorX+errorY*errorY);
    }
    double scoreCorrApprox = std::sqrt(score)/(double)nSteps;
    
    std::cout << "Score (quadratic mean of deviations from true): "<<scoreApprox<<"mm for full approx, and "<<scoreCorrApprox<<"mm for correcting approx"<<std::endl;

    return 0; 
}