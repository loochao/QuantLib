/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006 Ferdinando Ametrano
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007 StatPro Italia srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/reference/license.html>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/


#ifndef quantlib_marketmodel_hpp
#define quantlib_marketmodel_hpp

#include <ql/math/matrix.hpp>
#include <ql/utilities/null.hpp>
#include <ql/patterns/observable.hpp>
#include <vector>

namespace QuantLib {

    class EvolutionDescription;

    //! base class for market models
    /*! For each time step, generates the pseudo-square root of the covariance
        matrix for that time step.
    */
    class MarketModel {
      public:
        MarketModel(){};
        MarketModel(Size numberOfRates, 
                    Size numberOfFactors, 
                    Size numberOfSteps);
        virtual ~MarketModel() {}
        virtual const std::vector<Rate>& initialRates() const = 0;
        virtual const std::vector<Spread>& displacements() const = 0;
        virtual const EvolutionDescription& evolution() const = 0;
        virtual Size numberOfRates() const = 0;
        virtual Size numberOfFactors() const = 0;
        virtual Size numberOfSteps() const = 0;
        virtual const Matrix& pseudoRoot(Size i) const;
        virtual const Matrix& covariance(Size i) const;
        virtual const Matrix& totalCovariance(Size endIndex) const;

      protected:
        std::vector<Matrix> pseudoRoots_, covariance_, totalCovariance_;
    };

    //! base class for market-model factories
    class MarketModelFactory : public Observable {
      public:
        virtual ~MarketModelFactory() {}
        virtual boost::shared_ptr<MarketModel> create(
                                              const EvolutionDescription&,
                                              Size numberOfFactors) const = 0;
    };
    
    inline const Matrix& MarketModel::pseudoRoot(Size i) const {
        return pseudoRoots_[i];
    }
     
    inline const Matrix& MarketModel::covariance(Size i) const {
        return covariance_[i];
    }

    inline const Matrix& MarketModel::totalCovariance(Size endIndex) const {
        return totalCovariance_[endIndex];
    }

}

#endif