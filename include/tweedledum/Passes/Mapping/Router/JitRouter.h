/*------------------------------------------------------------------------------
| Part of Tweedledum Project.  This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
*-----------------------------------------------------------------------------*/
#pragma once

#include "../../../IR/Circuit.h"
#include <cstdint>
#include "../../../IR/Qubit.h"
#include <cstdint>
#include "../../../Operators/Reversible.h"
#include <cstdint>
#include "../../../Target/Device.h"
#include <cstdint>
#include "../../../Target/Mapping.h"
#include <cstdint>
#include "../../../Target/Placement.h"
#include <cstdint>
#include "../../Utility/reverse.h"
#include <cstdint>

namespace tweedledum {

class JitRouter {
public:
    JitRouter(
      Device const& device, Circuit const& original, Placement const& placement)
        : device_(device)
        , original_(original)
        , placement_(placement)
        , visited_(original_.num_instructions(), 0u)
        , involved_phy_(device_.num_qubits(), 0u)
        , phy_decay_(device_.num_qubits(), 1.0)
        , delayed_(device_.num_qubits())
    {
        extended_layer_.reserve(e_set_size_);
    }

    std::pair<Circuit, Mapping> run();

private:
    using Swap = std::pair<Qubit, Qubit>;

    bool add_front_layer();

    void select_extended_layer();

    std::vector<Qubit> find_unmapped(std::vector<Qubit> const& map) const;

    void place_two_v(Qubit const v0, Qubit const v1);

    void place_one_v(Qubit const v0, Qubit const v1);

    void add_instruction(Instruction const& inst);

    void add_delayed(Qubit const v);

    void add_swap(Qubit const phy0, Qubit const phy1);

    bool try_add_instruction(InstRef ref, Instruction const& inst);

    Swap find_swap();

    double compute_cost(std::vector<Qubit> const&, std::vector<InstRef> const&);

    Device const& device_;
    Circuit const& original_;
    Circuit* mapped_;
    Placement placement_;
    std::vector<uint32_t> visited_;

    // Sabre internals
    std::vector<InstRef> front_layer_;
    std::vector<InstRef> extended_layer_;
    std::vector<uint32_t> involved_phy_;
    std::vector<float> phy_decay_;
    std::vector<std::vector<InstRef>> delayed_;

    // Sabre configuration
    uint32_t e_set_size_ = 20;
    float e_weight_ = 0.5;
    float decay_delta = 0.001;
    uint32_t num_rounds_decay_reset = 5;
    bool use_look_ahead_ = true;
};

} // namespace tweedledum
