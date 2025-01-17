// mlvg test application
// Copyright (C) 2019-2022 Madrona Labs LLC
// This software is provided 'as-is', without any express or implied warranty.
// See LICENSE.txt for details.

#pragma once

#include "madronalib.h"
#include "MLAppView.h"
#include "MLWidget.h"
#include "MLView.h"
#include "MLDialBasic.h"
#include "MLResizer.h"
#include "MLTextLabelBasic.h"
#include "MLSVGImage.h"
#include "MLSVGButton.h"
#include "MLParameters.h"
#include "MLSerialization.h"

class TestAppView final:
  public ml::AppView
{
public:
  TestAppView(TextFragment appName, size_t instanceNum);
  ~TestAppView() override;

  // AppView interface
  void initializeResources(NativeDrawContext* nvg) override;
  void makeWidgets() override;
  void layoutView() override;
  void onGUIEvent(const GUIEvent& event) override {};
  void onResize(Vec2 newSize) override {};

  // Actor interface
  void onMessage(Message m) override;
};
