// This file is part of xsonrpc, an XML/JSON RPC library.
// Copyright (C) 2015 Erik Johansson <erik@ejohansson.se
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation; either version 2.1 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#include "fault.h"

namespace {

const char FAULT_CODE_NAME[] = "faultCode";
const char FAULT_STRING_NAME[] = "faultString";

} // namespace

namespace xsonrpc {

Fault::operator Value() const
{
  Value::Struct fault;
  fault[FAULT_CODE_NAME] = Value(myFaultCode);
  fault[FAULT_STRING_NAME] = Value(myFaultString);
  return std::move(fault);
}

const int32_t NotWellFormedFault::CODE = -32700;
const int32_t InvalidCharacterFault::CODE = -32702;
const int32_t InvalidXmlRpcFault::CODE = -32600;
const int32_t MethodNotFoundFault::CODE = -32601;
const int32_t InvalidParametersFault::CODE = -32602;
const int32_t InternalFault::CODE = -32603;

} // namespace xsonrpc