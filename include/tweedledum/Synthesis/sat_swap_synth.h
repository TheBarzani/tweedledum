/*------------------------------------------------------------------------------
| Part of Tweedledum Project.  This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
*-----------------------------------------------------------------------------*/
#pragma once

#include "../IR/Circuit.h"
#include <cstdint>
#include "../Target/Device.h"
#include <cstdint>

#include <nlohmann/json.hpp>
#include <cstdint>
#include <vector>
#include <cstdint>

namespace tweedledum {

Circuit sat_swap_synth(Device const& device,
  std::vector<uint32_t> const& init_cfg, std::vector<uint32_t> const& final_cfg,
  nlohmann::json const& config = {});

} // namespace tweedledum