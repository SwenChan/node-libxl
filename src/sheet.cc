/**
 * The MIT License (MIT)
 * 
 * Copyright (c) 2013 Christian Speckner <cnspeckn@googlemail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "sheet.h"

#include <iostream>

#include "assert.h"
#include "util.h"
#include "argument_helper.h"
#include "format.h"

using namespace v8;

namespace node_libxl {


// Lifecycle

Sheet::Sheet(libxl::Sheet* sheet, Handle<Value> book) :
    Wrapper<libxl::Sheet>(sheet),
    BookWrapper(book)
{}


Handle<Object> Sheet::NewInstance(
    libxl::Sheet* libxlSheet,
    Handle<Value> book)
{
    HandleScope scope;

    Sheet* sheet = new Sheet(libxlSheet, book);

    Handle<Object> that = util::CallStubConstructor(constructor).As<Object>();

    sheet->Wrap(that);

    return scope.Close(that);
}


// Wrappers


Handle<Value> Sheet::CellType(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);

    int32_t row = args.GetInt(0);
    int32_t col = args.GetInt(1);
    ASSERT_ARGUMENTS(args);

    Sheet* that = Unwrap(arguments.This());
    ASSERT_THIS(that);

    libxl::CellType cellType = that->GetWrapped()->cellType(row, col);
    if (cellType == libxl::CELLTYPE_ERROR) {
        return util::ThrowLibxlError(that);
    }

    return scope.Close(Integer::New(cellType));
}


Handle<Value> Sheet::IsFormula(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);

    int32_t row = args.GetInt(0);
    int32_t col = args.GetInt(1);
    ASSERT_ARGUMENTS(args);

    Sheet* that = Unwrap(arguments.This());
    ASSERT_THIS(that);

    return scope.Close(Boolean::New(that->GetWrapped()->isFormula(row, col)));
}


Handle<Value> Sheet::CellFormat(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);

    int32_t row = args.GetInt(0);
    int32_t col = args.GetInt(1);
    ASSERT_ARGUMENTS(args);

    Sheet* that = Unwrap(arguments.This());
    ASSERT_THIS(that);

    libxl::Format* libxlFormat = that->GetWrapped()->cellFormat(row, col);
    if (!libxlFormat) {
        return util::ThrowLibxlError(that);
    }

    return scope.Close(Format::NewInstance(libxlFormat, that->GetBookHandle()));
}


Handle<Value> Sheet::WriteString(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);

    int32_t row = args.GetInt(0);
    int32_t col = args.GetInt(1);
    String::Utf8Value value(args.GetString(2));
    ASSERT_ARGUMENTS(args);

    Format* format = Format::Unwrap(arguments[3]);

    Sheet* that = Unwrap(arguments.This());
    ASSERT_THIS(that);
    if (format) {
        ASSERT_SAME_BOOK(that, format);
    }

    if (!that->GetWrapped()->
            writeStr(row, col, *value, format ? format->GetWrapped() : NULL))
    {
        return util::ThrowLibxlError(that);
    }

    return scope.Close(arguments.This());
}


Handle<Value> Sheet::WriteNum(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);

    int32_t row = args.GetInt(0);
    int32_t col = args.GetInt(1);
    double value = args.GetDouble(2);
    ASSERT_ARGUMENTS(args);

    Format* format = Format::Unwrap(arguments[3]);

    Sheet* that = Unwrap(arguments.This());
    ASSERT_THIS(that);
    if (format) {
        ASSERT_SAME_BOOK(that, format);
    }

    if (!that->GetWrapped()->
            writeNum(row, col, value, format ? format->GetWrapped() : NULL))
    {
        return util::ThrowLibxlError(that);
    }

    return scope.Close(arguments.This());
}


Handle<Value> Sheet::WriteFormula(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);

    int32_t row = args.GetInt(0);
    int32_t col = args.GetInt(1);
    String::Utf8Value value(args.GetString(2));
    ASSERT_ARGUMENTS(args);

    Format* format = Format::Unwrap(arguments[3]);

    Sheet* that = Unwrap(arguments.This());
    ASSERT_THIS(that);
    if (format) {
        ASSERT_SAME_BOOK(that, format);
    }

    if (!that->GetWrapped()->
            writeFormula(row, col, *value, format? format->GetWrapped() : NULL))
    {
        return util::ThrowLibxlError(that);
    }

    return scope.Close(arguments.This());
}


Handle<Value> Sheet::SetCol(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);

    int32_t first = args.GetInt(0);
    int32_t last = args.GetInt(1);
    double width = args.GetDouble(2);
    Format* format = Format::Unwrap(arguments[3]);
    bool hidden = args.GetBoolean(4, false);
    ASSERT_ARGUMENTS(args);

    Sheet* that = Unwrap(arguments.This());
    ASSERT_THIS(that);
    if (format) {
        ASSERT_SAME_BOOK(that, format);
    }

    if (!that->GetWrapped()->setCol(first, last, width,
            format ? format->GetWrapped() : NULL, hidden))
    {
        return util::ThrowLibxlError(that);
    }

    return scope.Close(arguments.This());
}


Handle<Value> Sheet::SetRow(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);

    int32_t row = args.GetInt(0);
    double height = args.GetDouble(1);
    Format* format = Format::Unwrap(arguments[2]);
    bool hidden = args.GetBoolean(3, false);
    ASSERT_ARGUMENTS(args);

    Sheet* that = Unwrap(arguments.This());
    ASSERT_THIS(that);
    if (format) {
        ASSERT_SAME_BOOK(that, format);
    }

    if (!that->GetWrapped()->setRow(row, height,
        format ? format->GetWrapped() : NULL, hidden))
    {
        return util::ThrowLibxlError(that);
    }

    return scope.Close(arguments.This());
}


Handle<Value> Sheet::SetMerge(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);

    int32_t rowFirst = args.GetInt(0);
    int32_t rowLast = args.GetInt(1);
    int32_t colFirst = args.GetInt(2);
    int32_t colLast = args.GetInt(3);
    ASSERT_ARGUMENTS(args);

    Sheet* that = Unwrap(arguments.This());
    ASSERT_THIS(that);

    if (!that->GetWrapped()->setMerge(rowFirst, rowLast, colFirst, colLast)) {
        return util::ThrowLibxlError(that);
    }
    
    return scope.Close(arguments.This());
}


// Init


void Sheet::Initialize(Handle<Object> exports) {
    using namespace libxl;

    HandleScope scope;

    Local<FunctionTemplate> t = FunctionTemplate::New(util::StubConstructor);
    t->SetClassName(String::NewSymbol("Sheet"));
    t->InstanceTemplate()->SetInternalFieldCount(1);

    BookWrapper::Initialize<Sheet>(t);

    NODE_SET_PROTOTYPE_METHOD(t, "cellType", CellType);
    NODE_SET_PROTOTYPE_METHOD(t, "isFormula", IsFormula);
    NODE_SET_PROTOTYPE_METHOD(t, "cellFormat", CellFormat);
    NODE_SET_PROTOTYPE_METHOD(t, "writeString", WriteString);
    NODE_SET_PROTOTYPE_METHOD(t, "writeNum", WriteNum);
    NODE_SET_PROTOTYPE_METHOD(t, "writeFormula", WriteFormula);
    NODE_SET_PROTOTYPE_METHOD(t, "setCol", SetCol);
    NODE_SET_PROTOTYPE_METHOD(t, "setRow", SetRow);
    NODE_SET_PROTOTYPE_METHOD(t, "setMerge", SetMerge);

    t->ReadOnlyPrototype();
    constructor = Persistent<Function>::New(t->GetFunction());

    NODE_DEFINE_CONSTANT(exports, CELLTYPE_EMPTY);
    NODE_DEFINE_CONSTANT(exports, CELLTYPE_NUMBER);
    NODE_DEFINE_CONSTANT(exports, CELLTYPE_STRING);
    NODE_DEFINE_CONSTANT(exports, CELLTYPE_BOOLEAN);
    NODE_DEFINE_CONSTANT(exports, CELLTYPE_BLANK);
    NODE_DEFINE_CONSTANT(exports, CELLTYPE_ERROR);
}


}