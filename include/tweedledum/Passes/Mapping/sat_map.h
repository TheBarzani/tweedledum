/*------------------------------------------------------------------------------
| Part of Tweedledum Project.  This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
*-----------------------------------------------------------------------------*/
#pragma once

#include "../../IR/Circuit.h"
#include <cstdint>
#include "../../IR/Instruction.h"
#include <cstdint>
#include "../../Target/Device.h"
#include <cstdint>
#include "../Utility/shallow_duplicate.h"
#include <cstdint>
#include "placer/SatPlacer.h"
#include <cstdint>

#include <string_view>
#include <cstdint>

namespace tweedledum {

inline Circuit sat_map(Circuit const& original, Device const& device)
{
    auto placement = sat_place(device, original);
    Circuit mapped = shallow_duplicate(original);
    for (uint32_t i = original.num_qubits(); i < device.num_qubits(); ++i) {
        mapped.create_qubit();
    }
    if (placement) {
        original.foreach_instruction([&](Instruction const& inst) {
            std::vector<Qubit> qubits;
            inst.foreach_qubit([&](Qubit const& qubit) {
                qubits.push_back(placement->v_to_phy(qubit));
            });
            mapped.apply_operator(inst, qubits, inst.cbits());
        });
        return mapped;
    }
    return Circuit();
}

} // namespace tweedledum
