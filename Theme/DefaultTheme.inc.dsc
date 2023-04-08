## @file
#  This package defines a default theme for YaSetupPkg, A UEFI Settings utility.
#
#  wjs+o(wjs) team, 2023, All rights granted.
#
#  SPDX-License-Identifier: DO WHAT THE F**K YOU WANT TO PUBLIC LICENSE.
#
##

[PcdsFixedAtBuild]
  gYaSetupPkgTokenSpaceGuid.BackgroudColor      | 0xFFEFF0F1
  gYaSetupPkgTokenSpaceGuid.WindowCaptionColor  | 0xFFDEE0E2
  gYaSetupPkgTokenSpaceGuid.WindowCaptionHeight | 36
  gYaSetupPkgTokenSpaceGuid.DesiredScaleTargetW | 1920
  gYaSetupPkgTokenSpaceGuid.DesiredScaleTargetH | 1080
  gYaSetupPkgTokenSpaceGuid.PrimaryTextColor    | 0x002d2926
  gYaSetupPkgTokenSpaceGuid.BorderColor         | 0xFFDADCDE

[LibraryClasses]
  Theme|$(PLATFORM_NAME)/Theme/Default/DefaultTheme.inf
