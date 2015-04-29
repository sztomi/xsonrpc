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

#include "util.h"
#include "xmlwriter.h"

namespace {

const char METHOD_CALL_TAG[] = "methodCall";
const char METHOD_NAME_TAG[] = "methodName";
const char METHOD_RESPONSE_TAG[] = "methodResponse";
const char FAULT_TAG[] = "fault";
const char PARAMS_TAG[] = "params";
const char PARAM_TAG[] = "param";

const char VALUE_TAG[] = "value";

const char ARRAY_TAG[] = "array";
const char BASE_64_TAG[] = "base64";
const char BOOLEAN_TAG[] = "boolean";
const char DATE_TIME_TAG[] = "dateTime.iso8601";
const char DOUBLE_TAG[] = "double";
const char INTEGER_32_TAG[] = "i4";
const char INTEGER_64_TAG[] = "i8";
const char NIL_TAG[] = "nil";
const char STRING_TAG[] = "string";
const char STRUCT_TAG[] = "struct";

const char DATA_TAG[] = "data";
const char MEMBER_TAG[] = "member";
const char NAME_TAG[] = "name";

} // namespace

namespace xsonrpc {

const char* XmlWriter::GetData() const
{
  return myPrinter.CStr();
}

size_t XmlWriter::GetSize() const
{
  return myPrinter.CStrSize() - 1;
}

void XmlWriter::StartDocument()
{
  myPrinter.PushHeader(false, true);
}

void XmlWriter::EndDocument()
{
  // Empty
}

void XmlWriter::StartRequest(const std::string& methodName)
{
  myPrinter.OpenElement(METHOD_CALL_TAG, true);

  myPrinter.OpenElement(METHOD_NAME_TAG, true);
  myPrinter.PushText(methodName.c_str());
  myPrinter.CloseElement(true);

  myPrinter.OpenElement(PARAMS_TAG, true);
}

void XmlWriter::EndRequest()
{
  myPrinter.CloseElement(true);
  myPrinter.CloseElement(true);
}

void XmlWriter::StartParameter()
{
  myPrinter.OpenElement(PARAM_TAG, true);
}

void XmlWriter::EndParameter()
{
  myPrinter.CloseElement(true);
}

void XmlWriter::StartResponse(bool isFault)
{
  myPrinter.OpenElement(METHOD_RESPONSE_TAG, true);

  if (!isFault) {
    myPrinter.OpenElement(PARAMS_TAG, true);
    myPrinter.OpenElement(PARAM_TAG, true);
  }
  else {
    myPrinter.OpenElement(FAULT_TAG, true);
  }
}

void XmlWriter::EndResponse(bool isFault)
{
  if (!isFault) {
    myPrinter.CloseElement(true);
    myPrinter.CloseElement(true);
  }
  else {
    myPrinter.CloseElement(true);
  }
  myPrinter.CloseElement(true);
}

void XmlWriter::StartArray()
{
  StartValue();
  myPrinter.OpenElement(ARRAY_TAG, true);
  myPrinter.OpenElement(DATA_TAG, true);
}

void XmlWriter::EndArray()
{
  myPrinter.CloseElement(true);
  myPrinter.CloseElement(true);
  EndValue();
}

void XmlWriter::StartStruct()
{
  StartValue();
  myPrinter.OpenElement(STRUCT_TAG, true);
}

void XmlWriter::EndStruct()
{
  myPrinter.CloseElement(true);
  EndValue();
}

void XmlWriter::StartStructElement(const std::string& name)
{
  myPrinter.OpenElement(MEMBER_TAG, true);

  myPrinter.OpenElement(NAME_TAG, true);
  myPrinter.PushText(name.c_str());
  myPrinter.CloseElement(true);
}

void XmlWriter::EndStructElement()
{
  myPrinter.CloseElement(true);
}

void XmlWriter::WriteBinary(const uint8_t* data, size_t size)
{
  StartValue();
  myPrinter.OpenElement(BASE_64_TAG, true);
  myPrinter.PushText(util::Base64Encode(data, size).c_str());
  myPrinter.CloseElement(true);
  EndValue();
}

void XmlWriter::WriteNull()
{
  StartValue();
  myPrinter.OpenElement(NIL_TAG, true);
  myPrinter.CloseElement(true);
  EndValue();
}

void XmlWriter::Write(bool value)
{
  StartValue();
  myPrinter.OpenElement(BOOLEAN_TAG, true);
  myPrinter.PushText(value);
  myPrinter.CloseElement(true);
  EndValue();
}

void XmlWriter::Write(double value)
{
  StartValue();
  myPrinter.OpenElement(DOUBLE_TAG, true);
  myPrinter.PushText(value);
  myPrinter.CloseElement(true);
  EndValue();
}

void XmlWriter::Write(int32_t value)
{
  StartValue();
  myPrinter.OpenElement(INTEGER_32_TAG, true);
  myPrinter.PushText(value);
  myPrinter.CloseElement(true);
  EndValue();
}

void XmlWriter::Write(int64_t value)
{
  StartValue();
  myPrinter.OpenElement(INTEGER_64_TAG, true);
  myPrinter.PushText(std::to_string(value).c_str());
  myPrinter.CloseElement(true);
  EndValue();
}

void XmlWriter::Write(const std::string& value)
{
  StartValue();
  myPrinter.OpenElement(STRING_TAG, true);
  myPrinter.PushText(value.c_str());
  myPrinter.CloseElement(true);
  EndValue();
}

void XmlWriter::Write(const tm& value)
{
  StartValue();
  myPrinter.OpenElement(DATE_TIME_TAG, true);
  myPrinter.PushText(util::FormatIso8601DateTime(value).c_str());
  myPrinter.CloseElement(true);
  EndValue();
}

void XmlWriter::StartValue()
{
  myPrinter.OpenElement(VALUE_TAG, true);
}

void XmlWriter::EndValue()
{
  myPrinter.CloseElement(true);
}

} // namespace xsonrpc
