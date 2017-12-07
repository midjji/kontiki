//
// Created by hannes on 2017-12-07.
//

#ifndef TASERV2_TYPE_HELPERS_H
#define TASERV2_TYPE_HELPERS_H

#include <boost/hana.hpp>
namespace hana = boost::hana;

#include "trajectories/linear_trajectory.h"

#include "cameras/pinhole.h"
#include "cameras/atan.h"

#include "measurements/static_rscamera_measurement.h"
#include "measurements/position_measurement.h"

namespace TT = taser::trajectories;
namespace TM = taser::measurements;
namespace TC = taser::cameras;

static auto trajectory_types = hana::tuple_t<
    hana::template_t<TT::LinearTrajectory>,
    hana::template_t<TT::ConstantTrajectory>
>;

static auto camera_types = hana::tuple_t<
  TC::AtanCamera,
  TC::PinholeCamera
>;

static auto make_cam_meas = [](auto mtype, auto ctype) {
  using MeasType = typename decltype(mtype)::type;
  auto mclass = MeasType();
  return mclass(ctype);
};

static auto cam_meas_templates = hana::tuple_t<
  hana::template_t<TM::StaticRsCameraMeasurement>
>;

static auto camera_measurements = hana::ap(
    hana::make_tuple(make_cam_meas),
    cam_meas_templates,
    camera_types
    );

static auto measurement_types = hana::concat(
  camera_measurements,
  hana::tuple_t<TM::PositionMeasurement>
);
#endif //TASERV2_TYPE_HELPERS_H