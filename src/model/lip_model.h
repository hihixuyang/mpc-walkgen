////////////////////////////////////////////////////////////////////////////////
///
///\file lip_model.h
///\brief Implement the linear inverted pendulum model
///\author Lafaye Jory
///\date 19/06/13
///
////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef MPC_WALKGEN_LIPM_H
#define MPC_WALKGEN_LIPM_H

#include "../type.h"

namespace MPCWalkgen
{

  class LIPModel
  {
    public:

      LIPModel(int nbSamples,
               Scalar samplingPeriod,
               bool autoCompute);
      LIPModel();
      ~LIPModel();

      /// \brief compute all of the dynamics
      void computeDynamics();
      void computeCopXDynamic();
      void computeCopYDynamic();
      void computeComPosDynamic();
      void computeComVelDynamic();
      void computeComAccDynamic();
      void computeComJerkDynamic();

      /// \brief Get the linear dynamic correspond to the CoP position X
      inline const LinearDynamic& getCopXLinearDynamic() const
      {return copXDynamic_;}


      /// \brief Get the linear dynamic correspond to the CoP position Y
      inline const LinearDynamic& getCopYLinearDynamic() const
      {return copYDynamic_;}

      /// \brief Get the linear dynamic correspond to the CoM position
      inline const LinearDynamic& getComPosLinearDynamic() const
      {return comPosDynamic_;}

      /// \brief Get the linear dynamic correspond to the CoM velocity
      inline const LinearDynamic& getComVelLinearDynamic() const
      {return comVelDynamic_;}


      /// \brief Get the linear dynamic correspond to the CoM acceleration
      inline const LinearDynamic& getComAccLinearDynamic() const
      {return comAccDynamic_;}


      /// \brief Get the linear dynamic correspond to the CoM jerk
      inline const LinearDynamic& getComJerkLinearDynamic() const
      {return comJerkDynamic_;}

      /// \brief Get the state of the CoM along the X coordinate
      ///        It's a vector of size 4:
      ///        (Position, Velocity, Acceleration, 1)
      inline void setStateX(const VectorX& state)
      {
        assert(state==state);assert(state.size()==4);assert(state(3)==1.0);
        stateX_=state;
      }

      /// \brief Get the state of the CoM along the X coordinate
      inline const VectorX& getStateX() const
      {return stateX_;}

      /// \brief Get the state of the CoM along the Y coordinate
      ///        It's a vector of size 4:
      ///        (Position, Velocity, Acceleration, 1)
      inline void setStateY(const VectorX& state)
      {
        assert(state==state);assert(state.size()==4);assert(state(3)==1.0);
        stateY_=state;
      }

      /// \brief Get the state of the CoM along the Y coordinate
      inline const VectorX& getStateY() const
      {return stateY_;}

      /// \brief Get the state of the CoM along the Z coordinate
      inline const VectorX& getStateZ() const
      {return stateZ_;}

      /// \brief Set the number of samples for this dynamic
      void setNbSamples(int nbSamples);

      /// \brief Get the number of samples for this dynamic
      inline int getNbSamples() const
      {return nbSamples_;}

      /// \brief Update the X state of the CoM apply a constant jerk
      void updateStateX(Scalar jerk, Scalar feedBackPeriod);

      /// \brief Update the Y state of the CoM apply a constant jerk
      void updateStateY(Scalar jerk, Scalar feedBackPeriod);

      /// \brief Set the sampling period for each sample
      void setSamplingPeriod(Scalar samplingPeriod);

      /// \brief Get the sampling period for each sample
      inline Scalar getSamplingPeriod(void) const
      {return samplingPeriod_;}

      /// \brief Set the CoM constant height
      void setComHeight(Scalar comHeight);

      /// \brief Get the CoM constant height
      inline Scalar getComHeight(void) const
      {return comHeight_;}

      /// \brief Set the body mass
      void setMass(Scalar mass);

      /// \brief Get the body mass
      inline Scalar getMass(void) const
      {return mass_;}

      /// \brief Set the robot total mass
      void setTotalMass(Scalar mass);

      /// \brief Set the constant gravity vector
      void setGravity(const Vector3& gravity);

    private:
      bool autoCompute_;

      bool useLipModel2_;

      int nbSamples_;
      Scalar samplingPeriod_;

      VectorX stateX_;
      VectorX stateY_;
      VectorX stateZ_; // For future case of use? Jory?

      Scalar comHeight_;
      Vector3 gravity_;
      Scalar mass_;
      Scalar totalMass_;

      LinearDynamic comPosDynamic_;
      LinearDynamic comVelDynamic_;
      LinearDynamic comAccDynamic_;
      LinearDynamic comJerkDynamic_;
      LinearDynamic copXDynamic_;
      LinearDynamic copYDynamic_;
  };

}

#endif //MPC_WALKGEN_LIPM_H