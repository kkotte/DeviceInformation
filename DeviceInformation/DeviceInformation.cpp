// DeviceInformation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <collection.h>
#include <ppltasks.h>

using namespace std;
using namespace Platform;
using namespace Platform::Collections;
using namespace concurrency;
using namespace Windows::Devices::Enumeration;
using namespace Windows::Media::Devices;
using namespace Windows::Foundation;

int GetPropertyFromDefaultRenderDevice(String^ pkey)
{
	int value = -1;

	auto properties = ref new Vector<String^>();
	properties->Append(pkey);

	create_task(DeviceInformation::CreateFromIdAsync(MediaDevice::GetDefaultAudioRenderId(AudioDeviceRole::Default), properties)).then(
		[=, &value](DeviceInformation^ devinfo)
	{
		auto val = safe_cast<IPropertyValue^>(devinfo->Properties->Lookup(pkey));
		value = val->GetInt32();
	}).wait();

	return value;
}

int main(Array<String^>^ args)
{
	// properties are of the form L"{1DA5D803-D492-4EDD-8C23-E0C0FFEE7F0E} 0"
	cout << "Default render device has an int32 property of: " << GetPropertyFromDefaultRenderDevice(args[1]) << endl;
	return 0;
}

