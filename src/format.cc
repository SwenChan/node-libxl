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

#include "format.h"

#include "assert.h"
#include "util.h"
#include "argument_helper.h"

using namespace v8;

namespace node_libxl {


// Lifecycle

Format::Format(libxl::Format* format, Handle<Value> book) :
    Wrapper<libxl::Format>(format),
    BookWrapper(book)
{}


Handle<Object> Format::NewInstance(
    libxl::Format* libxlFormat,
    Handle<Value> book)
{
    HandleScope scope;

    Format* format = new Format(libxlFormat, book);

    Handle<Object> that = util::CallStubConstructor(constructor).As<Object>();

    format->Wrap(that);

    return scope.Close(that);
}


// Wrappers


Handle<Value> Format::SetNumFormat(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);
    
    int32_t format = args.GetInt(0);
    ASSERT_ARGUMENTS(args);

    Format* that = Unwrap(arguments.This());
    ASSERT_THIS(that);

    that->GetWrapped()->setNumFormat(format);

    return scope.Close(arguments.This());
}


Handle<Value> Format::NumFormat(const Arguments& arguments) {
    HandleScope scope;

    Format* that = Unwrap(arguments.This());
    ASSERT_THIS(that);

    return scope.Close(Integer::New(that->GetWrapped()->numFormat()));
}


Handle<Value> Format::SetWrap(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);
    bool wrap = args.GetBoolean(0);
    ASSERT_ARGUMENTS(args);

    Format* that = Unwrap(arguments.This());
    ASSERT_THIS(that);

    that->GetWrapped()->setWrap(wrap);

    return scope.Close(arguments.This());
}


Handle<Value> Format::SetShrinkToFit(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);
    bool shrink = args.GetBoolean(0);
    ASSERT_ARGUMENTS(args);

    Format* that = Unwrap(arguments.This());
    ASSERT_THIS(that);

    that->GetWrapped()->setShrinkToFit(shrink);

    return scope.Close(arguments.This());
}


Handle<Value> Format::SetAlignH(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);

    int32_t align = args.GetInt(0);
    ASSERT_ARGUMENTS(args);

    Format* that = Unwrap(arguments.This());
    ASSERT_THIS(that);

    that->GetWrapped()->setAlignH(static_cast<libxl::AlignH>(align));

    return scope.Close(arguments.This());
}


Handle<Value> Format::SetFillPattern(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);

    int32_t pattern = args.GetInt(0);
    ASSERT_ARGUMENTS(args);

    Format* that = Unwrap(arguments.This());
    ASSERT_THIS(that);

    that->GetWrapped()->setFillPattern(static_cast<libxl::FillPattern>(pattern));

    return scope.Close(arguments.This());
}


Handle<Value> Format::SetPatternBackgroundColor(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);

    int32_t color = args.GetInt(0);
    ASSERT_ARGUMENTS(args);

    Format* that = Unwrap(arguments.This());
    ASSERT_THIS(that);

    that->GetWrapped()->setPatternBackgroundColor(static_cast<libxl::Color>(color));

    return scope.Close(arguments.This());
}


Handle<Value> Format::SetPatternForegroundColor(const Arguments& arguments) {
    HandleScope scope;

    ArgumentHelper args(arguments);

    int32_t color = args.GetInt(0);
    ASSERT_ARGUMENTS(args);

    Format* that = Unwrap(arguments.This());
    ASSERT_THIS(that);

    that->GetWrapped()->setPatternForegroundColor(static_cast<libxl::Color>(color));

    return scope.Close(arguments.This());
}


// Init


