//
// This file is a part of UERANSIM project.
// Copyright (c) 2023 ALİ GÜNGÖR.
//
// https://github.com/aligungr/UERANSIM/
// See README, LICENSE, and CONTRIBUTING files for licensing details.
//

#include "milenage.hpp"

#include <crypt-ext/milenage.hpp>
#include <stdexcept>

namespace crypto::milenage
{

Milenage Calculate2(const OctetString &opc, const OctetString &key, const OctetString &rand, 
                   const OctetString &amf)
{
    Milenage r;
    r.mac_a = OctetString::FromSpare(8);
    r.mac_s = OctetString::FromSpare(8);
    r.res = OctetString::FromSpare(8);
    r.ck = OctetString::FromSpare(16);
    r.ik = OctetString::FromSpare(16);
    r.ak = OctetString::FromSpare(6);
    r.ak_r = OctetString::FromSpare(6);

    if (milenage_f1_ESAKA(opc.data(), key.data(), rand.data(),amf.data(), r.mac_a.data(), r.mac_s.data()))
        throw std::runtime_error("Milenage calculation failed");
    if (milenage_f2345(opc.data(), key.data(), rand.data(), r.res.data(), r.ck.data(), r.ik.data(), r.ak.data(),
                       r.ak_r.data()))
        throw std::runtime_error("Milenage calculation failed");

    return r;
}
Milenage Calculate(const OctetString &opc, const OctetString &key, const OctetString &rand, const OctetString &sqn,
                   const OctetString &amf)
{
    Milenage r;
    r.mac_a = OctetString::FromSpare(8);
    r.mac_s = OctetString::FromSpare(8);
    r.res = OctetString::FromSpare(8);
    r.ck = OctetString::FromSpare(16);
    r.ik = OctetString::FromSpare(16);
    r.ak = OctetString::FromSpare(6);
    r.ak_r = OctetString::FromSpare(6);

    if (milenage_f1(opc.data(), key.data(), rand.data(), sqn.data(), amf.data(), r.mac_a.data(), r.mac_s.data()))
        throw std::runtime_error("Milenage calculation failed");
    if (milenage_f2345(opc.data(), key.data(), rand.data(), r.res.data(), r.ck.data(), r.ik.data(), r.ak.data(),
                       r.ak_r.data()))
        throw std::runtime_error("Milenage calculation failed");

    return r;
}
OctetString CalculateOpC(const OctetString &op, const OctetString &key)
{
    OctetString opc = OctetString::FromSpare(op.length());
    if (milenage_opc_gen(opc.data(), key.data(), op.data()))
        throw std::runtime_error("OPC calculation failed");
    return opc;
}

} // namespace crypto::milenage