void Format::Initialize(Handle<Object> exports) {
    using namespace libxl;
    HandleScope scope;

    Local<FunctionTemplate> t = FunctionTemplate::New(util::StubConstructor);
    t->SetClassName(String::NewSymbol("Format"));
    t->InstanceTemplate()->SetInternalFieldCount(1);

    BookWrapper::Initialize<Format>(t);

    NODE_SET_PROTOTYPE_METHOD(t, "setNumFormat", SetNumFormat);
    NODE_SET_PROTOTYPE_METHOD(t, "numFormat", NumFormat);
    NODE_SET_PROTOTYPE_METHOD(t, "setWrap", SetWrap);
    NODE_SET_PROTOTYPE_METHOD(t, "setShrinkToFit", SetShrinkToFit);
    NODE_SET_PROTOTYPE_METHOD(t, "setAlignH", SetAlignH);
    NODE_SET_PROTOTYPE_METHOD(t, "setFillPattern", SetFillPattern);
    NODE_SET_PROTOTYPE_METHOD(t, "setPatternBackgroundColor",
        SetPatternBackgroundColor);
    NODE_SET_PROTOTYPE_METHOD(t, "setPatternForegroundColor",
        SetPatternForegroundColor);

    t->ReadOnlyPrototype();
    constructor = Persistent<Function>::New(t->GetFunction());

    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_GENERAL);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_NUMBER);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_NUMBER_D2);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_NUMBER_SEP);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_NUMBER_SEP_D2);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CURRENCY_NEGBRA);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CURRENCY_NEGBRARED);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CURRENCY_D2_NEGBRA);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CURRENCY_D2_NEGBRARED);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_PERCENT);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_PERCENT_D2);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_SCIENTIFIC_D2);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_FRACTION_ONEDIG);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_FRACTION_TWODIG);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_DATE);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CUSTOM_D_MON_YY);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CUSTOM_D_MON);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CUSTOM_MON_YY);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CUSTOM_HMM_AM);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CUSTOM_HMMSS_AM);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CUSTOM_HMM);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CUSTOM_HMMSS);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CUSTOM_MDYYYY_HMM);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_NUMBER_SEP_NEGBRA);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_NUMBER_SEP_NEGBRARED);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_NUMBER_D2_SEP_NEGBRA);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_NUMBER_D2_SEP_NEGBRARED);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_ACCOUNT);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_ACCOUNTCUR);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_ACCOUNT_D2);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_ACCOUNT_D2_CUR);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CUSTOM_MMSS);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CUSTOM_H0MMSS);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CUSTOM_MMSS0);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_CUSTOM_000P0E_PLUS0);
    NODE_DEFINE_CONSTANT(exports, NUMFORMAT_TEXT);

    NODE_DEFINE_CONSTANT(exports, ALIGNH_GENERAL);
    NODE_DEFINE_CONSTANT(exports, ALIGNH_LEFT);
    NODE_DEFINE_CONSTANT(exports, ALIGNH_CENTER);
    NODE_DEFINE_CONSTANT(exports, ALIGNH_RIGHT);
    NODE_DEFINE_CONSTANT(exports, ALIGNH_FILL);
    NODE_DEFINE_CONSTANT(exports, ALIGNH_JUSTIFY);
    NODE_DEFINE_CONSTANT(exports, ALIGNH_MERGE);
    NODE_DEFINE_CONSTANT(exports, ALIGNH_DISTRIBUTED);

    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_NONE);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_SOLID);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_GRAY50);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_GRAY75);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_GRAY25);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_HORSTRIPE);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_VERSTRIPE);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_REVDIAGSTRIPE);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_DIAGSTRIPE);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_DIAGCROSSHATCH);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_THICKDIAGCROSSHATCH);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_THINHORSTRIPE);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_THINVERSTRIPE);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_THINREVDIAGSTRIPE);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_THINDIAGSTRIPE);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_THINHORCROSSHATCH);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_THINDIAGCROSSHATCH);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_GRAY12P5);
    NODE_DEFINE_CONSTANT(exports, FILLPATTERN_GRAY6P25);

    NODE_DEFINE_CONSTANT(exports, COLOR_BLACK);
    NODE_DEFINE_CONSTANT(exports, COLOR_WHITE);
    NODE_DEFINE_CONSTANT(exports, COLOR_RED);
    NODE_DEFINE_CONSTANT(exports, COLOR_BRIGHTGREEN);
    NODE_DEFINE_CONSTANT(exports, COLOR_BLUE);
    NODE_DEFINE_CONSTANT(exports, COLOR_YELLOW);
    NODE_DEFINE_CONSTANT(exports, COLOR_PINK);
    NODE_DEFINE_CONSTANT(exports, COLOR_TURQUOISE);
    NODE_DEFINE_CONSTANT(exports, COLOR_DARKRED);
    NODE_DEFINE_CONSTANT(exports, COLOR_GREEN);
    NODE_DEFINE_CONSTANT(exports, COLOR_DARKBLUE);
    NODE_DEFINE_CONSTANT(exports, COLOR_DARKYELLOW);
    NODE_DEFINE_CONSTANT(exports, COLOR_VIOLET);
    NODE_DEFINE_CONSTANT(exports, COLOR_TEAL);
    NODE_DEFINE_CONSTANT(exports, COLOR_GRAY25);
    NODE_DEFINE_CONSTANT(exports, COLOR_GRAY50);
    NODE_DEFINE_CONSTANT(exports, COLOR_PERIWINKLE_CF);
    NODE_DEFINE_CONSTANT(exports, COLOR_PLUM_CF);
    NODE_DEFINE_CONSTANT(exports, COLOR_IVORY_CF);
    NODE_DEFINE_CONSTANT(exports, COLOR_LIGHTTURQUOISE_CF);
    NODE_DEFINE_CONSTANT(exports, COLOR_DARKPURPLE_CF);
    NODE_DEFINE_CONSTANT(exports, COLOR_CORAL_CF);
    NODE_DEFINE_CONSTANT(exports, COLOR_OCEANBLUE_CF);
    NODE_DEFINE_CONSTANT(exports, COLOR_ICEBLUE_CF);
    NODE_DEFINE_CONSTANT(exports, COLOR_DARKBLUE_CL);
    NODE_DEFINE_CONSTANT(exports, COLOR_PINK_CL);
    NODE_DEFINE_CONSTANT(exports, COLOR_YELLOW_CL);
    NODE_DEFINE_CONSTANT(exports, COLOR_TURQUOISE_CL);
    NODE_DEFINE_CONSTANT(exports, COLOR_VIOLET_CL);
    NODE_DEFINE_CONSTANT(exports, COLOR_DARKRED_CL);
    NODE_DEFINE_CONSTANT(exports, COLOR_TEAL_CL);
    NODE_DEFINE_CONSTANT(exports, COLOR_BLUE_CL);
    NODE_DEFINE_CONSTANT(exports, COLOR_SKYBLUE);
    NODE_DEFINE_CONSTANT(exports, COLOR_LIGHTTURQUOISE);
    NODE_DEFINE_CONSTANT(exports, COLOR_LIGHTGREEN);
    NODE_DEFINE_CONSTANT(exports, COLOR_LIGHTYELLOW);
    NODE_DEFINE_CONSTANT(exports, COLOR_PALEBLUE);
    NODE_DEFINE_CONSTANT(exports, COLOR_ROSE);
    NODE_DEFINE_CONSTANT(exports, COLOR_LAVENDER);
    NODE_DEFINE_CONSTANT(exports, COLOR_TAN);
    NODE_DEFINE_CONSTANT(exports, COLOR_LIGHTBLUE);
    NODE_DEFINE_CONSTANT(exports, COLOR_AQUA);
    NODE_DEFINE_CONSTANT(exports, COLOR_LIME);
    NODE_DEFINE_CONSTANT(exports, COLOR_GOLD);
    NODE_DEFINE_CONSTANT(exports, COLOR_LIGHTORANGE);
    NODE_DEFINE_CONSTANT(exports, COLOR_ORANGE);
    NODE_DEFINE_CONSTANT(exports, COLOR_BLUEGRAY);
    NODE_DEFINE_CONSTANT(exports, COLOR_GRAY40);
    NODE_DEFINE_CONSTANT(exports, COLOR_DARKTEAL);
    NODE_DEFINE_CONSTANT(exports, COLOR_SEAGREEN);
    NODE_DEFINE_CONSTANT(exports, COLOR_DARKGREEN);
    NODE_DEFINE_CONSTANT(exports, COLOR_OLIVEGREEN);
    NODE_DEFINE_CONSTANT(exports, COLOR_BROWN);
    NODE_DEFINE_CONSTANT(exports, COLOR_PLUM);
    NODE_DEFINE_CONSTANT(exports, COLOR_INDIGO);
    NODE_DEFINE_CONSTANT(exports, COLOR_GRAY80);
    NODE_DEFINE_CONSTANT(exports, COLOR_DEFAULT_FOREGROUND);
    NODE_DEFINE_CONSTANT(exports, COLOR_DEFAULT_BACKGROUND);
    NODE_DEFINE_CONSTANT(exports, COLOR_TOOLTIP);
    NODE_DEFINE_CONSTANT(exports, COLOR_AUTO);
}


}